#include "header.h"
#include "person_agent_header.h"

int MAX_PEOPLE = 484;
int_array degreeFriends;
/**
 * receiving a value and check if that value already exists in the array
 * if not exists add it to array of degreeFriends
 * @param  value = id of a friend
 * @return       0
 */
int remove_dup(int value)
{
    int duplicate = 0;
    for (int i = 0; i < degreeFriends.size; i++){
        if (degreeFriends.array[i] == value) duplicate = 1;
    }
    if(!duplicate) add_int(&degreeFriends, value);
    return 0;
}

/**
 * create the connections Static array
 * and write all agents on the message board.
 * @return 0
 */
int write_friends(){

  int connections[MAX_PEOPLE];
  init_int_array(&degreeFriends);
  for (int i = 0; i < MAX_PEOPLE ; i++){
    if (i < FRIENDS.size) connections[i] = FRIENDS.array[i];

    else connections[i] = -1;
  }

  add_social_message(ID,connections);
  return 0;
}

/**
 * find one degree away from friends
 * @return 0
 */
int find_degrees(){


  int  mes_id;
  int * mes_friends;

  START_SOCIAL_MESSAGE_LOOP //adding first and second degree

    mes_id = social_message->id;

    for (int i = 0 ; i < FRIENDS.size; i++ ){

      if(mes_id == FRIENDS.array[i]){

        mes_friends = social_message->connections;

        for(int i = 0; i < MAX_PEOPLE; i++){
          if(mes_friends[i] != -1){
             remove_dup(mes_friends[i]);

          }
        }
      }
    }
  FINISH_SOCIAL_MESSAGE_LOOP

  for (int i =0 ; i < FRIENDS.size ; i++ ) {
    remove_dup(FRIENDS.array[i]);//1st degree
  }
  // printf("Degree of freedom is 2: ");
  // for (int i =0 ; i< degreeFriends.size; i++){
  // printf("%d ",degreeFriends.array[i]);
  reset_int_array(&FRIENDS);
  init_int_array(&FRIENDS);
  for (int i= 0; i < degreeFriends.size; i ++ ){
    add_int(&FRIENDS, degreeFriends.array[i]);
  }
  reset_int_array(&degreeFriends);

  return 0;
  // printf("\n");

}
