/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * testdiscardCard: unittest1.c dominion.o rngs.o
 *      gcc -o testdiscardCard -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main() {
	int i, j;
	int seed = 15;
	int numPlayer = 2;
	int player, r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int h[5] = {copper, copper, copper, estate, estate};
	
	struct gameState G;
	struct gameState post;
	
	printf ("TESTING discardCard():\n");
	printf ("Testing regular operations\n");
	
	for (numPlayer = 2; numPlayer < 5; numPlayer++) {		//test 2 - 4 players
		memset(&G, 23, sizeof(struct gameState));		//clear the game
		memset(&post, 23, sizeof(struct gameState));	//clear the post
		
#if (NOISY_TEST == 1)			
		printf("Initializing Game with %d players\n", numPlayer);
#endif

		r = initializeGame(numPlayer, k, seed, &G);		//new game		
		
		for (player = 0; player < numPlayer; player++) {	//go through each player in this instance
			
#if (NOISY_TEST == 1)
			printf("Testing Player %d\n", player);
#endif
			
			for (i = 0; i < 5; i++) {					//test each hand position
#if (NOISY_TEST == 1)				
				printf("   Testing Hand Position %d \n", i);
#endif				
				memcpy(G.hand[player], h, sizeof(int) * 5); //set all cards to test hand h
				G.handCount[player] = 5;
				memcpy(&post, &G, sizeof(struct gameState));	//Save G
				
				discardCard(i, player, &post, 0);
				
				G.hand[player][i] = G.hand[player][ (G.handCount[player] - 1)];
				G.hand[player][G.handCount[player] - 1] = -1;
				G.handCount[player]--;
				G.playedCardCount++;
				
				assert(post.playedCardCount == G.playedCardCount);
				
				for(j = 0; j < 4; j++) {
					assert(post.hand[player][j] == G.hand[player][j]);
				}
				
			}
		}			
	}
	
	printf("Testing one card in hand\n");
	
	memset(&G, 23, sizeof(struct gameState));		//clear the game
	memset(&post, 23, sizeof(struct gameState));	//clear the post
	r = initializeGame(2, k, seed, &G);
	
	G.hand[1][0] = copper;
	G.handCount[1] = 1;
	
	memcpy(&post, &G, sizeof(struct gameState));	//Save G
	
	discardCard(0, 1, &post, 0);
	
	G.handCount[1]--;
	
	assert(post.handCount[1] == G.handCount[1]);
	
	printf("Testing card is trashed (not played)\n");
	
	memset(&G, 23, sizeof(struct gameState));		//clear the game
	memset(&post, 23, sizeof(struct gameState));	//clear the post
	r = initializeGame(2, k, seed, &G);
	
	G.hand[1][0] = copper;
	G.handCount[1] = 1;
	
	memcpy(&post, &G, sizeof(struct gameState));	//Save G
	
	discardCard(0, 1, &post, 1);
	
	G.handCount[1]--;
	
	assert(post.handCount[1] == G.handCount[1]);
	assert(post.playedCardCount == 0);	
	
	printf("All tests Successful!\n");
	return 0;
}
