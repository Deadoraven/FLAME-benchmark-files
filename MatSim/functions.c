#include <stdio.h>
#include "header.h"
#include "car_agent_header.h"
#include "place_agent_header.h"

int INFINIT = 999;
int VERTICES = 30;
int matrix [30][30] =
{
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
};

/*******************************************************
 ******** All functions related to Cars ****************
 *******************************************************/


/**
 * write all the cars and their current and final destination on MB
 * @return 0
 */
int write_cars()
{
  add_cars_message(C_ID, CURRENT_PLACE,FINAL_DEST);
  return 0;
}

int find_path()
{
  if(!PATH_FOUND){
    init_int_array(&PATH);
    int distance[VERTICES],pred[VERTICES],visited[VERTICES];
    int count, mindistance, nextnode, i, j;

    //pred[] stores the predecessor of each node
      //count gives the number of nodes seen so far
      for(i=0 ; i<VERTICES; i++)
          for(j=0; j<VERTICES; j++)
              if(matrix[i][j] == 0)
                  matrix[i][j]=INFINIT;



      //initialize pred[],distance[] and visited[]
      for(i=0;i < VERTICES;i++)
      {

        distance[i] = matrix[CURRENT_PLACE-1][i];
        pred[i] = CURRENT_PLACE-1;
        visited[i] = 0;
      }

      distance[CURRENT_PLACE-1]=0;
      visited[CURRENT_PLACE-1]=1;
      count=1;

      while(count < VERTICES-1)
      {
          mindistance=INFINIT;
          //nextnode gives the node at minimum distance
          for(i=0;i<VERTICES;i++)
              if(distance[i] < mindistance&& !visited[i])
              {
                  mindistance = distance[i];

                  // printf("\n 1st D: %d",distance[i]);
                  nextnode = i ;
              }

              //check if a better path exists through nextnode
              visited[nextnode]=1;
              for(i=0;i < VERTICES; i++)
                  if(!visited[i])
                      if(mindistance + matrix[nextnode][i] < distance[i])
                      {
                          distance[i]= mindistance + matrix[nextnode][i];
                          // printf(" 2nd D: %d\n",distance[i]);
                          pred[i]=nextnode;
                      }
          count++;
      }

      //print the path and distance of each node
      for(i=0;i< VERTICES;i++)
          if(i == FINAL_DEST - 1 )
          {
              printf("\nDistance of node %d = %d", i+1, distance[i]);
              printf("\nPath=%d",i+1);


              j=i;

              while (j != CURRENT_PLACE-1){
                j = pred[j];
                printf("<-%d",j+1);
                if (j != CURRENT_PLACE-1) add_int(&PATH,j+1);
              }
              add_int(&PATH,i+1);
      }

    PATH_FOUND = 1;
  }
  return 0;
}


/**
 * check if the next destination has room and then move to new location
 * @return 0
 */
int move()
{
  int nextDest, mes_id, mes_cars;
  nextDest = PATH.array[0];

  START_PLACES_MESSAGE_LOOP
    mes_id = places_message->p_id;
    if (nextDest == mes_id){
      mes_cars = places_message->num_cars;
      if (mes_cars < 10){
        CURRENT_PLACE = nextDest;
        remove_int(&PATH,0);
      }

    }

  FINISH_PLACES_MESSAGE_LOOP

  return 0;
}

/**
 * check if the car has arrived to its final destination
 * @return 1 if it has arrived and remove the agent
 * @return 0 if still moving
 */
//TODO at the begining or in the end?
int arrived()
{
 if (CURRENT_PLACE == FINAL_DEST) return 1;
 return 0;
}


/*******************************************************
 ******** All functions related to Places **************
 *******************************************************/
/**
 * find all the cars written/moved in each place
 *
 * @return [description]
 */
int get_cars()
{
  //assuming each turn at least one car will move
  //every turn set number of cars to zero
  NUM_CARS = 0;

  int mes_currPlace;
  START_CARS_MESSAGE_LOOP
    mes_currPlace = cars_message->current_place;
    if (mes_currPlace == P_ID){
      NUM_CARS ++;
    }
  FINISH_CARS_MESSAGE_LOOP
  return 0;
}

int write_places()
{
  add_places_message(P_ID,NUM_CARS);
  return 0;
}

int create_matrix()
{
  if(!MATRIX_CREATED){
    for (int i = 0; i < VERTICES; i++){
      matrix[P_ID-1][i] = DESTINATIONS[i];
    }

    MATRIX_CREATED = 1;
  }
  return 0;
}
