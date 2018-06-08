
/*
*agent functions
*/

#include "header.h"
#include "life_agent_header.h"

/**
 * writing alive agents on message board
 * @return [description]
 */
int write_state()
{
  if (STATE == 1) {
    add_state_message(ID, I, J, STATE);
  }
  return 0;
}

/**
 * read and find alive neighbors and increase count
 * @return 0
 */
int read_states()
{

  int mes_i, mes_j, mes_state;


  //start reading the messageboard
  START_STATE_MESSAGE_LOOP;

  //is it another agent?
  if (state_message->id != ID) {
    mes_i = state_message->i;
    mes_j = state_message->j;

    //check if it is a neighbor
    if (((mes_i == I - 1) && (mes_j == J - 1)) ||
        ((mes_i == I - 1) && (mes_j == J)) ||
        ((mes_i == I - 1) && (mes_j == J + 1)) ||
        ((mes_i == I) && (mes_j == J - 1)) ||
        ((mes_i == I) && (mes_j == J + 1)) ||
        ((mes_i == I + 1) && (mes_j == J - 1)) ||
        ((mes_i == I + 1) && (mes_j == J)) ||
        ((mes_i == I + 1) && (mes_j == J + 1))) {

          //add neighbor state to neighbors
          mes_state = state_message->state;
          if (mes_state == 1) COUNT++;
    }
  }

  //end of loop
  FINISH_STATE_MESSAGE_LOOP;
  return 0;
}

/**
 * react accordingly following the conway's game of life
 * @return 0
 */
int react()
{
  //react to neighbors
  if (COUNT < 2)  STATE = 0;
  if (COUNT == 3) STATE = 1;
  if (COUNT > 3)  STATE = 0;

  return 0;
}
