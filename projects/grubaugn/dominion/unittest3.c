/* -----------------------------------------------------------------------
 * Include the following lines in your makefile:
 *
 * testgetCost: unittest3.c dominion.o rngs.o
 *      gcc -o testgetCost -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"

#define NOISY_TEST 1

int main() {
	int i;
	int cost;
	int card[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, 
					gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, 
					ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
	
	int expect[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
	char name[256];
	
	printf ("TESTING getCost():\n");
	printf ("Testing regular operations\n");

	for(i = 0; i < 27; i++) {
		
		cardNumToName(card[i], &name);
	
#if (NOISY_TEST == 1)
		printf ("   Testing %s\n", name);
#endif	

		cost = getCost(card[i]);

#if (NOISY_TEST == 1)
		printf ("      Cost recieved: %d Expected: %d \n", cost, expect[i]);
#endif
	
	}
	
	printf ("Testing bad input\n");
	
	cost = getCost(256);
	
#if (NOISY_TEST == 1)	
	printf ("   Cost recieved: %d Expected: -1 \n", cost);
#endif

	printf("All tests Conducted!\n");
	return 0;
}
