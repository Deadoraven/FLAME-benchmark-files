#include "header.h"
#include "supervisor_agent_header.h"
#include "phase_agent_header.h"
#include "headquarter_agent_header.h"
#include "developer_agent_header.h"

int_array employed, laidoff, reserve_employed, reserve_laidoff, dispersed_funds;
int spent_money;

/**
 * checking if the developer is employed already or not
 * @param  employeeId
 * @return    0
 */
int isEmployed(int employeeId)
{
  for (int i= 0; i < employed.size;i++){
    if (employed.array[i] == employeeId) return 1;
  }
  add_int(&employed, employeeId);
  return 0;
}

/**
 * layoff extra developers
 * @return 0
 */
int layoff()
{
    int index;

    while (IS_HIRING < 0){
      if(reserve_employed.size > 0){
        index = EMPLOYEES.size - 1;
        add_int(&reserve_laidoff, EMPLOYEES.array[index]);
        remove_int(&EMPLOYEES,index);
        IS_HIRING ++;
      }
      else {
        index = EMPLOYEES.size - 1;
        add_int(&laidoff, EMPLOYEES.array[index]);
        remove_int(&EMPLOYEES,index);
        IS_HIRING ++;
      }
    }
    return 0;
}

/**
 * setting the is_working to 0 for laidoff devs
 * @return 1 and 0
 */
int dev_quit()
{
  if (RESERVE){
    for (int i = 0 ; i < reserve_laidoff.size; i++){
      if (reserve_laidoff.array[i]== ID){
        IS_WORKING = 0;
        return 1;
      }
    }
  }
  else{
    for (int i = 0 ; i < laidoff.size; i++){
      if (laidoff.array[i]== ID){
        IS_WORKING = 0;
        return 1;
      }
    }
  }
  return 0;
}
/*******************************************************
 ******** All functions related to Supervisors**********
 *******************************************************/
int write_supers()
{
  add_supers_message(ID, PHASE_ID, FUND, IS_HIRING);

  return 0;
}

/**
 * "ASSUMPTION: all supervisors will start
 *              at phase 1 in the begining of simulation"
 * check if we have all the requirements or need to hire people
 * by setting the fund and is_hiring to the number of needs
 * @return 0
 */
int req_check()
{
  init_int_array(&EMPLOYEES);
  init_int_array(&employed);
  init_int_array(&laidoff);
  init_int_array(&reserve_employed);
  init_int_array(&reserve_laidoff);
  init_int_array(&dispersed_funds);
  int mes_id, mes_superID, mes_devNeed, mes_moneyNeed;

  IS_HIRING = EMPLOYEES.size;

  START_PHASES_MESSAGE_LOOP
    mes_id = phases_message->p_id;
    mes_superID = phases_message->p_super_id;

    if (ID ==  mes_superID && PHASE_ID == mes_id){
      mes_moneyNeed = phases_message->needed_money;
      mes_devNeed = phases_message->needed_dev;

      FUND = mes_moneyNeed - FUND;
      IS_HIRING = mes_devNeed - IS_HIRING;
    }
  FINISH_PHASES_MESSAGE_LOOP
  if (IS_HIRING < 0) layoff();
  return 0;
}

/**
 * request money from hq
 * @return 0
 */
int fund_request()
{
  int mes_money;
  START_HEADQUARTER_MESSAGE_LOOP

    mes_money = headquarter_message->money;

  FINISH_HEADQUARTER_MESSAGE_LOOP

  if(spent_money + FUND <= mes_money){
      add_int(&dispersed_funds, FUND);
      spent_money += FUND;
      FUND =  0;
  }

  return 0;
}

/**
 * hire unemployed developers
 * @return 0
 */
int hire()
{
  if (IS_HIRING > 0){
    //do we need to hire at all ?
    int mes_id, mes_isWorking;

    START_DEVS_MESSAGE_LOOP

      if (IS_HIRING > 0){ // do we still need to hire more?
        mes_id = devs_message->d_id;
        mes_isWorking = devs_message->is_working;
        mes_reserve = devs_message->reserve;

        if (!mes_isWorking && !isEmployed(mes_id) ){
          if(!mes_reserve){
            IS_HIRING --;
            add_int(&EMPLOYEES, mes_id);
          }
          else{
            IS_HIRING --;
            add_int(&EMPLOYEES, mes_id);
            add_int(&reserve_employed, mes_id);
          }
        }
      }
      else break;

    FINISH_DEVS_MESSAGE_LOOP
  }
  return 0;
}



/**
 * after everything is done checks if the phase is over
 * then change it to next phase.
 * @return 1 if all phases has finished otherwise 0
 */
int phase_change(){

  if(IS_HIRING == 0 && FUND == 0){
         PHASE_ID++;
         TOTAL_PHASES--;
         if (TOTAL_PHASES == 0) return 1;
  }
  reset_int_array(&employed);
  reset_int_array(&laidoff);
  return 0;
}

/*******************************************************
 ********** All functions related to Phases ************
 *******************************************************/
/**
 * write all the phases of each project on MB
 * @return 0
 */
int write_phases()
{

  add_phases_message(P_ID, P_SUPER_ID, NEEDED_MONEY, NEEDED_DEV, IS_DONE);
  return 0;
}

/**
 * check if the phase has ended
 * @return 1 and removes the phase if ended otherwise 0
 */
int check_end()
{
  int mes_id, mes_phaseId, mes_isHiring, mes_finSrc;

  START_SUPERS_MESSAGE_LOOP

    mes_id = supers_message->id;
    mes_phaseId = supers_message->phase_id;

    if(P_SUPER_ID == mes_id && P_ID == mes_phaseId){
      mes_isHiring = supers_message->is_hiring;
      mes_finSrc = supers_message->fund;

      if(mes_isHiring == 0 && mes_finSrc == 0){
        IS_DONE = 1;
        return 1; //remove the agent from simulation
      }
    }
  FINISH_SUPERS_MESSAGE_LOOP

  return 0;
}


 /*******************************************************
  ********* All functions related to Developers *********
  *******************************************************/
/**
 * write all the developers on MB
 * @return 0
 */
int write_devs()
{
    add_devs_message(D_ID, IS_WORKING, RESERVE);
    return 0;
}

/**
 * first check if anyone was laid laid off and then hire and
 * set the IS_WORKING
 * @return [description]
 */
int hire_devs()
{
    if (reserve_laidoff.size > 0 || laidoff.size > 0) dev_quit();
    for (int i = 0; i < employed.size ; i++){
      if (employed.array[i] == D_ID) IS_WORKING = 1;
    }
    return 0;
}

  /*******************************************************
   ********* All functions related to Headquarter ********
   *******************************************************/
   /**
    * write the headquarter on the MB
    * @return 0
    */
int write_hq()
{

    spent_money = 0;
    add_headquarter_message(MONEY);
    return 0;
}

/**
 * updates the money in the headquarter
 * @return 0
 */
int update_money()
{
  int index;
  index = 0;

  while (index < dispersed_funds.size){
    MONEY -= dispersed_funds.array[index];

    index++;
  }


  reset_int_array(&dispersed_funds);

  return 0;
}
