#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

/*
Created By: Sam Schultz
Date: 5/5/2016
File Name: randomtestadventurer.c
Description:
Random tester for Adventurer post conditions.
Creates a random** game state for players and tests conditions for all players.
# of tests ran can be altered with the constant defined below.
*/

#define MAX_TEST_CASE  100

int testPass(){
	printf("Test Passed!\n");
	return 0;
}
 
 int testFail(){
 	printf("Test Failed!\n");
 	return 0;
 }

int main(int argc, char const *argv[])
{
	time_t seed = time(NULL);
	srand(seed);
	int boardCards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	
	int caseCounter = 0;


	//Random engine
	while(caseCounter < MAX_TEST_CASE){
		printf("TESTING ADVENTURER\tTEST #: %d\n", caseCounter);
		int numPlayers = rand() % 5;
		// random number of players within valid range
		if(numPlayers == 0 || numPlayers == 1){
			numPlayers = 2;
		}
		//Setting up the game state that will be altered each test case, also setting up
		//cpy state that will be tested against.
		struct gameState *state = newGame();
		struct gameState *cpyState = newGame();
		seed = (rand() % 1000) + 100;
		initializeGame(numPlayers, boardCards, seed, state);
		//-2 gurantees open slots for draw cards
		int numCards = (rand() % MAX_HAND) - 2;
		if(numCards <= 0){
			numCards = 1;
		}
		int i, j;
		//fills hand with adventureres, only need 1, rest can be arbitrary cards. Used same card because it was easy.
		for(i=0; i==numCards; i++){
			for(j=0; j < numPlayers; j++){
				state->hand[j][i] = adventurer;
			}
			
		}
		memcpy(cpyState, state, sizeof(struct gameState));
		//play for each player, and non player indexed condition tests.
		for(j=0; j < numPlayers; j++){
			playAdventurer(state);
			if(state->playedCards[0] == adventurer){
				testPass();
				printf("State->playedCards[0] is adventurer.\n");
			}
			else{
				testFail();
				printf("State->playedCards[0] != adventurer.\n");
			}
			if(state->coins > cpyState->coins){
				testPass();
				printf("State->coins > cpyState->coins.\n");
			}
			else{
				testFail();
				printf("State->coins !> cpyState->coins\n");
			}
			if(state->numActions == cpyState->numActions-1){
				testPass();
				printf("State->numActions == cpyState->numActions-1.\n");
			}
			else{
				testFail();
				printf("State->numActions != cpyState->numActions-1.\n");
			}

			endTurn(state);
			endTurn(cpyState);//for test case purposes
		}

		// Tests for all players consisting of player indexed conditions
		for(j=0; j < numPlayers; j++){
			if(state->handCount[j] == cpyState->handCount[j]+1){
				testPass();
				printf("Actual hand size = %d, Expected hand size = %d  \n", state->handCount[j], cpyState->handCount[j]+1);
			}
			else{
				testFail();
				printf("Actual hand size = %d, Expected hand size = %d  \n", state->handCount[j], cpyState->handCount[j]+1);
			}
			if(state->discardCount[j] > cpyState->discardCount[j]){
				testPass();
				printf("Expected played state discardCount to be larger than cpyState discardCount.\n");
			}
			else{
				testFail();
				printf("state->discardCount[j] <= cpyState->discardCount[j]\n");
			}

		}

		free(state);
		free(cpyState);
		caseCounter++;
	}

	return 0;
}