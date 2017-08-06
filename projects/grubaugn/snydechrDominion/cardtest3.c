/*
 * Include the following lines in your makefile:
 *
 * cardtestmine: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtestmine -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
    int i, j, c, ret;
    int handpos = 0, choice3 = 0, bonus = 0;
    int seed = 15;
    int numPlayers, player;
	struct gameState G, post;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	int l[17] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, 
					gardens, mine, remodel, smithy, village, baron, great_hall};
	
	int h[5] = {mine, copper, silver, gold, estate};
	int d[5] = {copper, copper, copper, copper, copper};
	int expect[5] = {mine, copper, silver, gold, estate};

	printf("Testing Card: Mine\n");
	printf("Testing regular operations\n");

	for (numPlayers = 2; numPlayers < 5; numPlayers++) {	//testing 2-4 player games
		memset(&G, 23, sizeof(struct gameState));		//clear the game
		memset(&post, 23, sizeof(struct gameState));	//clear the post
		
		for(j = 1; j < 4; j++) {			//copper, silver, gold
			
			for(i = 0; i < 17; i++) {		//test each card
			
				expect[0] = mine;
				expect[1] = copper;
				expect[2] = silver;
				expect[3] = gold;
				expect[4] = estate;
				c = 0;
				
				if((getCost(h[j]) + 3) <= getCost(l[i])) {
					expect[0] = l[i];
					expect[j] = estate;
					c = 1;						//recognize hand count change
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

					cardEffect(mine, j, l[i], choice3, &post, handpos, &bonus);
					
#if (NOISY_TEST == 1)			
					printf("   Checking hand count: \n");
					printf("      Hand count: %d Expected: %d\n", post.handCount[player], G.handCount[player] - c);		//hand count should still be 4 (+1 - 2)
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
	}
	
	printf("Testing nonexistant card\n");
	expect[0] = mine;
	expect[1] = copper;
	expect[2] = silver;
	expect[3] = gold;
	expect[4] = estate;
	c = 0;
	
	initializeGame(2, k, seed, &G);
	
	for(player = 0; player < 2; player++) {		//testing each player in game
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

		cardEffect(mine, 1, 256, choice3, &post, handpos, &bonus);
		
#if (NOISY_TEST == 1)			
		printf("   Checking hand count: \n");
		printf("      Hand count: %d Expected: %d\n", post.handCount[player], G.handCount[player] - c);		//hand count should still be 4 (+1 - 2)
		printf("      If this test doesn't work, then the next one won't either\n");
		printf("   Checking correct card was discarded: \n");
#endif

		ret = memcmp(post.hand[player], expect, sizeof(int) * post.handCount[player]);
		
#if (NOISY_TEST == 1)		
		printf("      Comparison: %d Expected: 0\n", ret);
#endif
	}
	
	printf("Testing non-treasure card\n");
	expect[0] = mine;
	expect[1] = copper;
	expect[2] = silver;
	expect[3] = gold;
	expect[4] = estate;
	c = 0;
	
	initializeGame(2, k, seed, &G);
	
	for(player = 0; player < 2; player++) {		//testing each player in game
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

		cardEffect(mine, 4, 256, choice3, &post, handpos, &bonus);
		
#if (NOISY_TEST == 1)			
		printf("   Checking hand count: \n");
		printf("      Hand count: %d Expected: %d\n", post.handCount[player], G.handCount[player] - c);		//hand count should still be 4 (+1 - 2)
		printf("      If this test doesn't work, then the next one won't either\n");
		printf("   Checking correct card was discarded: \n");
#endif

		ret = memcmp(post.hand[player], expect, sizeof(int) * post.handCount[player]);
		
#if (NOISY_TEST == 1)		
		printf("      Comparison: %d Expected: 0\n", ret);
#endif
	}
	
	printf("All tests Conducted!\n");

	return 0;
}