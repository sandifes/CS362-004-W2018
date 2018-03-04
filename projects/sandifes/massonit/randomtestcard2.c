/*
** VILLAGE
** Using for random testing:
** gcc -o rtc2 -g  randomtestcard2.c dominion.c rngs.c -Wall -fpic -coverage -lm
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

void checkVillageCard(int p, struct gameState *post) {
    int a, b, c, d;
    int preHandCount, preDeckCount, preActionCount;
    int postHandCount, postDeckCount, postActionCount;
    int bonus = 0;

    // game state variable to manually act on the functions actions
    struct gameState pre;

    // copy the passed in game state to pre
    memcpy(&pre,post,sizeof(struct gameState));

    // call the card effect function with the village card
    a = cardEffect(village,0,0,0,post,0,&bonus);
    if(a != 0) {cardEffectFail++;}

    //card effect for village should draw one card, discard one card and gain two actions
    b = drawCard(p, &pre);
    if(b == -1) {drawFail++;}

    //gain two actions
    c = pre.numActions + 2;
    //discard one card
    d = discardCard(0, p, &pre, 0);
    if(d == -1) {discardFail++;}

    preHandCount = pre.handCount[p];
    preDeckCount = pre.deckCount[p];
    preActionCount = c;

    postHandCount = post->handCount[p];
    postDeckCount = post->deckCount[p];
    postActionCount = post->numActions;

    if(preActionCount != postActionCount) {actionFail++;}
    if(preHandCount != postHandCount) {handCountFail++;}
    if(preDeckCount != postDeckCount) {deckCountFail++;}

}

int main () {

    int i, n, p;
    struct gameState G;
    srand(time(NULL));

    printf ("Random Testing: Village Card.\n");

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
        checkVillageCard(p,&G);
    }

    printf("cardEffectFails: %d\n",cardEffectFail);
    printf("drawFails: %d\n",drawFail);
    printf("discardFails: %d\n",discardFail);
    printf("actionFails: %d\n",actionFail);
    printf("handCountFails: %d\n",handCountFail);
    printf("deckCountFails: %d\n",deckCountFail);

    return 0;
}



