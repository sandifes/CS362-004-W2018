/*
** isGameOver()
**
** Using for testing:
** gcc -o unittest3 -g  unittest3.c dominion.c rngs.c -Wall -fpic -coverage -lm
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
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    int seed = 1000;


    printf("         ***** Unit test of isGameOver() *****\n");
    printf("\nisGameOver() returns a value of 1 if true\n");
    //Initialize the game state
    initializeGame(numPlayers, k, seed, &G);

    //Check game over conditions:
    //When we rn out of province cards or any 3 supply piles
    printf("\nFirst check that initialize has populated all supply counts...\n");
    assert(isGameOver(&G) ==  0); //check if return value is 0

    printf("\nTest by setting the number of province cards to zero...\n");
    G.supplyCount[province] = 0;
    assert(isGameOver(&G) ==  1); //check if return value is 1
    G.supplyCount[province] = 1;

    printf("\nTest by setting any 3 supply piles to empty...\n");
    G.supplyCount[estate] = 0;
    G.supplyCount[copper] = 0;
    G.supplyCount[smithy] = 0;
    assert(isGameOver(&G) ==  1); //check if return value is 1

	printf("\n\n***isGameOver() TEST SUCCESSFULLY COMPLETED ***\n\n");


	return 0;
}


