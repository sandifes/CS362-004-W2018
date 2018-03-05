/*
** ADVENTURER
** Using for testing:
** gcc -o cardtest1 -g  cardtest1.c dominion.c rngs.c -Wall -fpic -coverage -lm
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
    int treasureTotal = 0;
    int originalTreasureTotal = 0;
    int myCard;

    printf("       ***** CARD TEST: ADVENTURER *****\n");
    //Initialize the game state
    initializeGame(numPlayers, k, seed, &G);
    //Copu it to originalG
    memcpy(&originalG, &G, sizeof(struct gameState));
    //Call card effect on G
    cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
    //Check if 3 cards were drawn and 1 discarded
    assert(G.handCount[playerA] == originalG.handCount[playerA] + 2);
    printf("Player 0 plays adventurer and gains 2 cards...\n");
    printf("Hand count: %d\n", G.handCount[playerA]);
    printf("Expected hand count: %d\n", originalG.handCount[playerA] + 2);
    printf("\n");

    printf("Checking that Player 0 gained 2 treasure cards...\n");
    //Treasure total
    for(i = 0; i < G.handCount[playerA]; i++)
    {
        myCard = G.hand[playerA][i];
        if(myCard == copper || myCard == silver || myCard == gold){
            treasureTotal++;
        }
    }
    //Treasure total before playing adventurer
    for(i = 0; i < originalG.handCount[playerA]; i++)
    {
        myCard = originalG.hand[playerA][i];
        if(myCard == copper || myCard == silver || myCard == gold){
            originalTreasureTotal++;
        }
    }

    //Check that player 0 hand now has 2 more treasure cards
    assert(treasureTotal == originalTreasureTotal + 2);
    printf("\nOriginal treasure: %d\n", originalTreasureTotal);
    printf("Treasure after playing adventurer: %d\n", treasureTotal);
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

	printf("\n\n***ADVENTURER TEST COMPLETED SUCCESSFULLY***\n\n");


	return 0;
}


