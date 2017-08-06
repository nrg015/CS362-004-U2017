#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main()
{
	//500 max hand
	//4 max players
	//47 maximum coppers
	//41 maximum silvers
	//31 maximum golds
	//15 maximum bonus
	
	struct gameState game;
	int numCoppers, numSilvers, numGold, handIDX, bonus, coinSum, player, i;
	int numPass = 0;
	int numTrials = 0;
	int initSuccess = 0;
	int numPlayers, handCountidx;
	int seed = 1000;
	int kingCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};
	printf(">>>>>>    UPDATE COINS TESTING    <<<<<<\n");
	for(numPlayers = 2; numPlayers < (MAX_PLAYERS + 1); numPlayers++)//(MAX_PLAYERS + 1)
	{
		for(player = 0; player < numPlayers; player++)//numPlayers
		{
			for(handCountidx = 0; handCountidx < 5; handCountidx++)//0 ->MAX_HAND
			{
				
				for(bonus = 0; bonus < 4; bonus++)
				{
					for(numCoppers = 0; numCoppers < handCountidx; numCoppers++)
					{
						for(numSilvers = 0; numSilvers < (handCountidx - numCoppers); numSilvers++)
						{
							numGold = handCountidx - numCoppers - numSilvers;
							coinSum = (numCoppers * 1) + (numSilvers * 2) + (numGold * 3) + bonus;
							memset(&game, 23, sizeof(struct gameState));	
							initSuccess = initializeGame(numPlayers, kingCards, seed, &game);
							
							//set other game parameters here
							game.handCount[player] = handCountidx;
							for(handIDX = 0; handIDX < handCountidx; handIDX++)
							{
								//building the hand combinations
								if(handIDX < numCoppers)
								{
									game.hand[player][handIDX] = copper;
								//	coinSum += 1;
								}
								else if((handIDX >= numCoppers) && (handIDX < (numCoppers + numSilvers)))
								{
									game.hand[player][handIDX] = silver;
								}
								else if(handIDX >= (numCoppers + numSilvers))
								{
									game.hand[player][handIDX] = gold;
								}
							}
							//run the thing here
							//
							numTrials++;
							updateCoins(player, &game, bonus);
							if(coinSum == game.coins)
							{
								//PASS
								printf("updateCoins(): PASS  num players: %d, player: %d, hand size: %d, bonus: %d, numCoppers: %d, numSilvers: %d, numGold: %d \n", numPlayers, player, handCountidx, bonus, numCoppers, numSilvers, numGold);
								numPass++;
							}
							else
							{
								//FAIL
								printf("updateCoins(): FAIL  num players: %d, player: %d, hand size: %d, bonus: %d, numCoppers: %d, numSilvers: %d, numGold: %d \n", numPlayers, player, handCountidx, bonus, numCoppers, numSilvers, numGold);
							}
						}
					}
				}
			}
		}
	}
	printf("%d PASSED test cases out of %d\n", numPass, numTrials);
	printf("%d FAILED test cases out of %d\n", numTrials - numPass, numTrials);
	if((numTrials-numPass) == 0)
		printf(">>>>>>    TEST SUCCESS    <<<<<<\n");
	else
		printf(">>>>>>    TEST FAILURE    <<<<<<\n");
		
	printf(">>>>>>    UPDATE COINS TEST COMPLETE    <<<<<<\n");

	return 0;
}
