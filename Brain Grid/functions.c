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
/**
 * writing all the agents on the messageboard
 * @return 0
 */
int write_state()
{
  //add to messageboard
  if(TYPE != INACTIVE) add_state_message(I, J, TYPE, DIRECTION_X,DIRECTION_Y);

  return 0;
}

/**
 * ACTIVE:disperse signals toward a random direction
 * NEUTRAL:continues a motion
 * INACTIVE:stops a motion
 * @return 0
 */
int disperse()
{
  //srand(time(NULL));
  int mes_i, mes_j, mes_type, mes_directionX, mes_directionY;
  int_array destX, destY;

  if (TYPE == INACTIVE){
    DIRECTION_X = -1;
    DIRECTION_Y = -1;
  }
  //ACTIVE
  else if (TYPE == ACTIVE){
      int randDir = rand()%8;
      switch (randDir){
        case NW:
          DIRECTION_X = I - 1;
          DIRECTION_Y = J - 1;
          break;
        case N:
          DIRECTION_X = I - 1;
          DIRECTION_Y = J;
          break;
        case NE:
          DIRECTION_X = I - 1;
          DIRECTION_Y = J + 1;
          break;
        case W:
          DIRECTION_X = I;
          DIRECTION_Y = J - 1;
          break;
        case E:
          DIRECTION_X = I ;
          DIRECTION_Y = J + 1;
          break;
        case SE:
          DIRECTION_X = I + 1;
          DIRECTION_Y = J - 1;
          break;
        case S:
          DIRECTION_X = I + 1;
          DIRECTION_Y = J;
          break;
        case SW:
          DIRECTION_X = I + 1;
          DIRECTION_Y = J + 1;
          break;
        }
  }
  else if(TYPE == NEUTRAL){
    // initializing temp incoming directions
    init_int_array(&destX);
    init_int_array(&destY);

    //check the incoming signals
    START_STATE_MESSAGE_LOOP
      mes_type = state_message->type;

      if(mes_type != INACTIVE){

        mes_i = state_message->i;
        mes_j = state_message->j;

        //we only want neighbors
        if (((mes_i == I - 1) && (mes_j == J - 1)) ||
            ((mes_i == I - 1) && (mes_j == J)) ||
            ((mes_i == I - 1) && (mes_j == J + 1)) ||
            ((mes_i == I) && (mes_j == J - 1)) ||
            ((mes_i == I) && (mes_j == J + 1)) ||
            ((mes_i == I + 1) && (mes_j == J - 1)) ||
            ((mes_i == I + 1) && (mes_j == J)) ||
            ((mes_i == I + 1) && (mes_j == J + 1))) {

              mes_directionX = state_message->direction_x;
              mes_directionY = state_message->direction_y;

              //if its signal is coming toward this cell
              //is this cell signal going the opposite way?
              if(mes_directionX == I && mes_directionY == J){
                if (DIRECTION_X == mes_i && DIRECTION_Y == mes_j){
                  DIRECTION_X = STOP;
                  DIRECTION_Y = STOP;
                }
                else{
                  add_int(&destX,mes_i);
                  add_int(&destY,mes_j);
                }
              }
        }
      }
    FINISH_STATE_MESSAGE_LOOP;

    //update the new direction
    if (destX.size > 1){
      int picked_dir = rand()% destX.size;
      DIRECTION_X = destX.array[picked_dir];
      DIRECTION_Y = destY.array[picked_dir];
    }
    else if (destX.size == 1){
      DIRECTION_X = destX.array[0];
      DIRECTION_Y = destY.array[0];
    }
  }
  //reset temp arrays
  reset_int_array(&destX);
  reset_int_array(&destY);
  return 0;
}
