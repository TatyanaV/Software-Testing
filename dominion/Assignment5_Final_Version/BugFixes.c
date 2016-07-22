Bugs Found By Sean Mulholland

=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***: Incorrect net sum of cards after playAdventurer is called

Description: When playAdventurer is called, 2 new treasure cards should be added
into the hand and then the card should be discarded. This should make the net sum
equal to 1 more than the original value. This is not true.


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
My first reaction to this was: Sean is wrong, the net sum of the handcount should be
equal to 2 more than the original value. I found the original dominion code [ provided by the istructor],
tested it and found out that I was correct - new handcount should be equal to old handcount + 2.
However, what made me think was the Sean found 2 bugs [see below] that I have not introduced into the code.
I was very confused and made several posts on the piazza, just to find out that there were bugs in the original
code.

I've studied the code and noticed [ something that I have not noticed before] that there is no code that
discards adventure card after its played, thus the new handcount becomes = old handcount +2.
I've tried to play dominion game just to see whats going on, but I guess I have not reached high enough level,
so adventure card is not available in the game.

It seems logical that once the card is played, it should be discarded, and I need to add discardCard() to
discard adventure card after its played. However, I should say that I am very SKEPTICAL about this bug in
the original code.

Anyways, I am hoping I am correct that there was a bug in the original Adventure code and the adventure card
needs to be discarded after the player playes the card. At the same time, Sean detected this bug, and accoding to
him the "the net sum equal to 1 more than the original value.", so I will go ahead and fix this bug, but adding
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0); to the int card_Adventurer(struct gameState *state, int handPos)
  function.

=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***: Treasure found when no treasure exists in deck/discard

Description: As cards are being drawn from the deck, the discard may have to be
shuffled back into the deck to find 2 treasures. If both deck and discard don't
have any treasures, there should be no treasure to be found by the card.
The function currently finds it when a state is created with no treasure in either the deck or discard.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

This bug makes sense because these is the bug that I have introducted mysel:
	Bug: if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) to the
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn != gold)

What this bug does - no matter what card is drawn if its not gold, it is coutned as
a treasure card and added to the hand of the player. Thus when real treasure does not exist
in the deck/discard, "treasures" are found anyways because every card that is not gold is
counted as treasure. To fix this bug, I have changed
if (cardDrawn == copper || cardDrawn == silver || cardDrawn != gold)
    back to
if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
which was in the original code.

=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***: Not enough state changes after playAdventurer is called

Description: There are 8 expected state changes after the card is played:
   hand[player][] +++++
   handCount[player] +++++
   deck[player][]
   deckCount[player]+++++
   discard[player][]
   discardCount[player]
   playedCards[]
   playedCardCount
Only 3 states are being affected by the play of adventurer: hand, handCount, and deckCount.
None of the others are properly affected.


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
this bug makes sense for the same reason why 1st bug makes sense - there was a bug in the original code.
See top of the document for discussion.
The adventure card was not discarded after it was played, thus, there was not change in the discardCount, discard,
playercardCount, playedCards, etc. This bug was fixed by adding the following line:
      //discard card from hand
  discardCard(handPos, currentPlayer, state, 0); to the int card_Adventurer(struct gameState *state, int handPos)
  function.


=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***: Specific game state causes faulty return value

Description: When running checkGameOver a specific state can cause the function to
return that a game is not over when it actually is.
In checkGameOver there is a for loop that iterates over 25 of the card values instead of up to treasure_map+1.
treasure_map+1 = 28. This leaves 3 card values and their supply counts unchecked.
If these 3 supply piles are empty, the game doesn't check
and returns a false value (i.e. game continues when it shouldn't)


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
this was a surprize bug to me. As I pointed out, I just found out today that there
were bugs in the original code.
Sean provided very detailed explanation about the bug and how to fix the bug. To fix the Bug

for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }


was changed to
for (i = 0; i < 28; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }



=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***:  Village card not netting correct number of actions

Description: The village card should use 1 action to play the
original card and gain two for a net of 1 action gained from original
state number of actions. In other words, if you start with 1 action you use
it and have 0 actions but then gain 2 more actions you have 1 more than you
started with (2 - 1 == 1). State gets altered to have a net gain of 2 actions.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
this bug makes sense because I have introduced this bug for the assignment #2
Bug:  state->numActions = state->numActions + 2; is replaced with  state->numActions = state->numActions + 3;
To fix this bug, I have changed state->numActions = state->numActions + 3; back to what it was in the original
code: state->numActions = state->numActions + 2;




=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===


***Bug Title***:  discard[player][] not changing as expected

Description: When discardCard is called and the gameState is
compared to a copy taken before the function is called, the array
representing the discard pile for that player is unchanged. In other words:
   before->discard[player][i] == after->discard[player][i]
   for all values of i < MAX_DECK
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
This was a surprize bug to me as well and this must be the bug present in the
original code. If I interpret this bug correctly, the discardCard() function does not discard cards,
and the discardCount is not getting updated.

To fix the bug, I used the following resources, just to get a better idea what was going on
https://github.com/aburasali/cs362sp16/blob/70a2a856cd84bb1812934d796ae2ff2bcb6a9e1c/projects/hiteda/dominion/dominion.c
This bug can be fixed by adding the following lines of code to the discardCard() function:
    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][handPos];
	state->discardCount[currentPlayer]++;

These code copy the current players card at handPos in their hand to the top of the discard pile.
After that the discardCount is incremented.


=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***: Total count of all cards not maintained after Smithy Card played

Description: The same number of cards across hand, deck, and discard should remain
the same before and after the smithy card is played. This is not the case.
After the card is played, there is a net 1 card gain by the player in the state
(not sure if its in hand, deck, or discard). Likely related to bad discard function.
Specific card is Smithy card that has a different count before and after.

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

this bug was detected due to the bug in the discardCard() function. The bug was fixed above, so
by fixing the bug in the discardCard() function, this detected bug was fized as well.


=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

*****Its alredy 10:30pm Pacific time and I still have not gotten bug report from Samuel Theodore Schultz, so Ill go ahead and fix my bugs.****


=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***:  simthy

this bug was introduced by me:

    smithy card code is moved to the int card_Smithy(struct gameState *state, int handPos) function
    function card_Smithy(state,handPos) is called in the case smithy:
    all required variables are declared locally in the int card_Smithy(struct gameState *state, int handPos) function
	Bug: in for statement the loop is started at 1 instead of 0

When I ran my cardtest1.c, this error was dtected:
    %****************************SMITHY CARD TEST****************************%


 Unit Test for SMITHY
Hand Count before Smithy Card is Played: 5

Hand Count after Smithy Card is Played:

ERROR: Hand Count Should be: 7. Instead Hand Count is: 6

To fix this bug, I have changed
  for (i = 1; i < 3; i++)
  {
    drawCard(currentPlayer, state);
  }


  back to

    for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer, state);
  }

=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

***Bug Title***:  adventure card
The bug that I have introduced was already fixed using bug report that I got from Sean


=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===


 ***Bug Title***:  Unit Test for council_room
 this bug was introduced by me:
Bug:        //+1 Buy      //state->numBuys++; is removed from the function

This bug does allow the current player to buy a card, thus with this Bug
the handcount will increase +3 instead of expected +4 ------------------------NOTE THIS WAS INCORRECT INTERPRETATION

    when I ran my card test, thats the results that I got:

 %****************************COUNCIL_ROOM CARD TEST****************************%


 Hand Count of the CURRENT player before council_room Card is Played: 5
Hand Count of the OTHER player before council_room Card is Played: 0

Hand Count Of the CURRENT Player after council_room Card is Played:

ERROR: Hand Count Should be: 9. Instead Hand Count is: 8

Hand Count Of the OTHER Player after council_room Card is Played:

No Errors were detected in the Council_room card. Hand Count is: 1




to fix the bug, I have added the state->numBuys++; back to the code. Basically,
I have removed the bug that I have introduced in the code.  I reran the test
and found out that the bug was not gone.

Here are the results:
%****************************COUNCIL_ROOM CARD TEST****************************%


 Unit Test for council_room
Hand Count of the CURRENT player before council_room Card is Played: 5
Hand Count of the OTHER player before council_room Card is Played: 0

Hand Count Of the CURRENT Player after council_room Card is Played:

ERROR: Hand Count Should be: 9. Instead Hand Count is: 8

Hand Count Of the OTHER Player after council_room Card is Played:

No Errors were detected in the Council_room card. Hand Count is: 1

As you can see the bug is still there. I was very confused. I decided to take a look at the code of the council_room and realized
that I have missinterpreted the code for the council_room card.
When I saw comment       //+1 Buy
next to the     state->numBuys++;, I've interpreted it as if the player HAS TO BUY THE CARD,
and not that the numBuys increases. As the result of this, I thought that the handcount needs to
increase +4 [ 4 drawn + 1 buy - 1 discard = 4], but the reality is the handcount is increased +3 [ 3 drawn - 1 discard = 3]
and the numBuys is +1. Becasue I missinterpreted the comment, I made my test incorrectly.



Conclusion about coverage:
    After this assignment I am very sceptical about coverages. I got the following results for my tests:

File 'unittest1.c'
    Lines executed:83.33% of 24
    Branches executed:100.00% of 6
    Taken at least once:66.67% of 6
    Calls executed:70.59% of 17

File 'unittest2.c'
    Lines executed:100.00% of 18
    Branches executed:100.00% of 4
    Taken at least once:50.00% of 4
    Calls executed:77.78% of 9
    Creating 'unittest2.c.gcov'

File 'unittest3.c'
    Lines executed:80.00% of 25
    Branches executed:66.67% of 12
    Taken at least once:33.33% of 12
    Calls executed:66.67% of 15
    Creating 'unittest3.c.gcov'

File 'unittest4.c'
    Lines executed:84.21% of 19
    Branches executed:100.00% of 6
    Taken at least once:50.00% of 6
    Calls executed:72.73% of 11
    Creating 'unittest4.c.gcov'

File 'cardtest1.c'
    Lines executed:92.86% of 14
    Branches executed:100.00% of 2
    Taken at least once:50.00% of 2
    Calls executed:87.50% of 8
    Creating 'cardtest1.c.gcov'


File 'cardtest2.c'
    Lines executed:92.86% of 14
    Branches executed:100.00% of 2
    Taken at least once:50.00% of 2
    Calls executed:87.50% of 8
    Creating 'cardtest2.c.gcov'

File 'cardtest3.c'
    Lines executed:90.00% of 20
    Branches executed:100.00% of 4
    Taken at least once:50.00% of 4
    Calls executed:83.33% of 12
    Creating 'cardtest3.c.gcov'


File 'cardtest4.c'
    Lines executed:90.00% of 20
    Branches executed:100.00% of 4
    Taken at least once:50.00% of 4
    Calls executed:83.33% of 12
    Creating 'cardtest4.c.gcov'


File 'randomtestcard.c'
Lines executed:97.14% of 35
Branches executed:100.00% of 12
Taken at least once:91.67% of 12
Calls executed:96.00% of 25

File 'randomtestadventurer.c'
Lines executed:97.83% of 46
Branches executed:100.00% of 28
Taken at least once:96.43% of 28
Calls executed:96.55% of 29

File 'dominion.c'
Lines executed:34.33% of 571
Branches executed:30.94% of 417
Taken at least once:23.98% of 417
Calls executed:27.72% of 101
Creating 'dominion.c.gcov'

If you look at the coverage of my tests, the coverage looks really good. Even the coverage of the dominion.c file is decent.
However, I found out using results from Sam there were bugs in the original code
that I was not aware of and the only reason why some of those bugs were discovered was becasue Sam refactored and implemented
tests for different functions. Thus, a lot of the functions that I have
tested using my tests are used by other functions in the code that we not tested and they have bugs. At the same time, I realized
that my tests were not very thorough, I should have tested for different states of the game, not only for the handcounts of the players.
Yes, my coverage for testing Smithy card is great
File 'unittest1.c'
    Lines executed:83.33% of 24
    Branches executed:100.00% of 6
    Taken at least once:66.67% of 6
    Calls executed:70.59% of 1

 But I have not caught the bug that card was not added to the discard pile after Smithy card was played because I have not
 checked the state of the discard pile. Overeall, this was the most usefull assignment in this class and I got a much better
 understanding how to make decent/good tests for the code.




