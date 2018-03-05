/*
** gainCard()
**
** Using for testing:
** gcc -o unittest1 -g  unittest1.c dominion.c rngs.c -Wall -fpic -coverage -lm
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

    printf("         ***** Unit test of gainCard() *****\n");
    //Initialize the game state
    initializeGame(numPlayers, k, seed, &G);

    G.supplyCount[copper] = 10;
    int coppers = 10;

    printf("Testing gainCard(): discard a copper...\n");
    int discard = G.discardCount[0];
    gainCard(copper, &G, 0, 0);  //Add copper to discard
    //check if one card was added to the discard
    assert(discard+1 == G.discardCount[0]);

    printf("Testing gainCard(): add a copper to deck...\n");
    int deck = G.deckCount[0];
    gainCard(copper, &G, 1, 0);  //Add copper to deck
    //check if one card was added to the deck
    assert(deck+1 == G.deckCount[0]);

    printf("Testing gainCard() add a copper to hand...\n");
    int hand = G.handCount[0];
    gainCard(copper, &G, 2, 0);  //Add copper to hand
    //check if one card was added to the hand
    assert(hand+1 == G.handCount[0]);

    printf("Check that copper supply count was reduced by 3...\n");
    printf("Copper count: %d\n", G.supplyCount[copper]);
    printf("Expected copper count: %d\n", coppers - 3);

    assert(G.supplyCount[copper] == 7);

    printf("Testing gainCard(): set copper supply to zero, should return -1...\n");
    G.supplyCount[copper] = 0;
    assert(gainCard(copper, &G, 0, 0) == -1);



	printf("\n\n***gainCard() TEST COMPLETED SUCCESSFULLY ***\n\n");


	return 0;
}


