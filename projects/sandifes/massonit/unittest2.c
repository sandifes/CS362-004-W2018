/*
** shuffle()
**
** Using for testing:
** gcc -o unittest2 -g  unittest2.c dominion.c rngs.c -Wall -fpic -coverage -lm
**
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {

    struct gameState G;
    int numPlayers = 2;
    int playerA = 0;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    int seed = 1000;
    int i, x = 0;

    printf("         ***** Unit test of shuffle() *****\n");
    //Initialize the game state
    initializeGame(numPlayers, k, seed, &G);
    shuffle(playerA, &G);


    while(x < 3){
        //Compare decks before and after
        printf("\nTest number %d  ", x + 1);
        printf("(Estates = 1, Coppers = 4):");
        printf("\nDeck before...\n");
        for (i = 0; i < 10; i++) {
          printf("%d ", G.deck[playerA][i]);
        }

        shuffle(playerA, &G);

        printf("\nDeck after...\n");
        for (i = 0; i < 10; i++) {
          printf("%d ", G.deck[playerA][i]);
        }
        printf("\n");
        x++;
    }

    printf("\n\nAND, If the deck size is 0, shuffle should return -1\n ");
    G.deckCount[playerA] = 0;
    assert(shuffle(playerA, &G) == -1);


	printf("\n\n***shuffle() TEST COMPLETED SUCCESSFULLY***\n\n");


	return 0;
}


