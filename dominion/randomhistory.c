randomhistory.c
Tatyana Vlaskin
CS 362 - Assignment #4
Software Engineering II

randomtestadventurer.c Testing and randomtestcard.c Testing

INSTRUCTIONS HOW TO RUN FILES: make randomtestcard.out randomtestadventurer.out

DETAILING ABOUT TESTING:

*********randomtestadventurer.c Testing:

The following parameters are randomized for each run of the test:
* Number of players: rand() % (MAX_PLAYERS - 2) + 2;
* seed: randomSeed = (rand() % 17) + 1;
*** the above mentioned variables were used in initializeGame(players, k, randomSeed, G); function
* choice1 = rand() % 2;
* choice2 = rand() % 2;
* choice3 = rand() % 2;
* handPos = rand() % 4;
* G->deckCount[player] = rand() % MAX_DECK;
* G->discardCount[player] = rand() % MAX_DECK;
* G->handCount[player] = rand() % MAX_HAND;
* cards in the deck - see code
* cards in the hand - see code
* cards in the discard - see code

			    Adventure is an action card with the terminal action that digs for treasure cards in the deck. The palayer
                draws cards from their deck until they get 2 treasure cards. The treasure cards are added to the deck of the
                player and the rest of the cards that were revealed are placed in the discard pile. In case the deck is empty
                before the player find 2 treasure cards, the discarded cards are shuffled and placed on the deck

Thus when the card is played by the player, the player will gain 2 treasure cards and the count of the cards [G->handCount[player]]
will increase +2. I have run 25 tests of all the players in the game [ so if randomly 4 players have been chosen - i have done 25*4 = 100 tests].
The goal of the testing was to make sure that each player, who players the advenature card, gets 2 treasure cards and hand count will increase +2.
Coverage information:
File 'randomtestadventurer.c'
Lines executed:97.83% of 46
Branches executed:100.00% of 28
Taken at least once:96.43% of 28
Calls executed:96.55% of 29

A bug that I have introduced in the code for the adventure card was revealed:
	Bug: if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) to the
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn != gold)
What this bug does - no matter what card is drawn, it is accepted as a treasure card.
However, it was also observed that the hand count was failing on multiple ocasions.
Initially it was not making any sense because there was no bug in the dominon.c code
that should mess up the hand count after the adventure card is played.
However, after looking at the randomtestadventure.c, I have realized that when I randomly assign cards at the begining of the game:
    			//assign random cards in the hand pile
			for(i = 0; i < G->handCount[player]; i++){
				G->hand[player][i] = rand() % 27;
					if(G->hand[player][i] == copper || G->hand[player][i] == silver || G->hand[player][i] == gold){
					countTreasurebefore++;
				}
			}

some of the players randomly will not get an adventure card, so when they try to play it, there is no effect because, they just do
not have an adventure card to play, so the test fails.  This is the fault of the random test that I have designed. When I design radnom testing
for the next card, I will use the same code to randomly assign cards in the players hands and I will make sure that the user has that specific card that
I want to test.




*********randomtestcard.c Testing:
    For the second card, I have decided to test SMITHY card.

The following factors are randomized for each run of the test:
* Number of players: rand() % (MAX_PLAYERS - 2) + 2;
* seed: randomSeed = (rand() % 17) + 1;
*** the above mentioned variable were used in initializeGame(players, k, randomSeed, G); function
* choice1 = rand() % 2;
* choice2 = rand() % 2;
* choice3 = rand() % 2;
* handPos = rand() % 4;
* G->deckCount[player] = rand() % MAX_DECK;
* G->discardCount[player] = rand() % MAX_DECK;
* G->handCount[player] = rand() % MAX_HAND;
* cards in the deck - see code
* cards in the hand - see code
* cards in the discard - see code


                Smithy is a terminal card, meaning it provides no +Action. This card lets the user to draw 3 additional cards.
                The implementation of the card is a simple for loop that calles the drawCard(currentPlayer, state) method 3 times.
                After 3 cards are drawn, the discardCard(handPos, currentPlayer, state, 0) method is called to discard the smithy
                card to the discarded pile. So after the Smithy card is played, it is expted that the player will get handcount increased +2.

Thus when the card is played by the player, the count of the cards [G->handCount[player]]
will increase +2. I have run 25 tests of all the players in the game [ so if randomly 4 players have been chosen - i have done 25*4 = 100 tests].
The goal of the testing was to make sure that each player, who players the smithy card will get handcount increase +2.
Coverage information:
File 'randomtestcard.c'
Lines executed:97.14% of 35
Branches executed:100.00% of 12
Taken at least once:91.67% of 12
Calls executed:96.00% of 25

A bug that I have introduced in the 1st Assignment was revealed:
    Bug: in for statement the loop is started at 1 instead of 0
The handcount was increasing +1 and not +2, which made total sense.
Howerver, it was observed that the hand count of some players was not changing at all and this did not make any sense.
The issue that I have mentioned in the descritpion of the adventure card has been resolved. I made sure that when the cards
in the hands are randomly assigned, each player gets the smithy card using this code:
			//assign random cards in the hand pile
			for(i = 0; i < G->handCount[player]-1; i++){
				G->hand[player][i] = rand() % 27;
			}
			//i want to make sure that the player has at least one smithy card
            G->hand[player][G->handCount[player]] = smithy;

However, in each game [ after the game was inilialized] only the first user was getting an expected effect of the smithy card with the
bug, the other players did not get a change in hand count at all. So I decided to display the cards that each player was holding before
playing smithy card, just to make sure that the player really had the smithy card. This was accoplished using the following code:
            for(i = 0; i < G->handCount[player]; i++){
				printf(" %s, ", cardNames[G->hand[player][i]]);
			}
It was confirmed that the player had a smithy card, but somehow it was not used past the 1st player. I stared at the code for a really long
time and it looks like when cardEffect(smithy, choice1, choice2, choice3, G, handPos, 0); is called --- it only applies to the first player
and not to the rest of the players. i need to figure out how to change to code to make sure that its not only the 1st player that plays the
card, but other players in the game as well.

