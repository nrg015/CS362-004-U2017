/*
 * cardtest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtestsmithy: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtestsmithy -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int ret;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 15;
    int numPlayers, player;
	struct gameState G, post;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	int h[5] = {smithy, copper, copper, estate, estate};
	int d[5] = {copper, copper, copper, copper, copper};
	int expect[7] = {copper, copper, copper, estate, estate, copper, copper};

	printf("Testing Card: Smithy\n");

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
			//cards can be shuffled differently, so drawn cards might not be the same for each instance of the game
			//thus all the cards in the deck were made coppers.	
			memcpy(G.hand[player], h, sizeof(int) * 5); //set all cards to test hand h
			memcpy(G.deck[player], d, sizeof(int) * 5); //set all cards to test deck d
			G.deckCount[player] = 5;
			G.handCount[player] = 5;
			G.whoseTurn = player;		//smithy card expects that the player is playing it on their turn
			
			memcpy(&post, &G, sizeof(struct gameState)); //save G

			cardEffect(smithy, choice1, choice2, choice3, &post, handpos, &bonus);
#if (NOISY_TEST == 1)			
			printf("   Checking hand count: \n");
#endif			
			G.handCount[player] += 2;		//Adds three cards and discards smithy = +2 cards in hand
			
#if (NOISY_TEST == 1)		
			printf("      Hand count: %d Expected: %d\n", post.handCount[player], G.handCount[player]);
			printf("      If this test doesn't work, then the next one won't either\n");
			printf("   Checking correct card was discarded: \n");
#endif
			
			ret = memcmp(post.hand[player], expect, sizeof(int) * post.handCount[player]);
			
#if (NOISY_TEST == 1)		
			printf("      Comparison: %d Expected: 0\n", ret);
#endif

		}
	}
		printf("All tests Conducted!\n");

	return 0;
}


