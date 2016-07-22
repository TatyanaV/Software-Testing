#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#include "dominion.h"
#define MAX_TESTS 25

//REFFERENCES
/*
https://github.com/CS362-Winter-2016/cs362w16_phamju/blob/8dff85e2d0541d248c228967afe2f2ec89b8e032/dominion/playMe.c
https://github.com/aburasali/cs362sp16/blob/6e08b61c7e573a9268fc278ebd298d0fdef5360a/projects/castigla/dominion/randomtestcard.c
https://github.com/CS362-Winter-2016/cs362w16_eilertsm/blob/205a6d7501f695c3d9719a089bf13635020da6b2/dominion/randomtestadventurer.c
https://github.com/CS362-Winter-2016/cs362w16_klindtwj/blob/master/dominion/randomtestadventurer.c
https://github.com/CS362-Winter-2016/cs362w16_phamju/blob/8dff85e2d0541d248c228967afe2f2ec89b8e032/dominion/playMe.c
https://github.com/aburasali/cs362sp16/blob/6e08b61c7e573a9268fc278ebd298d0fdef5360a/projects/tungr/dominion/randomtestadventurer.c

*/

int main(){

	//make new game object
	struct gameState* G = newGame();
	//list of cards was taken from
    //used the following reffence https://github.com/CS362-Winter-2016/cs362w16_phamju/blob/8dff85e2d0541d248c228967afe2f2ec89b8e032/dominion/playMe.c
  	char *cardNames[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast",
  								"gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute",
  								"ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
    //cards that will be used to initialize the game
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    int players, player, randomSeed, choice1, choice2, choice3, choice4, handPos, checkTreasure, countTreasurebefore, countTreasureafter, handOriginal;
	//seeding the rand() function
	time_t t;
	srand((unsigned) time(&t));  //seeding the rand() function
	printf("ADVENTURE CARD RANDOME TESTING\n\n");
    int w;
	for(w = 0; w < MAX_TESTS; w++){
        countTreasurebefore = 0;
        countTreasureafter = 0;
        printf("\n\nTest #: %d\n", w);
        //random number of player from 2 to 4
		players = (rand() % 3) + 2;
		//randomize the seed
		randomSeed = (rand() % 17) + 1;
	    //initialize the game
        //int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,  struct gameState *state) {
		initializeGame(players, k, randomSeed, G);
        //loop through all the players to ranomize their decks
		for(player = 0; player < players; player++){
            printf("\nPlayer #: %d\n", player);
			//the test the card, I will run the following function:
			//if ( cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus) < 0 )
            choice1 = rand() % 2;
			choice2 = rand() % 2;
			choice3 = rand() % 2;
			handPos = rand() % 4;
			//randomize the deck count
			G->deckCount[player] = rand() % MAX_DECK;
			//randomize discardcount
            G->discardCount[player] = rand() % MAX_DECK;
            //randomize handcount
            handOriginal = G->handCount[player] = rand() % MAX_HAND;
            //randomize the card content for all 3 decks
            int i;
            //assign random cards in the deck
            for(i = 0; i < G->deckCount[player]; i++){
				G->deck[player][i] = rand() % 27;
            };

			//assign random cards in the discard pile
			for(i = 0; i < G->discardCount[player]; i++){
				G->discard[player][i] = rand() % 27;

			}
			//assign random cards in the hand pile
			for(i = 0; i < G->handCount[player]; i++){
				G->hand[player][i] = rand() % 27;
					if(G->hand[player][i] == copper || G->hand[player][i] == silver || G->hand[player][i] == gold){
					countTreasurebefore++;
				}
			}

			//play the adventure card
			cardEffect(adventurer, choice1, choice2, choice3, G, handPos, 0);
			/*
			    Adventure is an action card with the terminal action that digs for treasure cards in the deck. The palayer
                draws cards from their deck until they get 2 treasure cards. The treasure cards are added to the deck of the
                player and the rest of the cards that were revealed are placed in the discard pile. In case the deck is empty
                before the player find 2 treasure cards, the discarded cards are shuffled and placed on the deck.
            */

            //according to the description above, the treasure count should increase +2
			//check number of treasures after the adventure card was played
			for(i = 0; i < G->handCount[player]; i++){
				if(G->hand[player][i] == copper || G->hand[player][i] == silver || G->hand[player][i]== gold){
					countTreasureafter++;
				}
			}
            printf("Treasures Before: %d\n", countTreasurebefore);
			printf("Treasures After: %d\n", countTreasureafter);
			if(countTreasureafter == countTreasurebefore + 2){
				printf("	TREASURE COUNT TEST PASSED\n");
			} else {
				printf("	TREASURE COUNT TEST FAILED\n");
			}
            //according to the description of the adventure card above, the handcount should increase +2
            printf("Handcount Before: %d\n", handOriginal);
			printf("Handcount After: %d\n", G->handCount[player]);

          if(handOriginal + 2 == G->handCount[player]){
				printf("	HAND COUNT TEST PASSED\n");
			} else {
				printf("	HANDCOUNT TEST FAILED\n");
			}
		}


	}

	printf("RANDOM TESTING OF ADVENTURE CARD IS COMPLETE\n");
	return 0;
}
