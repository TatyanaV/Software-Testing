/*
 *Created by :Sam Schultz
	
  File: randomhistory.c
  Summary: Description of random test .out files.
  Date: 5/8/2016


  After reviewing the results of my random testers I have noticed that there are bugs that curently exist with both of the cards I tested.
  I chose to test Adventurer and Smithy Cards.
  The bugs that I noticed within the Adventurer card is that the card does not update the coins correctly. Another bug with the
  adventurer card is it is not put into the played card pile correctly.
  The card also does not remove an action after being played.
  I was also getting weired numbers for the actual hand size compared to the expected hand size. 
  After looking at my randomtestadventurer.out I see that 37% of dominion.c was executed with a total of 28% of branches executed.
  I am not sure if these coverages are satisfactory because I am only testing one small section of the dominion.c file and not the whole thing.

  After looking at the results of my Smithy random tester I see that there are currently some existing bugs.
  These bugs consist of the played card pile not being updated correctly.
  Another bug that I noticed is that the number of actions is not updated correctly.
  The hand size is also not being updated correctly causing a test case to fail. 
  Another thing I noticed was that other players hands were not being updated correctly either.

  My smithy tester executed with 37% of lines being executed from dominion.c.
  With 28% of branches executed.
  I beleive that these numbers are close between the two testers because I tested very similar cases between the two cards.
 *
 *
 *
 *
 *
 *
 * */
