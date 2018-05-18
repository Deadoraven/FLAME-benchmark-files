#include "header.h"
#include "finance_agent_header.h"
#include "cluster_agent_header.h"

//three different type
enum financialEntity{
    CLUSTER,FIRM,BANK
};

//8 different direction
enum directions{
    NW,N,NE,W,E,SW,S,SE
};

//write clusters on clusters board
int write_clusters()
{
    //write them on messageboard
    add_clusters_message(X, Y, HASBANK);
    return 0;
}

//write all agents on the agents board
int write_agents()
{
    if (TYPE == BANK) add_banks_message(I, J, MONEY);

    else if (TYPE == FIRM) add_firms_message(I, J, MONEY);

    return 0;

}

int set_has_bank(){

    int mes_i, mes_j, mes_money;

    //Start looping through message board
    START_BANKS_MESSAGE_LOOP
    mes_i = banks_message->i;
    mes_j = banks_message->j;
    mes_money = banks_message->money;

    if (X == mes_i && Y == mes_j && mes_money > 0){
        set_hasbank(BANK);
    }
    FINISH_BANKS_MESSAGE_LOOP
    return 0 ;
}

int find_firms(){

    int mes_i, mes_j, mes_money;

    START_FIRMS_MESSAGE_LOOP
    mes_i = firms_message->i;
    mes_j = firms_message->j;

    mes_money = firms_message->money;

    if (X == mes_i && Y == mes_j && mes_money < 0 && HASBANK != BANK){
        set_hasbank (FIRM);
    }
    FINISH_FIRMS_MESSAGE_LOOP
    return 0;
}

//reading from message board
int read_clusters()
{
    int mes_i, mes_j, mes_hasbank;;

    START_CLUSTERS_MESSAGE_LOOP
    mes_i = clusters_message->x;
    mes_j = clusters_message->y;


    //if it is does it have a bank?
    if ((mes_i == X - 1) && (mes_j == Y - 1)){

        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[NW] = mes_hasbank;

    }
    else if ((mes_i == X - 1) && (mes_j == Y)){
        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[N] = mes_hasbank;
    }
    else if ((mes_i == X - 1) && (mes_j == Y + 1)){
        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[NE] = mes_hasbank;
    }
    else if ((mes_i == X) && (mes_j == Y - 1)) {
        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[W] = mes_hasbank;
    }
    else if ((mes_i == X) && (mes_j == Y + 1)) {
        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[E] = mes_hasbank;
    }
    else if ((mes_i == X + 1) && (mes_j == Y - 1)) {
        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[SW] = mes_hasbank;
    }
    else if ((mes_i == X + 1) && (mes_j == Y)) {
        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[S] = mes_hasbank;
    }
    else if ((mes_i == X + 1) && (mes_j == Y + 1)) {
        mes_hasbank = clusters_message->hasbank;
        NEIGHBORS[SE] = mes_hasbank;
    }
    FINISH_CLUSTERS_MESSAGE_LOOP

    return 0;
}

int bank_dest(){

    if (HASBANK == BANK){
        int count, numDest, newDest;
        count = 0;

        for (int i =0 ; i < 8 ; i++ ){
            if (NEIGHBORS[i] == FIRM){
                FINANCES.array[count] = i;
                count ++;
            }
        }
        if(count > 0){
            numDest = rand() % count;
            newDest = FINANCES.array[numDest];
            DESTINATION = newDest;
        }
    }
    else DESTINATION = -1;

    add_destinations_message(X, Y, DESTINATION);
    return 0;
}

int update(){

    int mes_i, mes_j, mes_money;

    if(MONEY < 0){// we have a FIRM

        START_BANKS_MESSAGE_LOOP

        mes_i = banks_message->i;
        mes_j = banks_message->j;
        mes_money = banks_message->money;

        if(I == mes_i && J == mes_j && mes_money > 0){
            if (MONEY + mes_money <= 0)
            {
                MONEY += mes_money;
            }
            else {
                MONEY = 0;
            }
        }
        FINISH_BANKS_MESSAGE_LOOP
    }

    else if(MONEY > 0){//there's a bank with some money
        START_FIRMS_MESSAGE_LOOP

        mes_i = firms_message->i;
        mes_j = firms_message->j;
        mes_money = firms_message->money;

        if(I == mes_i && J == mes_j && mes_money < 0){
            if (MONEY + mes_money >= 0)
            {
                MONEY += mes_money;
            }
            else {
                MONEY = 0;
            }
        }
        FINISH_FIRMS_MESSAGE_LOOP
    }
    return 0;
}


int move(){

    if (MONEY > 0){//do we need this bank to move at all?
        int mes_i, mes_j, mes_destination;

        START_DESTINATIONS_MESSAGE_LOOP
        mes_i = clusters_message->x;
        mes_j = clusters_message->y;


        if (I == mes_i && J == mes_j){

            mes_destination = clusters_message->destination;
            switch (mes_destination){
                case NW:
                    I = I - 1;
                    J = J - 1;
                    break;
                case N:
                    I = (I - 1);
                    J = (J);
                    break;
                case NE:
                    I = (I - 1);
                    J = (J + 1);
                    break;
                case W:
                    I = (I);
                    J = (J - 1);
                    break;
                case E:
                    I = (I );
                    J = (J + 1);
                    break;
                case SW:
                    I = (I + 1);
                    J = (J - 1);
                    break;
                case S:
                    I = (I + 1);
                    J = (J);
                    break;
                case SE:
                    I = (I + 1);
                    J = (J + 1);
                    break;
            }
        }
        FINISH_DESTINATIONS_MESSAGE_LOOP
    }
    return 0;
}
