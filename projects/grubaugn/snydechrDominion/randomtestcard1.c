/*
 * Include the following lines in your makefile:
 *
 * randomtestvillage: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestvillage -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 15;
    int numPlayers, player;
	struct gameState G, post;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	int l[17] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, 
					gardens, mine, remodel, smithy, village, baron, great_hall};
					
	int h[100];
	int d[100];
	
	srand(time(NULL));
	
	printf("Testing Card: Village\n");
	
	for (i = 0; i<100; i++) {
		h[i] = copper;
		d[i] = l[rand() % 17];
	}
	
	for (numPlayers = 2; numPlayers < 5; numPlayers++) {	//testing 2-4 player games
		memset(&G, 23, sizeof(struct gameState));		//clear the game
		memset(&post, 23, sizeof(struct gameState));	//clear the post
		
#if (NOISY_TEST == 1)			
		printf("Initializing Game with %d players\n", numPlayers);
#endif
		initializeGame(numPlayers, k, seed, &G);
	
		for(player = 0; player < numPlayers; player++) {		//testing each player in game

#if (NOISY_TEST == 1)		
			printf("Testing Player %d\n", player);
#endif		
			
			for (i = 0; i<100; i++) {
				if (i > 0) {
					h[i-1] = copper;
				}
				h[i] = village;
				memcpy(G.hand[player], h, sizeof(int) * 100); //set all cards to test hand h
				memcpy(G.deck[player], d, sizeof(int) * 100); //set all cards to test deck d
				G.deckCount[player] = 100;
				G.handCount[player] = 100;
				G.whoseTurn = player;
				G.numActions = (i + 1);
				handpos = i;
				
				memcpy(&post, &G, sizeof(struct gameState)); //save G
				
				cardEffect(village, choice1, choice2, choice3, &post, handpos, &bonus);
				
				drawCard(player, &G);
				discardCard(handpos, player, &G, 0);
				
#if (NOISY_TEST == 1)			
				printf("   Checking hand count: \n");
				printf("      Hand count: %d Expected: %d\n", post.handCount[player], G.handCount[player]);
				printf("   Checking deck count: \n");
				printf("      Deck count: %d Expected: %d\n", post.deckCount[player], G.deckCount[player]);
				printf("   Checking Actions count: \n");
				printf("      Actions count: %d Expected: %d\n", post.numActions, G.numActions +2);
#endif
				
			}
		}	
	}
	
	return 0;
}