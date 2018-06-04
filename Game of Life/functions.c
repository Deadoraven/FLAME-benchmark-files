
/*
*agent functions
*/

#include "header.h"
#include "life_agent_header.h"

int write_state()
{
  if (STATE == 1) {
    add_state_message(ID, I, J, STATE);
  }
  return 0;
}
int read_states()
{

  int mes_id, mes_i, mes_j, mes_state;
  int count;

  for (count = 0; count <= 7; count++)
    NEIGHBORS[count] = 0;

  count = 0;

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
      NEIGHBORS[count] = mes_state;
      count++;
    }
  }
  //end of loop
  FINISH_STATE_MESSAGE_LOOP;
  return 0;
}

int react()
{
  //retreive the initail info of the agent
  int i, count;

  //count to keep track of alive neighbors
  count = 0;
  //check how many neighbors are alive
  for (i = 0; i < 8; i++) {
    if (NEIGHBORS[i] == 1) count++;
  }

  //react to neighbors
  if (count < 2)  STATE = 0;
  if (count == 2) continue;
  if (count == 3) STATE = 1;
  if (count > 3)  STATE = 0;


  return 0;
}
