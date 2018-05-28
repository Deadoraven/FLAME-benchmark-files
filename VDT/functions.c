#include "header.h"
#include "supervisor_agent_header.h"
#include "phase_agent_header.h"
#include "headquarter_agent_header.h"
#include "developer_agent_header.h"

int dev_counter = 0;
int sup_counter = 0;
/*******************************************************
 ******** All functions related to Supervisors**********
 *******************************************************/
int write_supers()
{
  add_supers_message(ID, PHASE_ID, FUND,IS_HIRING);
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
  int mes_id, mes_superID, mes_devNeed, mes_moneyNeed;

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
  return 0;
}

/**
 * request money from hq
 * @return 0
 */
//TODO PROBLEM all will be set to 0;
int fund_request()
{
  int mes_money;

  START_HEADQUARTER_MESSAGE_LOOP

    mes_money = headquarter_message->money;
    FUND = (mes_money - FUND >= 0) ? 0:FUND;

  FINISH_HEADQUARTER_MESSAGE_LOOP

  return 0;
}

int hire()
{
  if (IS_HIRING > 0){

    //do we need to hire at all ?
    int mes_superID, mes_isWorking;

    START_DEVS_MESSAGE_LOOP

      if (IS_HIRING > 0){ // do we still need to hire more?
        mes_id = devs_message->d_id;
        mes_superID = devs_message->d_super_id;
        mes_isWorking = devs_message->is_working;

        if(mes_id > dev_counter){
          if (!mes_isWorking && mes_superID == ID ){
            IS_HIRING --;
            dev_counter ++;
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

  int mes_id, mes_superID,mes_isDone;

  START_PHASES_MESSAGE_LOOP
    mes_id = phases_message->p_id;
    mes_superID = phases_message->p_super_id;

    if (ID ==  mes_superID && PHASE_ID == mes_id){

      mes_isDone = phases_message->is_done;
      if (mes_isDone){
         PHASE_ID++;
         TOTAL_PHASES--;
         if (TOTAL_PHASES == 0) return 1;
      }
    }
  FINISH_PHASES_MESSAGE_LOOP

  return 0;
}

/*******************************************************
 ********** All functions related to Phases ************
 *******************************************************/
int write_phases()
{

  add_phases_message(P_ID, P_SUPER_ID, NEEDED_MONEY, NEEDED_DEV, IS_DONE);
  return 0;
}

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
int write_devs()
{
    if (D_SUPER_ID == 0) add_devs_message(D_ID, D_SUPER_ID,IS_WORKING);
    return 0;
}

int hire_devs()
{
  int mes_id,mes_isHiring;
  


  return 0;
}



  /*******************************************************
   ********* All functions related to Headquarter ********
   *******************************************************/
int write_hq()
{
    add_headquarter_message(MONEY,LAST_READ);
    return 0;
}


int update_money()
{
  int mes_need;

  START_SUPERS_MESSAGE_LOOP
    mes_need = supers_message->fund;
    MONEY =  (MONEY - mes_need >= 0) ? (MONEY - mes_need):MONEY;
  FINISH_SUPERS_MESSAGE_LOOP
  return 0;
}
