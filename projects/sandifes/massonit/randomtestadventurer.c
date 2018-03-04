/*
** Adventurer
** Using for random testing:
** gcc -o rtca -g  randomtestadventurer.c dominion.c rngs.c -Wall -fpic -coverage -lm
**
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int cardEffectFail = 0;
int drawFail = 0;
int discardFail = 0;
int handCountFail = 0;
int treasureFail = 0;

void checkAdventurerCard(int p, struct gameState *post) {
    int a, b, c, i, myCard;
    int preHandCount, postHandCount;
    int treasureTotal = 0;
    int originalTreasureTotal = 0;

    // game state variable to manually act on the functions actions
    struct gameState pre;

    // copy the passed in game state to pre
    memcpy(&pre,post,sizeof(struct gameState));
    int bonus = 0;

    // call the card effect function with the adventurer card
    a = cardEffect(adventurer,0,0,0,post,0,&bonus);

    if(a != 0) {cardEffectFail++;}

    //Treasure total
    for(i = 0; i < post->handCount[p]; i++)
    {
        myCard = post->hand[p][i];
        if(myCard == copper || myCard == silver || myCard == gold){
            treasureTotal++;
        }
    }
    //Treasure total before playing adventurer
    for(i = 0; i < pre.handCount[p]; i++)
    {
        myCard = pre.hand[p][i];
        if(myCard == copper || myCard == silver || myCard == gold){
            originalTreasureTotal++;
        }
    }

    //Check that player hand now has 2 more treasure cards
    if(treasureTotal != originalTreasureTotal + 2) {treasureFail++;}

    //card effect for adventurer: Net effect is 2 cards are drawn
    b = drawCard(p, &pre);
    if(b == -1) {drawFail++;}

    c = drawCard(p, &pre);
    if(c == -1) {drawFail++;}

    preHandCount = pre.handCount[p];
    postHandCount = post->handCount[p];

    if(preHandCount != postHandCount) {handCountFail++;}
}

int main () {

    int n, p, pCount;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    struct gameState G;
    srand(time(NULL));
    printf ("Random Testing: Adventurer Card.\n");

    //Initialize and fill gameState with random values
    for (n = 1; n < 1000; n++) {
/*        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
*/
        pCount = rand()%3+2;
        //Set gameState values in a valid range
        p = floor(Random() * MAX_PLAYERS);

        initializeGame(pCount, k, 1000, &G);

        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        //set playedCardCount for discardCard()
        G.playedCardCount = floor(Random() * (MAX_DECK - 1));
        G.whoseTurn = p;
        G.numActions = 1;
        //We can now test the gameState on our card
        checkAdventurerCard(p,&G);
    }

    printf("cardEffectFails: %d\n",cardEffectFail);
    printf("drawFails: %d\n",drawFail);
    printf("discardFails: %d\n",discardFail);
    printf("handCountFails: %d\n",handCountFail);
    printf("treasureFails: %d\n",treasureFail);

    return 0;
}



