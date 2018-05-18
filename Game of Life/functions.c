
/*
*agent functions
*/

#include "header.h"
#include "life_agent_header.h"

int write_state()
{
  int my_state, my_id, my_i, my_j;
  my_state = get_state();
  my_id = get_id();
  my_i = get_i();
  my_j = get_j();
  if (my_state == 1) {
    add_state_message(my_id, my_i, my_j, my_state);
  }
  return 0;
}
int read_states()
{
  int my_id, my_i, my_j;
  int mes_id, mes_i, mes_j, mes_state;
  int count;
  my_id = get_id();
  my_i = get_i();
  my_j = get_j();

  for (count = 0; count <= 7; count++)
    NEIGHBORS[count] = 0;

  count = 0;

  //start reading the messageboard
  START_STATE_MESSAGE_LOOP;

  //is it another agent?
  if (state_message->id != my_id) {
    mes_id = state_message->id;
    mes_i = state_message->i;
    mes_j = state_message->j;

    //check if it is a neighbor
    if (((mes_i == my_i - 1) && (mes_j == my_j - 1)) ||
        ((mes_i == my_i - 1) && (mes_j == my_j)) ||
        ((mes_i == my_i - 1) && (mes_j == my_j + 1)) ||
        ((mes_i == my_i) && (mes_j == my_j - 1)) ||
        ((mes_i == my_i) && (mes_j == my_j + 1)) ||
        ((mes_i == my_i + 1) && (mes_j == my_j - 1)) ||
        ((mes_i == my_i + 1) && (mes_j == my_j)) ||
        ((mes_i == my_i + 1) && (mes_j == my_j + 1))) {

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
  int my_id, my_i, my_j, my_state;
  int i, count;

  my_id = get_id();
  my_i = get_i();
  my_j = get_j();
  my_state = get_state();

  //count to keep track of alive neighbors
  count = 0;
  //check how many neighbors are alive
  for (i = 0; i < 8; i++) {
    if (NEIGHBORS[i] == 1) count++;
  }

  //react to neighbors
  if (count < 2)  my_state = 0;
  if (count == 2) my_state = my_state;
  if (count == 3) my_state = 1;
  if (count > 3)  my_state = 0;

  //set the new state
  set_state(my_state);

  return 0;
}
