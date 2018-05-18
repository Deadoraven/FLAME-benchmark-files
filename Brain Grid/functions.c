/*
*agent functions
*/
#include "header.h"
#include "neuron_agent_header.h"

//8 different direction
enum directions{
      NW,N,NE,W,E,SW,S,SE
};

//type of neurons
enum neurons{
  INACTIVE, NEUTRAL, ACTIVE
};

//type of stage
enum stageStatus{
  DEACTIVATED,ENACTED
};

enum directionStatus{
   STOP, IN, OUT
};

int write_state()
{
  int my_id, my_i, my_j ,my_type, my_currStage;
  int *my_directionStatus;
  my_currStage = get_currStage();
  my_id = get_id();
  my_i = get_i();
  my_j = get_j();
  my_type = get_type();
  my_directionStatus = get_directionStatus();
  for (int i = 0 ; i < 8 ; i++ ){
    printf("%d", my_directionStatus[i]);
  }
  if (my_state == 1) {
    add_state_message(my_id, my_i, my_j, my_currStage, my_type, my_directionStatus);
  }
  return 0;
}

int read_states()
{
  int my_id, my_i, my_j;
  int *my_neighbors;
  int *my_directionStatus;
  int mes_id, mes_i, mes_j, mes_currStage, mes_type;
  int *mes_directionStatus;

  my_id = get_id();
  my_i = get_i();
  my_j = get_j();
  my_neighbors = get_neighbors();
  my_directionStatus = get_directionStatus();

  // //initialize the array
  // for (int i = 0; i <= 7; i++)
  //   my_neighbors[i] = 0;

  //Start Reading the message board
  START_STATE_MESSAGE_LOOP;

  if (state_message->id != my_id) {
    mes_id = state_message->id;
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

    if ((mes_i == my_i - 1) && (mes_j == my_j - 1)){
      mes_currStage = state_message->currStage;
      mes_directionStatus = state_message->directionStatus;
      my_neighbors[NW] = mes_type;
      if (mes_directionStatus[SE] == OUT){
        my_directionStatus[NW] = IN;
      }
    }
    else if ((mes_i == my_i - 1) && (mes_j == my_j)){
      mes_currStage = state_message->currStage;
      my_neighbors[N] = mes_type;
      if (mes_directionStatus[S] == OUT){
        my_directionStatus[N] = IN;
      }
    }
    else if ((mes_i == my_i - 1) && (mes_j == my_j + 1)){
      mes_currStage = state_message->currStage;
      my_neighbors[NE] = mes_type;
      if (mes_directionStatus[SW] == OUT){
        my_directionStatus[NE] = IN;
      }
    }
    else if ((mes_i == my_i) && (mes_j == my_j - 1)) {
      mes_currStage = state_message->currStage;
      my_neighbors[W] = mes_type;
      if (mes_directionStatus[E] == OUT){
        my_directionStatus[W] = IN;
      }
    }
    else if ((mes_i == my_i) && (mes_j == my_j + 1)) {
      mes_currStage = state_message->currStage;
      my_neighbors[E] = mes_type;
      if (mes_directionStatus[W] == OUT){
        my_directionStatus[E] = IN;
      }
    }
    else if ((mes_i == my_i + 1) && (mes_j == my_j - 1)) {
      mes_currStage = state_message->currStage;
      my_neighbors[SW] = mes_type;
      if (mes_directionStatus[NE] == OUT){
        my_directionStatus[SW] = IN;
      }
    }
    else if ((mes_i == my_i + 1) && (mes_j == my_j))
    {
      mes_currStage = state_message->currStage;
      my_neighbors[S] = mes_type;
      if (mes_directionStatus[N] == OUT){
        my_directionStatus[S] = IN;
      }
    }
    else if((mes_i == my_i + 1) && (mes_j == my_j + 1))) {
      mes_currStage = state_message->currStage;
      my_neighbors[SE] = mes_type;
      if (mes_directionStatus[NW] == OUT){
        my_directionStatus[SE] = IN;
      }
    }
  }

  FINISH_STATE_MESSAGE_LOOP;
  return 0;
}

int react()
{
  int my_id, my_i, my_j, my_type, my_currStage;
  int *my_neighbors;
  int *my_directionStatus;

  my_id = get_id();
  my_i = get_i();
  my_j = get_j();
  my_currStage = get_currStage();
  my_type = get_type();
  my_neighbors = get_neighbors();
  my_directionStatus = get_directionStatus();
  int count;
  if (my_type == INACTIVE){

    for (int i = 0 ; i <8 ; i++ ){
      my_directionStatus[i] = STOP;
    }
    my_currStage = DEACTIVATED;
  }

  if (my_type == NEUTRAL){
    for (int i =0 ; i< 8 ; i++){
      if (my_neighbors[i] == ACTIVE || my_neighbors[i] == NEUTRAL){

        if (my_directionStatus[i] == IN && my_directionStatus [7-i] = STOPPED)
        {
          my_directionStatus[7-i] =OUT;
        }
        else if (my_directionStatus[i] == IN && my_directionStatus [7-i]== IN)
        {
          my_directionStatus[i] = STOP;
        }
      }

      if (directionStatus[i] == STOP)
      {
          count++;
      }
    }
      // if there's nothing coming in it is stopped
      my_currStage = (count == 8)? DEACTIVATED:ENACTED;
    }
  if (my_type == ACTIVE){
    if (my_currStage == STOPPED){
      my_currStage = ENACTED;
      for (int i = 0; i< 8 ; i++){
        directionStatus[i] = OUT;
      }
    }
  }


  set_currStage(my_currStage);
  return 0;
}
