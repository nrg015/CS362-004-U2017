#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main()
{
	//sweep num players
	//players
	//all cards possible 27 for each player combo
	//sweep handcount and index
	//assign which players turn it is for the game
	int handIDX, player, numPlayers, handCountidx, currentCard;
	struct gameState game;
	int numTrials = 0;
	int numPass = 0;
	int initSuccess = 0;
	int seed = 1000;
	int kingCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy};
	
	printf(">>>>>>    HAND CARD TESTING    <<<<<<\n");
	for(numPlayers = 2; numPlayers < (MAX_PLAYERS +1); numPlayers++)
	{
		for(player = 0; player < numPlayers; player++)
		{
			for(handCountidx = 0; handCountidx < 5; handCountidx++)
			{
				for(currentCard = 0; currentCard < 27; currentCard++)
				{
					memset(&game, 23, sizeof(struct gameState));
					initSuccess = initializeGame(numPlayers, kingCards, seed, &game);

					game.handCount[player] = handCountidx;
					game.whoseTurn = player;
					game.hand[player][handIDX] = currentCard;
					numTrials++;
					if(currentCard == handCard(handIDX, &game))
					{
						//PASS
						printf("handCard(): PASS  Hand Index: %d, Current Card: %s, Whose Turn: %d\n ", handIDX, cardName(currentCard), game.whoseTurn);
						numPass++;
					}
					else
					{
						//FAIL
						printf("handCard(): FAIL  Hand Index: %d, Current Card: %s, Whose Turn: %d\n ", handIDX, cardName(currentCard), game.whoseTurn);

					}
				}
			}
		}
	}
	
	printf("%d PASSED test cases out of %d\n", numPass, numTrials);
	printf("%d FAILED test cases out of %d\n", numTrials-numPass, numTrials);
	if((numTrials-numPass) == 0)
		printf(">>>>>>    TEST SUCCESS    <<<<<<\n");
	else
		printf(">>>>>>    TEST FAILURE    <<<<<<\n");

	printf(">>>>>>    HAND CARD TEST COMPLETE    <<<<<<\n");
	return 0;
}
