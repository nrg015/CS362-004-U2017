/*
 * Include the following lines in your makefile:
 *
 * cardtestadventurer: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtestadventurer -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    int i, ret;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 15;
    int numPlayers, player;
	struct gameState G, post;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	int h[5] = {adventurer, copper, copper, estate, estate};
	int d[5];
	int expect[6] = {copper, copper, copper, estate, estate, copper};

	printf("Testing Card: Adventurer\n");

	for (numPlayers = 2; numPlayers < 5; numPlayers++) {	//testing 2-4 player games
		memset(&G, 23, sizeof(struct gameState));		//clear the game
		memset(&post, 23, sizeof(struct gameState));	//clear the post
		
		for(i = 0; i < 3; i++) {		//testing each treasure card in deck
			
			switch (i) {
				case 0: 
				{
					d[0] = estate;
					d[1] = copper; 
					d[2] = curse;
					d[3] = copper;
					d[4] = gardens;
					expect[0] = copper;
					expect[5] = copper;
				}
				case 1: 
				{
					d[0] = mine;
					d[1] = silver;
					d[2] = province;
					d[3] = silver;
					d[4] = village;
					expect[0] = silver;
					expect[5] = silver;
				}		
				case 2: 
				{
					d[0] = duchy; 
					d[1] = gold;
					d[2] = minion;
					d[3] = gold;
					d[4] = cutpurse;
					expect[0] = gold; 
					expect[5] = gold;
				}
			}
			
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

				cardEffect(adventurer, choice1, choice2, choice3, &post, handpos, &bonus);
#if (NOISY_TEST == 1)			
				printf("   Checking hand count: \n");
				printf("      Hand count: %d Expected: %d\n", post.handCount[player], G.handCount[player]+1);		//hand count should still be 5 (+1 - 1)
				printf("      If this test doesn't work, then the next one won't either\n");
				printf("   Checking correct card was discarded: \n");
#endif
				
				ret = memcmp(post.hand[player], expect, sizeof(int) * post.handCount[player]);
				
#if (NOISY_TEST == 1)		
				printf("      Comparison: %d Expected: 0\n", ret);
#endif

			}
		}
	}
	
	printf("Testing one treasure card in deck\n");
	
	h[0] = adventurer;
	h[1] = copper;
	h[2] = copper;
	h[3] = estate; 
	h[4] = estate;
	d[0] = estate;
	d[1] = duchy; 
	d[2] = curse;
	d[3] = copper;
	d[4] = gardens;
	
	memset(&G, 23, sizeof(struct gameState));		//clear the game
	memset(&post, 23, sizeof(struct gameState));	//clear the post
	
#if (NOISY_TEST == 1)			
	printf("Initializing Game with %d players\n", numPlayers);
#endif

	initializeGame(numPlayers, k, seed, &G);
	
	memcpy(G.hand[player], h, sizeof(int) * 5); //set all cards to test hand h
	memcpy(G.deck[player], d, sizeof(int) * 5); //set all cards to test deck d
	G.deckCount[player] = 5;
	G.handCount[player] = 5;
	G.whoseTurn = player;		//smithy card expects that the player is playing it on their turn
	
	memcpy(&post, &G, sizeof(struct gameState)); //save G
	
	//cardEffect(adventurer, choice1, choice2, choice3, &post, handpos, &bonus); //this bug catches an infinite loop
	
#if (NOISY_TEST == 1)			
	printf("   Checking hand count: \n");
	printf("      Hand count: %d Expected: %d\n", post.handCount[player], G.handCount[player]+1);		//hand count should still be 5 (+1 - 1)
#endif

	printf("All tests Conducted!\n");

	return 0;
}