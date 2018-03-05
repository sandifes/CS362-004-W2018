/*
** SMITHY
** Using for testing:
** gcc -o cardtest4 -g  cardtest4.c dominion.c rngs.c -Wall -fpic -coverage -lm
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

    struct gameState G, originalG;
    int numPlayers = 2;
    int playerA = 0, playerB = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    int seed = 1000;
    int i;

    printf("       ***** CARD TEST: SMITHY *****\n");
    //Initialize the game state
    initializeGame(numPlayers, k, seed, &G);
    //Copy it to originalG
    memcpy(&originalG, &G, sizeof(struct gameState));
    //Call card effect on G
    cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
    //Check if 3 cards were drawn and 1 discarded
    assert(G.handCount[playerA] == originalG.handCount[playerA] + 2);
    printf("Player 0 plays smithy and draws 3 cards and discards the smithy...\n");
    printf("Hand count: %d\n", G.handCount[playerA]);
    printf("Expected hand count: %d\n", originalG.handCount[playerA] + 2);
    printf("\n");

    assert(G.deckCount[playerA] == originalG.deckCount[playerA] - 3);
    printf("Player 0 deck count before: %d\n", originalG.deckCount[playerA]);
    printf("Deck count after: %d\n", G.deckCount[playerA]);
    printf("Expected deck count after: %d\n", originalG.deckCount[playerA] - 3);
    printf("\n");

    assert(G.handCount[playerB] == originalG.handCount[playerB]);
    printf("Player 1 hand count should be unchanged...\n");
    printf("Hand count: %d\n", G.handCount[playerB]);
    printf("Expected hand count: %d\n", originalG.handCount[playerB]);
    printf("\n");

    assert(G.deckCount[playerB] == originalG.deckCount[playerB]);
    printf("Player 1 deck count should be unchanged... \n");
    printf("Deck count before: %d\n", originalG.deckCount[playerB]);
    printf("Deck count after: %d\n", G.deckCount[playerB]);

    printf("\nChecking Kingdom Card Piles...");
    for(i = 0; i < 10; i++)
    {
        assert(G.supplyCount[k[i]] == originalG.supplyCount[k[i]]);
    }

    printf("\n\nChecking Victory Card Piles...");

    assert(G.supplyCount[estate] == originalG.supplyCount[estate]);
    assert(G.supplyCount[duchy] == originalG.supplyCount[duchy]);
    assert(G.supplyCount[province] == originalG.supplyCount[province]);

	printf("\n\n***SMITHY TEST COMPLETED SUCCESSFULLY***\n\n");


	return 0;
}


