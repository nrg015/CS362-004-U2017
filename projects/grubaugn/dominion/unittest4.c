/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * testisGameOver: unittest4.c dominion.o rngs.o
 *      gcc -o testisGameOver -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int i, j, l, m;
	int seed = 15;
	int numPlayer;
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	int end; //captures isGameOver() return value

	struct gameState G;
	
	printf ("TESTING isGameOver():\n");
	
	for (numPlayer = 2; numPlayer < 5; numPlayer++) {		//test 2 - 4 players
		memset(&G, 23, sizeof(struct gameState));		//clear the game
		
#if (NOISY_TEST == 1)			
		printf("Initializing Game with %d players\n", numPlayer);
#endif
		r = initializeGame(numPlayer, k, seed, &G);		//new game
		
#if (NOISY_TEST == 1)		
		printf("   Testing start of game\n");
#endif

		end = isGameOver(&G);

#if (NOISY_TEST == 1)		
		printf("      Game Over? %d Expected: 0\n", end);
#endif	
		

#if (NOISY_TEST == 1)
		printf("   Testing empty Province pile\n");
#endif
		j = G.supplyCount[province];		//save province supply
		G.supplyCount[province] = 0;
		end = isGameOver(&G);
		
#if (NOISY_TEST == 1)		
		printf("      Game Over? %d Expected: 1\n", end);
#endif

#if (NOISY_TEST == 1)
		printf("   Testing one card in Province pile\n");
#endif
		G.supplyCount[province] = 1;
		end = isGameOver(&G);
		
#if (NOISY_TEST == 1)		
		printf("      Game Over? %d Expected: 0\n", end);
#endif

		G.supplyCount[province] = j;		//restore province supply

#if (NOISY_TEST == 1)
		printf("   Testing 3 empty supply piles\n");
#endif
	
		for(i = 0; i < 8; i++) {
			j = G.supplyCount[k[i]];		//save supply piles
			l = G.supplyCount[k[i+1]];
			m = G.supplyCount[k[i+2]];
			
			G.supplyCount[k[i]] = 0;		//set to 0
			G.supplyCount[k[i+1]] = 0;
			G.supplyCount[k[i+2]] = 0;
			
			end = isGameOver(&G);
			
#if (NOISY_TEST == 1)		
		printf("      Game Over? %d Expected: 1\n", end);
#endif

			G.supplyCount[k[i]] = j;		//restore supply piles
			G.supplyCount[k[i+1]] = l;
			G.supplyCount[k[i+2]] = m;
		}
		
#if (NOISY_TEST == 1)
		printf("   Testing 2 empty supply piles\n");
#endif
	
		for(i = 0; i < 9; i++) {
			j = G.supplyCount[k[i]];		//save supply piles
			l = G.supplyCount[k[i+1]];
			
			G.supplyCount[k[i]] = 0;		//set to 0
			G.supplyCount[k[i+1]] = 0;
			
			end = isGameOver(&G);
			
#if (NOISY_TEST == 1)		
		printf("      Game Over? %d Expected: 0\n", end);
#endif

			G.supplyCount[k[i]] = j;		//restore supply piles
			G.supplyCount[k[i+1]] = l;
		}
	}

	printf("All tests Conducted!\n");
	return 0;
}
