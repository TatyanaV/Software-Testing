Source: dominion.c -> checkGameOver(struct gameState*)

Bug Title: Specific game state causes faulty return value

Description: When running checkGameOver a specific state can cause the function to return that a game is not over when it actually is. In checkGameOver there is a for loop that iterates over 25 of the card values instead of up to treasure_map+1. treasure_map+1 = 28. This leaves 3 card values and their supply counts unchecked. If these 3 supply piles are empty, the game doesn't check and returns a false value (i.e. game continues when it shouldn't)





Source: dominion.c -> discardCard(int, int, struct gameState*, int)

Bug Title: discard[player][] not changing as expected

Description: When discardCard is called and the gameState is compared to a copy taken before the function is called, the array representing the discard pile for that player is unchanged. In other words:
   before->discard[player][i] == after->discard[player][i]
   for all values of i < MAX_DECK





Source: dominion.c -> playAdventurer(struct gameState*)

Bug Title: Incorrect net sum of cards after playAdventurer is called

Description: When playAdventurer is called, 2 new treasure cards should be added into the hand and then the card should be discarded. This should make the net sum equal to 1 more than the original value. This is not true.




Source: dominion.c -> playAdventurer(struct gameState*)

Bug Title: Not enough state changes after playAdventurer is called

Description: There are 8 expected state changes after the card is played:
   hand[player][]
   handCount[player]
   deck[player][]
   deckCount[player]
   discard[player][]
   discardCount[player]
   playedCards[]
   playedCardCount
There are 3 states that aren't being affected properly. discard[player][], discardCount, and playedCardCount (likely related to the missing discard call in function, and associated bug).




Source: dominion.c -> playAdventurer(struct gameState*)

Bug Title: Treasure found when no treasure exists in deck/discard

Description: As cards are being drawn from the deck, the discard may have to be shuffled back into the deck to find 2 treasures. If both deck and discard don't have any treasures, there should be no treasure to be found by the card. The function currently finds it when a state is created with no treasure in either the deck or discard.




Source: dominion.c ->playAdventurer(struct gameState*)

Bug Title: Count of a card type changing after adventurer card played

Description: In a game at a given point, you should be able to count each type of card that is in their deck, hand, and discard and these values shouldn't change after playing the adventurer card. They may get shuffled, but if there were 5 smithy cards before there should be 5 after. This is not currently the case. The adventurer card is changing the amount of each type of card after it is played. This is likely related to the discard portion of the card that involves the tempHand.




Source: dominion.c -> playSmithy(struct gameState*)

Bug Title: Total count of all cards not maintained after Smithy Card played

Description: The same number of cards across hand, deck, and discard should remain the same before and after the smithy card is played. This is not the case. After the card is played, there is a net 1 card gain by the player in the state (not sure if its in hand, deck, or discard). Likely related to bad discard function. Specific card is Smithy card that has a different count before and after.




Source: dominion.c -> playVillage(struct gameState*)

Bug Title: Village card not netting correct number of actions

Description: The village card should use 1 action to play the original card and gain two for a net of 1 action gained from original state number of actions. In other words, if you start with 1 action you use it and have 0 actions but then gain 2 more actions you have 1 more than you started with (2 - 1 == 1). State gets altered to have a net gain of 2 actions.


