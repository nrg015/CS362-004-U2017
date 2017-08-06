#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <string.h>

int main()
{
	//there are 27 cards so we need 2 columns by 27 corresponding with the card and the expected cost
	int cardCostLUT[28][2] = {	curse,			0,
								estate, 		2,
								duchy,			5,
								province,		8,
								copper,			0,
								silver,			3,
								gold,			6,
								adventurer,		6,
								council_room,	5,
								feast,			4,
								gardens,		4,
								mine,			5,
								remodel,		4,
								smithy,			4,
								village,		3,
								baron,			4,
								great_hall,		3,
								minion,			5,
								steward,		3,
								tribute,		5,
								ambassador,		3,
								cutpurse,		4,
								embargo,		2,
								outpost,		5,
								salvager,		4,
								sea_hag,		4,
								treasure_map,	4,
								27,				-1,
								};

	//string cardCostTestResults[27][2];
	//int cardCostTestResults[27][2];
	int cardIndex = curse;
	char currentCard[50];
	int numPass = 0;
	int numFail = 0;
	printf(">>>>>>    CARD COST TESTING    <<<<<<\n");
	for(cardIndex = curse; cardIndex < (treasure_map + 2); cardIndex++)
	{

		//currentCard = cardName(cardIndex);
		strcpy(currentCard, cardName(cardIndex));
		//cardCostResults[cardIndex][0] = currentCard;
		if(cardCostLUT[cardIndex][1] == getCost(cardIndex))
		{
			//cardCostResults[cardIndex][1] = ;
			numPass++;
			printf("getCardCost(): PASS for card %s\n", currentCard);
		}
		else
		{
			//cardCostResults[cardIndex][1] = "FAILED";
			numFail++;
			printf("getCardCost(): FAIL for card %s\n", currentCard);
		}

	}
	
	printf("%d PASSED test cases out of 28 \n", numPass);
	printf("%d FAILED test cases out of 28 \n", 28 - numPass);

	if((28 - numPass) == 0)
		printf(">>>>>>    TEST SUCCESS    <<<<<<\n");
	else
		printf(">>>>>>    TEST FAILURE    <<<<<<\n");


	printf(">>>>>>    CARD COST TEST COMPLETE    <<<<<<\n");
	//save the results to the .out file
	return 0;
}
