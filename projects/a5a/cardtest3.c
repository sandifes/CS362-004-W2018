/*
** GREAT HALL
** Using for testing:
** gcc -o cardtest3 -g  cardtest3.c dominion.c rngs.c -Wall -fpic -coverage -lm
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

    printf("       ***** CARD TEST: GREAT HALL *****\n");
    //Initialize the game state
    initializeGame(numPlayers, k, seed, &G);
    //Copy it to originalG
    memcpy(&originalG, &G, sizeof(struct gameState));
    //Call card effect on G
    cardEffect(great_hall, choice1, choice2, choice3, &G, handpos, &bonus);
    //Check if 1 card was drawn and 1 discarded
    assert(G.handCount[playerA] == originalG.handCount[playerA]);
    printf("Player 0 plays great hall and draws 1 card, gains 1 action, and discards the great hall.\n");
    printf("When the great hall is first added to the player's cards, the player also gains one victory point...\n\n");
    printf("Check if 1 card was drawn and 1 discarded...\n");
    printf("Player 0 Hand count: %d\n", G.handCount[playerA]);
    printf("Expected hand count: %d\n", originalG.handCount[playerA]);
    printf("\n");

    assert(G.deckCount[playerA] == originalG.deckCount[playerA] - 1);
    printf("Player 0 deck count before: %d\n", originalG.deckCount[playerA]);
    printf("Deck count after: %d\n", G.deckCount[playerA]);
    printf("Expected deck count after: %d\n", originalG.deckCount[playerA] - 1);
    printf("\n");

    assert(G.numActions == originalG.numActions + 1);
    printf("Number of actions before: %d\n", originalG.numActions);
    printf("Number of actions after: %d\n", G.numActions);
    printf("Expected number of actions after: %d\n", originalG.numActions + 1);
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


    printf("\n\nAdd great hall to player 0 hand and check victory points...\n");
    int scoreBefore = scoreFor(playerA, &G);

    G.hand[playerA][0] = great_hall;

    int scoreAfter = scoreFor(playerA, &G);
    printf("Victory points before adding great hall: %d\n", scoreBefore);
    printf("Victory points after adding great hall: %d\n", scoreAfter);
    printf("Expected victory points after adding great hall: %d\n", scoreBefore + 1);
    assert(scoreAfter == scoreBefore + 1);


    printf("\n\nChecking Kingdom Card Piles...");
    for(i = 0; i < 10; i++)
    {
        assert(G.supplyCount[k[i]] == originalG.supplyCount[k[i]]);
    }

    printf("\n\nChecking Victory Card Piles...");

    assert(G.supplyCount[estate] == originalG.supplyCount[estate]);
    assert(G.supplyCount[duchy] == originalG.supplyCount[duchy]);
    assert(G.supplyCount[province] == originalG.supplyCount[province]);




	printf("\n\n***GREAT HALL TEST COMPLETED SUCCESSFULLY***\n\n");


	return 0;
}


