/*
** SMITHY
** Using for random testing:
** gcc -o rtc1 -g  randomtestcard1.c dominion.c rngs.c -Wall -fpic -coverage -lm
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
int actionFail = 0;
int handCountFail = 0;
int deckCountFail = 0;

void checkSmithyCard(int p, struct gameState *post) {
    int a, b, ba, bb, d;
    int preHandCount, preDeckCount;
    int postHandCount, postDeckCount;
    int bonus = 0;

    // game state variable to manually act on the functions actions
    struct gameState pre;

    // copy the passed in game state to pre
    memcpy(&pre,post,sizeof(struct gameState));

    // call the card effect function with the smithy card
    a = cardEffect(smithy,0,0,0,post,0,&bonus);
    if(a != 0) {cardEffectFail++;}

    //card effect for smithy should draw three cards and discard one card
    b = drawCard(p, &pre);
    if(b == -1) {drawFail++;}
    ba = drawCard(p, &pre);
    if(ba == -1) {drawFail++;}
    bb = drawCard(p, &pre);
    if(bb == -1) {drawFail++;}

    //discard one card
    d = discardCard(0, p, &pre, 0);
    if(d == -1) {discardFail++;}

    preHandCount = pre.handCount[p];
    preDeckCount = pre.deckCount[p];

    postHandCount = post->handCount[p];
    postDeckCount = post->deckCount[p];

    if(preHandCount != postHandCount) {handCountFail++;}
    if(preDeckCount != postDeckCount) {deckCountFail++;}

}

int main () {

    int i, n, p;
    struct gameState G;
    srand(time(NULL));

    printf ("Random Testing: Smithy Card.\n");

    //Initialize and fill gameState with random values
    for (n = 0; n < 1000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        //Set gameState values in a valid range
        p = floor(Random() * MAX_PLAYERS);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        //set playedCardCount for discardCard()
        G.playedCardCount = floor(Random() * (MAX_DECK - 1));
        G.whoseTurn = p;
        G.numActions = 1;
        //We can now test the gameState on our card
        checkSmithyCard(p,&G);
    }

    printf("cardEffectFails: %d\n",cardEffectFail);
    printf("drawFails: %d\n",drawFail);
    printf("discardFails: %d\n",discardFail);
    printf("handCountFails: %d\n",handCountFail);
    printf("deckCountFails: %d\n",deckCountFail);

    return 0;
}



