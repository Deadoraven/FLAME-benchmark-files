#include "header.h"
#include "person_agent_header.h"

int MAX_PEOPLE = 22*22;
int_array degreeFriends;

int remove_dup(int value)
{
    int duplicate = 0;
    for (int i = 0; i < degreeFriends.size; i++){
        if (degreeFriends.array[i] == value) duplicate = 1;
    }
    if(!duplicate) add_int(&degreeFriends, value);
    return 0;
}

int write_friends(){

  int mes_id, count;
  int connections[MAX_PEOPLE];
  init_int_array(&FRIENDS);
  for (int i = 0; i < MAX_PEOPLE ; i++){
    if (i < FRIENDS.size) connections[i] = FRIENDS.array[i];
    else connections[i] = -1;
  }

  add_social_message(ID,connections);
  return 0;
}

int find_degrees(){

  int  mes_id_deg2, mes_id_deg3, mes_id_deg4;
  int * mes_friends_deg2;
  int * mes_friends_deg3;
  int * mes_friends_deg4;


  START_SOCIAL_MESSAGE_LOOP //adding first and second degree

    mes_id_deg2 = social_message->id;

    for (int i = 0 ; i < MAX_PEOPLE; i++ ){

      if(mes_id_deg2 == FRIENDS[i]){

        mes_friends_deg2 = social_message->connections;

        START_SOCIAL_MESSAGE_LOOP // adding third degree

          mes_id_deg3 = social_message->id;

          for (int i = 0 ; i < MAX_PEOPLE; i++ ){

            if(mes_id_deg3 == mes_friends_deg2[i]){

              mes_friends_deg3 = social_message->connections;

              START_SOCIAL_MESSAGE_LOOP // looping for the fourth degree

                mes_id_deg4 = social_message->id;

                for (int i = 0 ; i < MAX_PEOPLE; i++ ){

                  if(mes_id_deg4 == mes_friends_deg3[i]){

                    mes_friends_deg4 = social_message->connections;

                    for(int i = 0; i < MAX_PEOPLE; i++){

                      if(mes_friends_deg4[i] != -1){

                         remove_dup(mes_friends_deg4[i]);
                      }
                    }
                  }
                }
              FINISH_SOCIAL_MESSAGE_LOOP // 4th

              for(int i = 0; i < MAX_PEOPLE; i++){

                if(mes_friends_deg3[i] != -1){

                   remove_dup(mes_friends[i]);
                }
              }
            }
          }
        FINISH_SOCIAL_MESSAGE_LOOP

        for(int i = 0; i < MAX_PEOPLE; i++){
          if(mes_friends_deg2[i] != -1){
             remove_dup(mes_friends_deg2[i]);
          }
        }
      }
    }
  FINISH_SOCIAL_MESSAGE_LOOP

  for (int i =0 ; i < MAX_PEOPLE ; i++ ) if(FRIENDS[i] != -1) remove_dup(FRIENDS[i]);//1st degree

  // printf("Degree of freedom is 2: ");
  // for (int i =0 ; i< degreeFriends.size; i++){
  //   printf("%d ",degreeFriends.array[i]);
  }
  // printf("\n");
  reset_int_array(&degreeFriends);

  return 0;
}
