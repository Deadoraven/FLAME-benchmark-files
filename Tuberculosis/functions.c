#include "header.h"
#include "agents_agent_header.h"
#include "bacteria_agent_header.h"

int_array emptyX, emptyY;
int totalInfected = 0;

//three different type
enum status{
    CLEAN,INFECTED
};

//8 different direction
enum directions{
    NW,N,NE,W,E,SW,S,SE
};

/*******************************************************
 ******** All functions related to Bacteria ************
 *******************************************************/

/**
 * writing bacterias on MB
 * @return 0
 */
int write_bacteria()
{
    init_int_array(&emptyX);
    init_int_array(&emptyY);
    //write on messageboard
    add_bacteria_message(I, J, ALIVE, STATE, HAS_CLEANING_AGENTS, HAS_INFECTING_AGENTS);
    return 0;
}


/**
 * read bacteria and set totalInfected
 * @return 0
 */
int read_bacteria()
{
    int mes_i, mes_j, mes_state;

    START_BACTERIA_MESSAGE_LOOP

      mes_i = bacteria_message->i;
      mes_j = bacteria_message->j;

      //if it is does it have a bank?
      if (((mes_i == I - 1) && (mes_j == J - 1)) ||
          ((mes_i == I - 1) && (mes_j == J)) ||
          ((mes_i == I - 1) && (mes_j == J + 1)) ||
          ((mes_i == I) && (mes_j == J - 1)) ||
          ((mes_i == I) && (mes_j == J + 1)) ||
          ((mes_i == I + 1) && (mes_j == J - 1)) ||
          ((mes_i == I + 1) && (mes_j == J)) ||
          ((mes_i == I + 1) && (mes_j == J + 1))) {
            mes_state = bacteria_message->state;
            if (mes_state == INFECTED) totalInfected += 1;
      }

    FINISH_BACTERIA_MESSAGE_LOOP

    return 0;
}
/**
 * setting the next generation of bacterias
 * @return 0
 */
int disperseBacteria()
{
   if (totalInfected > 0) STATE = INFECTED;

   return 0;
}

/**
 * find agent on each bacteria
 * @return 0
 */
int find_agents(){

    int mes_i, mes_j, mes_state;

    //Start looping through message board
    START_AGENTS_MESSAGE_LOOP

      mes_i = agents_message->x;
      mes_j = agents_message->y;

      if (((mes_i == I - 1) && (mes_j == J - 1)) ||
          ((mes_i == I - 1) && (mes_j == J)) ||
          ((mes_i == I - 1) && (mes_j == J + 1)) ||
          ((mes_i == I) && (mes_j == J - 1)) ||
          ((mes_i == I) && (mes_j == J + 1)) ||
          ((mes_i == I + 1) && (mes_j == J - 1)) ||
          ((mes_i == I + 1) && (mes_j == J)) ||
          ((mes_i == I + 1) && (mes_j == J + 1))) {
            mes_state = agents_message->a_state;
            if (mes_state == INFECTED) HAS_INFECTING_AGENTS += 1;
            else if(mes_state == CLEAN) HAS_CLEANING_AGENTS += 1;
      }

    FINISH_AGENTS_MESSAGE_LOOP

    return 0 ;
}

/**
 * disperseAgentInfluence
 * @return 0
 */
int disperseAgentInfluence()
{

  if (HAS_CLEANING_AGENTS > 0) STATE = CLEAN;
  else if(HAS_INFECTING_AGENTS > 0) STATE = INFECTED;

  return 0;

}


/*******************************************************
 ********** All functions related to Agents ************
 *******************************************************/
/**
 * writing all agents on messageboard
 * @return [description]
 */
int write_agents()
{
  add_agents_message(X, Y, ENERGY, A_STATE);
  return 0;
}

/**
 * kill all agents that ran out of energy
 * @return 1 for dead agents return 0 for alive agents
 */
int killAgent()
{
  if (ENERGY <= 0) return 1;//remove agent from simulation
  else return 0;
}

/**
 * update energy of agents
 * @return 0
 */
int update(){

    ENERGY--;
    return 0;
}

/**
 * move agents to next place randomly
 * @return 0
 */

int move(){

  int mes_i, mes_j,mes_cleaning, mes_infecting, count;

  count = 0;

  //finding empty places
  START_BACTERIA_MESSAGE_LOOP
    mes_i = bacteria_message->i;
    mes_j = bacteria_message->j;
    mes_cleaning = bacteria_message->has_cleaning_agents;
    mes_infecting = bacteria_message->has_infecting_agents;

    if (((mes_i == X - 1) && (mes_j == Y - 1)) ||
        ((mes_i == X - 1) && (mes_j == Y)) ||
        ((mes_i == X - 1) && (mes_j == Y + 1)) ||
        ((mes_i == X) && (mes_j == Y - 1)) ||
        ((mes_i == X) && (mes_j == Y + 1)) ||
        ((mes_i == X + 1) && (mes_j == Y - 1)) ||
        ((mes_i == X + 1) && (mes_j == Y)) ||
        ((mes_i == X + 1) && (mes_j == Y + 1))) {
          if( mes_cleaning == 0 && mes_infecting == 0){
            add_int(&emptyX,mes_i);
            add_int(&emptyY,mes_j);
          }
    }
  FINISH_BACTERIA_MESSAGE_LOOP

  //randomly select the new destination for agents
  if (emptyX.size > 0){

    int newDirection = rand()% emptyX.size;
    X = emptyX.array[newDirection];
    Y = emptyY.array[newDirection];

  }
  reset_int_array(&emptyX);
  reset_int_array(&emptyY);
  return 0;
}
