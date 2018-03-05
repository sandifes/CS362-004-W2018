/*
** initializeGame()
**
** Using for testing:
** gcc -o unittest4 -g  unittest4.c dominion.c rngs.c -Wall -fpic -coverage -lm
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


    printf("         ***** Unit test of initializeGame() *****\n");

    //Initialize the game state
    initializeGame(numPlayers, k, seed, &G);

    printf("After initialization, Player 0 should have 5 cards in hand and 5 cards in the draw pile.\n");
    assert(G.deckCount[0] == 5);
    printf("Player 0 deck count: %d\n", G.deckCount[0]);
    assert(G.handCount[0] == 5);
    printf("Player 0 hand count: %d\n", G.handCount[0]);
    assert(G.discardCount[0] == 0);
    printf("Player 0 discard count: %d\n", G.discardCount[0]);

    printf("\nCheck supply counts...\n");

    assert(G.supplyCount[estate] == 8);
    assert(G.supplyCount[duchy] == 8);
    assert(G.supplyCount[province] == 8);

    assert(G.supplyCount[curse] == 10);

    assert(G.supplyCount[copper] == 60-(7*numPlayers));
    assert(G.supplyCount[silver] == 40);
    assert(G.supplyCount[gold] == 30);

    printf("\nSet the number of players to 10, function should return -1...\n");
    numPlayers = 10;
    assert(initializeGame(numPlayers, k, seed, &G) == -1);

    printf("\nSet two kingdom cards the same, function should return -1...\n");
    numPlayers = 2;
    int k1[10] = {smithy, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    assert(initializeGame(numPlayers, k1, seed, &G) == -1);




	printf("\n\n***initializeGame() TEST SUCCESSFULLY COMPLETED ***\n\n");


	return 0;
}


