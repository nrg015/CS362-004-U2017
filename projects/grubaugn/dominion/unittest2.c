/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * testgainCard: unittest2.c dominion.o rngs.o
 *      gcc -o testgainCard -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i;
	int seed = 15;
	int numPlayer;
	int player, r; 
	int maxPlayer = 4;
	int toFlag;
	// toFlag = 0 : add to discard
	// toFlag = 1 : add to deck
	// toFlag = 2 : add to hand

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	int l[17] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, 
					gardens, mine, remodel, smithy, village, baron, great_hall};
	
	int notInPlay [10] = {minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
	
	char card[256];
	
	struct gameState G;
	struct gameState post;
	
	printf ("TESTING gainCard():\n");
	printf ("Testing regular operations\n");
	
	for (numPlayer = 2; numPlayer < 5; numPlayer++) {		//test 2 - 4 players
		for (toFlag = 0; toFlag < 3; toFlag++) {			//test add to discard/deck/hand 
			memset(&G, 23, sizeof(struct gameState));		//clear the game
			memset(&post, 23, sizeof(struct gameState));	//clear the post
			
#if (NOISY_TEST == 1)			
			printf("Initializing Game with %d players\n", numPlayer);
#endif

			r = initializeGame(numPlayer, k, seed, &G);		//new game
			
			memcpy(&post, &G, sizeof(struct gameState));	//Save G
			
			
			for (player = 0; player < numPlayer; player++) {	//go through each player in this instance
				
#if (NOISY_TEST == 1)
				printf("Testing Player %d\n", player);
#endif
				
				for (i = 0; i < 18; i++) {					//go through each card in l
					
#if (NOISY_TEST == 1)
					cardNumToName(l[i], &card);
					printf("   Testing Card: %s \n", card);
#endif
					
					gainCard(l[i], &post, toFlag, player);
					
#if (NOISY_TEST == 1)
					switch (toFlag) {
						case 0: 
							printf("   Dsicard Count: %d Expected: %d\n", post.discardCount[player], G.discardCount[player] + 1);
							break;
						case 1: 
							printf("   Deck Count:    %d Expected: %d\n", post.deckCount[player], G.deckCount[player] + 1);
							break;
						case 2: 
							printf("   Hand Count:    %d Expected: %d\n", post.handCount[player], G.handCount[player] + 1);
							break;
					}
					
					printf("   Supply Count:    %d Expected: %d\n", post.supplyCount[l[i]], G.supplyCount[l[i]] - 1);
#endif

					memcpy(&G, &post, sizeof(struct gameState));	//get ready for next player
				}
			}
		}			
	}
	
	printf("Testing empty Supply piles: \n");
	
	memset(&G, 23, sizeof(struct gameState));		//clear the game
	r = initializeGame(2, k, seed, &G);
	player = 0;
	toFlag = 2;
	
	for (i = 0; i < 18; i++) {
		
#if (NOISY_TEST == 1)
		cardNumToName(l[i], &card);
		printf("   Testing Card: %s \n", card);
#endif
		G.supplyCount[l[i]] = 0;
		
		printf("      Return Value: %d Expected: 0\n", gainCard(l[i], &G, toFlag, player));
	}
	
	printf("Testing cards not in play: \n");
	
	memset(&G, 23, sizeof(struct gameState));		//clear the game
	r = initializeGame(2, k, seed, &G);
	player = 0;
	toFlag = 2;
	
	for (i = 0; i < 11; i++) {
		
#if (NOISY_TEST == 1)
		cardNumToName(notInPlay[i], &card);
		printf("   Testing Card: %s \n", card);
#endif
		assert(gainCard(notInPlay[i], &G, toFlag, player) == -1);
	}
	
	printf("All tests conducted!\n");
	
	return 0;
}
