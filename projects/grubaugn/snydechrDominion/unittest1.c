#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

int main()
{

	int i, j, k, l, initSuccess, numPlayers, numCards, numCurseCards, numCopper,numSilver, numGold, x, t;
	int supplyCountCount = 0;
	int numEmpty = 0;
	int seed = 1000;
	int kingCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};

	int gameOver = 0;
	int isGameOverResult;
	int successCounter = 0;
	int failureCounter = 0;
	char currentCard[50];
	struct gameState game;
	//loop curse which is dependent on the number of players 10 for 2, 20 for 3, 30 for 4
	//loop victory cards (estate, duchy, and province) depending on number of players, 8 for 2 and 12 for all else
	//loop treasurecards copper = 60 - (7*numPlayers), silver = 40, gold = 30
	//loop kingdom card combinations
	//	10 kingdom cards, 8 could have up to 10, and great_hall and gardens can have upto 8 and 12 for 2 and more players respectively
	//
	printf(">>>>>>    IS GAME OVER TESTING     <<<<<<\n");

	numPlayers = MAX_PLAYERS;
	for(numCurseCards = 0; numCurseCards < 2; numCurseCards++) //31 either has or doesnt have curse
	{	
		for(i = 1; i < 2; i++)
		{
		
			for(j = 0; j < 2; j++)	//victory loop if zero make sure end game returns a different value
			{
				for(numCopper = 0; numCopper < 2; numCopper++) //47
				{
					for(numSilver = 0; numSilver < 2; numSilver++) //41
					{
						for(numGold = 0; numGold < 2; numGold++) //31
						{
							memset(&game, 23, sizeof(struct gameState));	
							initSuccess = initializeGame(i, kingCards, seed, &game);
							game.supplyCount [i] = j;
							game.supplyCount[curse] = numCurseCards;
							game.supplyCount[copper] = numCopper;
							game.supplyCount[silver] = numSilver;
							game.supplyCount[gold] = numGold;

							for(k = adventurer; k <= treasure_map; k++)
							{
								if(game.supplyCount[k] == -1)
								{
									//do nothing this card is not used in this game
								}
								else if((game.supplyCount[k] != -1))
								{
									for(numCards = 0; numCards < 2; numCards++)
									{
										supplyCountCount = 0;
										game.supplyCount[k] = numCards;
										for(x = 0; x < 27; x++)	//27
										{
											if(game.supplyCount[x] == 0)
												supplyCountCount++;
										}
										if(supplyCountCount >= 3)
											gameOver = 1;
										else
											gameOver = 0;
										if(game.supplyCount[province] == 0)
											gameOver = 1;

										isGameOverResult = isGameOver(&game);

										if(isGameOverResult == gameOver)
										{
											printf("isGameOver(): PASS for ");
											for(t = 0; t < 27; t++)
											{
												strcpy(currentCard, cardName(t));
												printf(" %s quantity: %d, ", currentCard, game.supplyCount[t]);
												
											}
											printf("\n");
											successCounter++;
										}
										else
										{
											printf("isGameOver(): FAIL for ");
											for(t = 0; t < 27; t++)
											{
												strcpy(currentCard, cardName(t));
												printf(" %s quantity: %d, ", currentCard, game.supplyCount[t]);
												
											}
											printf("\n");

											failureCounter++;
										}

									}
								}
							}


						}
					}
				}

			}
		}
	}
	printf("Num Successes: %d \n", successCounter);
	printf("Num Failures: %d \n", failureCounter);
	printf("Num trials: %d \n", (successCounter + failureCounter));

	printf("%d PASSED test cases out of %d\n", successCounter, (successCounter + failureCounter));
	printf("%d FAILED test cases out of %d\n", failureCounter, (successCounter + failureCounter));
	if((failureCounter) == 0)
		printf(">>>>>>    TEST SUCCESS    <<<<<<\n");
	else
		printf(">>>>>>    TEST FAILURE    <<<<<<\n");

	
	printf(">>>>>>    IS GAME OVER TEST COMPLETE     <<<<<<\n");
	//printf("Press Enter to continue.... \n");
	//getchar();
	return 0;
}
