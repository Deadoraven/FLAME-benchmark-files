#include "header.h"
#include "finance_agent_header.h"
#include "cluster_agent_header.h"
#include <time.h>


int_array in_need, taken;
//three different type
enum financialEntity{
    CLUSTER,FIRM,BANK
};

/*******************************************************
 ******** All functions related to Clusters ************
 *******************************************************/
/**
 * write clusters on the message
 * @return 0
 */
int write_clusters()
{
    //write them on messageboard
    add_clusters_message(ID, HASBANK);
    return 0;
}

/**
 * set hasbank if there's a bank with money here.
 * @return 0
 */
int set_has_bank(){

    int mes_cid, mes_money;

    //Start looping through message board
    START_BANKS_MESSAGE_LOOP
      mes_cid = banks_message->c_id;
      mes_money = banks_message->money;

      if (mes_cid == ID && mes_money > 0){
          HASBANK = BANK;
      }
    FINISH_BANKS_MESSAGE_LOOP
    return 0 ;
}

/**
 * find if there's any firms in this cluster or not
 * @return 0
 */
int find_firms(){

    int mes_cid, mes_money;

    START_FIRMS_MESSAGE_LOOP
      mes_cid = firms_message->c_id;
      mes_money = firms_message->money;

      if (mes_cid == ID && HASBANK == BANK) continue;
      else if(mes_cid == ID && mes_money<= 0 && HASBANK != BANK){
          HASBANK = FIRM;
      }
    FINISH_FIRMS_MESSAGE_LOOP
    return 0;
}

/**
 * determine the next destination for the bank in this cluster
 * @return 0
 */

int bank_dest()
{

    int already_taken = 0;

    if (HASBANK == BANK){
        int count, numDest, newDest, mes_id, mes_hasbank;
        count = 0;

        START_CLUSTERS_MESSAGE_LOOP
          mes_id = clusters_message->id;
          mes_hasbank = clusters_message->hasbank;

          if (mes_id != ID && mes_hasbank == FIRM){
            for (int i = 0 ;i < taken.size; i++){
              if (taken.array[i] == mes_id) already_taken = 1;
            }
            if(!already_taken){
              add_int(&taken, mes_id);
              DESTINATION = mes_id;
            }
          }
          else DESTINATION = 0;

        FINISH_CLUSTERS_MESSAGE_LOOP

    }

    add_destinations_message(ID, DESTINATION);

    return 0;
}

/*******************************************************
 ****** All functions related to financialEntities *****
 *******************************************************/

/**
 * write agents on message board
 * @return 0
 */
int write_agents()
{
    if (TYPE == BANK) add_banks_message(C_ID, MONEY);

    else if (TYPE == FIRM) add_firms_message(C_ID, MONEY);

    return 0;

}

/**
 * update all the money in banks and firms
 * @return 0
 */
int update(){

    int mes_cid, mes_money;

    if(MONEY < 0){// we have a FIRM

        START_BANKS_MESSAGE_LOOP

          mes_cid = banks_message->c_id;
          mes_money = banks_message->money;

          if(C_ID == mes_cid && mes_money > 0){
              if (MONEY + mes_money <= 0)
              {
                  MONEY += mes_money;
              }
              else {
                  MONEY = 0;
              }
          }
        FINISH_BANKS_MESSAGE_LOOP
    }

    else if( MONEY > 0 ){//there's a bank with some money
        START_FIRMS_MESSAGE_LOOP

          mes_cid = firms_message->c_id;
          mes_money = firms_message->money;

          if(C_ID == mes_cid && mes_money < 0){
              if (MONEY + mes_money >= 0)
              {
                  MONEY += mes_money;
              }
              else {
                  MONEY = 0;
              }
          }
        FINISH_FIRMS_MESSAGE_LOOP
    }
    return 0;
}

/**
 * move banks to new place
 * @return 0
 */
int move(){
    int my_cid;
    reset_int_array(&taken);
    if (MONEY > 0){//do we need this bank to move at all?
        int mes_id, mes_destination;

        START_DESTINATIONS_MESSAGE_LOOP
          mes_id = destinations_message->id;
          if (mes_id == C_ID){
            mes_destination = destinations_message->destination;
            my_cid = mes_destination;

          }

        FINISH_DESTINATIONS_MESSAGE_LOOP
        C_ID = my_cid;
    }

    return 0;
}
