/*
*agent functions
*/
#include "header.h"
#include "neuron_agent_header.h"
#include <time.h>


//8 different direction
enum directions{
      NW,N,NE,W,E,SW,S,SE
};

//type of neurons
enum neurons{
  INACTIVE, NEUTRAL, ACTIVE
};


enum movement{
  STOP, IN, OUT
};

int write_state()
{
  //add to messageboard
  add_state_message(I, J, TYPE, DIRECTION);

  return 0;
}

int read_states()
{
  int mes_i, mes_j, mes_type;
  int * mes_direction;

  //Start Reading the messageboard
  START_STATE_MESSAGE_LOOP;

      mes_i = state_message->i;
      mes_j = state_message->j;

      /*
      I did this on purpose like this. I wanted to make sure
      that each neighbor will sit in its exact location in the
      arrays:

            [NW][N][NE]
             [W][A][E]    =====> neighbors={NW,N,NE,W,E,SW,S,SE}
            [SW][S][SE]

      */

    if ((mes_i == I- 1) && (mes_j == J - 1)){
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[NW] = mes_type;
      if (mes_direction[SE] == OUT){
        DIRECTION[NW] = IN;
      }
    }
    else if ((mes_i == I - 1) && (mes_j == J)){
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[N] = mes_type;
      if (mes_direction[S] == OUT){
        DIRECTION[N] = IN;
      }
    }
    else if ((mes_i == I - 1) && (mes_j == J + 1)){
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[NE] = mes_type;
      if (mes_direction[SW] == OUT){
        DIRECTION[NE] = IN;
      }
    }
    else if ((mes_i == I) && (mes_j == J - 1)) {
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[W] = mes_type;
      if (mes_direction[E] == OUT){
        DIRECTION[W] = IN;
      }
    }
    else if ((mes_i == I) && (mes_j == J + 1)) {
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[E] = mes_type;
      if (mes_direction[W] == OUT){
        DIRECTION[E] = IN;
      }
    }
    else if ((mes_i == I +1) && (mes_j == J - 1)) {
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[SW] = mes_type;
      if (mes_direction[NE] == OUT){
        DIRECTION[SW] = IN;
      }
    }
    else if ((mes_i == I+1) && (mes_j == J ))
    {
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[S] = mes_type;
      if (mes_direction[N] == OUT){
        DIRECTION[S] = IN;
      }
    }
    else if((mes_i == I + 1) && (mes_j == J + 1)) {
      mes_type = state_message->type;
      mes_direction = state_message->direction;
      NEIGHBORS[SE] = mes_type;
      if (mes_direction[NW] == OUT){
        DIRECTION[SE] = IN;
      }
    }

  FINISH_STATE_MESSAGE_LOOP;

  return 0;
}

int react()
{

  if (TYPE == INACTIVE){
    for (int i = 0 ; i <8 ; i++ ){
      DIRECTION[i] = STOP;
    }
  }

  if (TYPE == NEUTRAL){

    for (int i =0 ; i< 8 ; i++){

      if (NEIGHBORS[i] == ACTIVE || NEIGHBORS[i] == NEUTRAL){

        if (DIRECTION[i] == IN && DIRECTION [7-i] == STOP)
        {
          DIRECTION[7-i] =OUT;
        }
        else if (DIRECTION[i] == IN && DIRECTION [7-i]== IN)
        {
          DIRECTION[i] = STOP;
        }
      }
    }
  }

  if (TYPE == ACTIVE){
      srand(time(NULL))
      int randDir = rand()%8;
      DIRECTION[randDir] = OUT;

      for (int i =0 ; i < 8 ; i++ ){
       if (NEIGHBORS[i] == ACTIVE && DIRECTION[i] == IN){
         DIRECTION[i] = STOP;
       }
     }
  }
  return 0;
}
