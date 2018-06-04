#include "header.h"
#include "agents_agent_header.h"
#include "bacteria_agent_header.h"

int_array EMPTY;

//three different type
enum status{
    CLEAN,INFECTED
};

//8 different direction
enum directions{
    NW,N,NE,W,E,SW,S,SE
};

//write clusters on clusters board
int write_bacteria()
{
    //write them on messageboard
    add_bacteria_message(I, J, ALIVE, STATE, HAS_AGENTS);
    return 0;
}

//reading from message board
int read_bacteria()
{
    int mes_i, mes_j, mes_state;

    START_BACTERIA_MESSAGE_LOOP

      mes_i = bacteria_message->i;
      mes_j = bacteria_message->j;

      //if it is does it have a bank?
      if ((mes_i == I - 1) && (mes_j == J - 1)){

          mes_state = bacteria_message->state;
          NEIGHBORS[NW] = mes_state;

      }
      else if ((mes_i == I - 1) && (mes_j == J)){
          mes_state = bacteria_message->state;
          NEIGHBORS[N] = mes_state;
      }
      else if ((mes_i == I - 1) && (mes_j == J + 1)){
          mes_state = bacteria_message->state;
          NEIGHBORS[NE] = mes_state;
      }
      else if ((mes_i == I) && (mes_j == J - 1)) {
          mes_state = bacteria_message->state;
          NEIGHBORS[W] = mes_state;
      }
      else if ((mes_i == I) && (mes_j == J + 1)) {
          mes_state = bacteria_message->state;
          NEIGHBORS[E] = mes_state;
      }
      else if ((mes_i == I + 1) && (mes_j == J - 1)) {
          mes_state = bacteria_message->state;
          NEIGHBORS[SW] = mes_state;
      }
      else if ((mes_i == I + 1) && (mes_j == J)) {
          mes_state = bacteria_message->state;
          NEIGHBORS[S] = mes_state;
      }
      else if ((mes_i == I + 1) && (mes_j == J + 1)) {
          mes_state = bacteria_message->state;
          NEIGHBORS[SE] = mes_state;
      }
    FINISH_BACTERIA_MESSAGE_LOOP

    return 0;
}

int disperseBacteria()
{
   int totalInfected = 0;
   for (int i= 0; i< 8; i++){
     totalInfected += NEIGHBORS[i];
   }

   if (totalInfected > 0) STATE = INFECTED;

   return 0;
}

int disperseAgentInfluence()
{
  int totalInfectionAgents = 0;
  int totalCleaningAgents = 0;

  for (int i = 0; i < 8 ; i++){
    if (NEIGHBORS[i] == INFECTED) totalInfectionAgents += 1;
    else if (NEIGHBORS [i] == CLEAN) totalCleaningAgents += 1;
  }

  if (totalCleaningAgents > 0) STATE = CLEAN;
  else if(totalInfectionAgents > 0) STATE = INFECTED;

  return 0;

}

int find_agents(){

    int mes_i, mes_j;

    //Start looping through message board
    START_AGENTS_MESSAGE_LOOP

      mes_i = agents_message->x;
      mes_j = agents_message->y;

      if (I == mes_i && J == mes_j){
        HAS_AGENTS += 1 ;
      }
    FINISH_AGENTS_MESSAGE_LOOP

    return 0 ;
}

int killAgent()
{
  if (ENERGY <= 0) return 1;//remove agent from simulation
  else return 0;
}

//write all agents on the agents board
int write_agents()
{
  add_agents_message(X, Y, ENERGY, A_STATE);
  return 0;
}

int update(){

    ENERGY--;
    return 0;
}


int move(){

  int mes_i, mes_j,mes_has_agents, count;

  count = 0;

  //finding empty places
  START_BACTERIA_MESSAGE_LOOP

    mes_i = bacteria_message->i;
    mes_j = bacteria_message->j;
    mes_has_agents = bacteria_message->has_agents;

    //if it is does it have a bank?
    if ((mes_i == X - 1) && (mes_j == Y - 1) && mes_has_agents == 0){
        EMPTY.array[count] = NW;
        count++;
    }
    else if ((mes_i == X - 1) && (mes_j == Y) && mes_has_agents == 0){
        EMPTY.array[count] = N;
        count++;
    }
    else if ((mes_i == X - 1) && (mes_j == Y + 1) && mes_has_agents == 0){
        EMPTY.array[count] = NE;
        count++;
    }
    else if ((mes_i == X) && (mes_j == Y - 1) && mes_has_agents == 0) {
        EMPTY.array[count] = W;
        count++;
    }
    else if ((mes_i == X) && (mes_j == Y + 1) && mes_has_agents == 0) {
        EMPTY.array[count] = E;
        count++;
    }
    else if ((mes_i == X + 1) && (mes_j == Y - 1) && mes_has_agents == 0) {
        EMPTY.array[count] = SW;
        count++;
    }
    else if ((mes_i == X + 1) && (mes_j == Y) && mes_has_agents == 0) {
        EMPTY.array[count] = S;
        count++;
    }
    else if ((mes_i == X + 1) && (mes_j == Y + 1) && mes_has_agents == 0) {
        EMPTY.array[count] = SE;
        count++;
    }
  FINISH_BACTERIA_MESSAGE_LOOP

  //randomly select the new destination for agents
  if (EMPTY.size > 0){

    int newDirection = rand()% EMPTY.size;
    int newDest = EMPTY.array[newDirection];
    switch (newDest){
        case NW:
            X = X - 1;
            Y = Y - 1;
            break;
        case N:
            X = (X - 1);
            Y = (Y);
            break;
        case NE:
            X = (X - 1);
            Y = (Y + 1);
            break;
        case W:
            X = (X);
            Y = (Y - 1);
            break;
        case E:
            X = (X );
            Y = (Y + 1);
            break;
        case SW:
            X = (X + 1);
            Y = (Y - 1);
            break;
        case S:
            X = (X + 1);
            Y = (Y);
            break;
        case SE:
            X = (X + 1);
            Y = (Y + 1);
            break;
    }
  }
  return 0;
}
