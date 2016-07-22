=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

Bugs in Sean Mulholland code

=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===
%****************************PLEASE NOTE THAT MY RANDOM TESTING WORKS ACCURATELY ONLY FOR player # 0,
so in case you decide to take a look at the randomtestestcard.out and randomtestadventure.out
only look at the results for PLAYER #0


DETECTED BUG #1: SMITHY CARD TEST AND RANDOM TESTING ---- HANCOUNT has failed

After the smithy card is played the handcount of the player is lower than expected.
Based on the values that I got the handcount has not changed at all.

Here is the output my test [ card1.c] for the Sean's Smithy card.

%****************************SMITHY CARD TEST****************************%


 Unit Test for SMITHY
Hand Count before Smithy Card is Played: 5

Hand Count after Smithy Card is Played:

ERROR: Hand Count Should be: 7. Instead Hand Count is: 5

The Smithy card has also failed using the random testing - there was no change in the handout.
Please note my random test works accuratly only for the player # 0

 SMITHY CARD RANDOME TESTING

%**************************** SMITHY CARD RANDOM TESTING****************************%

Test #: 0

Player #: 0
 outpost,  ambassador,  mine,  silver,  silver,  smithy,  steward,  province,  ambassador,  gold,  treasure_map,  gardens,  embargo,  ambassador,  ambassador,  steward,  embargo,  mine,  copper,  silver,  council_room,  gardens,  curse,  cutpurse,  cutpurse,  copper,  gardens,  gold,  province,  gold,  estate,  treasure_map,  baron,  smithy,  copper,  ambassador,  treasure_map,  remodel,  salvager,  council_room,  adventurer,  outpost,  adventurer,  duchy,  silver,  curse,  ambassador,  estate,  mine,  smithy,  embargo,  council_room,  outpost,  outpost,  tribute,  adventurer,  curse,  steward,  duchy,  tribute,  salvager,  tribute,  adventurer,  smithy,  cutpurse,  remodel,  gold,  feast,  smithy,  tribute,  minion,  ambassador,  copper,  salvager,  embargo,  gardens,  salvager,  silver,  curse,  salvager,  adventurer,  embargo,  embargo,  ambassador,  adventurer,  province,  great_hall,  salvager,  cutpurse,  steward,  great_hall,  tribute,  treasure_map,  salvager,  cutpurse,  cutpurse,  sea_hag,  great_hall,  province,  mine,  sea_hag,  cutpurse,  ambassador,  duchy,  steward,  copper,  estate,  silver,  feast,  minion,  duchy,  gold,  smithy,  smithy,  baron,  feast,  great_hall,  copper,  gold,  mine,  mine,  remodel,  tribute,  gardens,  feast,  duchy,  copper,  outpost,  steward,  council_room,  outpost,  great_hall,  duchy,  great_hall,  council_room,  feast,  ambassador,  sea_hag,  village,  tribute,  great_hall,  gold,  sea_hag,  steward,  council_room,  smithy,  curse,  sea_hag,  gold,  adventurer,  sea_hag,  minion,  council_room,  gold,  curse,  minion,  council_room,  silver,  duchy,  baron,  smithy,  sea_hag,  cutpurse,  copper,  village,  duchy,  smithy,  adventurer,  curse,  minion,  baron,  great_hall,  remodel,  duchy,  adventurer,  ambassador,  copper,  salvager,  steward,  gardens,  ambassador,  silver,  curse,  estate,  mine,  minion,  steward,  council_room,  embargo,  feast,  salvager,  salvager,  adventurer,  steward,  minion,  cutpurse,  feast,  tribute,  minion,  feast,  feast,  embargo,  baron,  cutpurse,  salvager,  mine,  copper,  duchy,  council_room,  embargo,  estate,  estate,  minion,  duchy,  duchy,  estate,  tribute,  feast,  treasure_map,  province,  steward,  outpost,  curse,  village,  province,  minion,  council_room,  remodel,  feast,  baron,  cutpurse,  council_room,  gardens,  sea_hag,  steward,  adventurer,  gardens,  embargo,  sea_hag,  adventurer,  adventurer,  curse,  feast,  salvager,  steward,  curse,  village,  treasure_map,  treasure_map,  smithy,  duchy,  gold,  sea_hag,  steward,  cutpurse,  estate,  salvager,  steward,  smithy,  embargo,  gold,  salvager,  province,  great_hall,  embargo,  mine,  smithy,  cutpurse,  embargo,  mine,  duchy,  duchy,  curse,  curse,  baron,  steward,  curse,  tribute,  minion,  baron,  cutpurse,  council_room,  embargo,  ambassador,  treasure_map,  great_hall,  cutpurse,  outpost,  adventurer,  salvager,  tribute,  province,  cutpurse,  mine,  council_room,  silver,  mine,  cutpurse,  curse,  adventurer,  curse,
Handcount Before: 301
Handcount After: 301
	HANDCOUNT TEST FAILED



DETECTED BUG #2: VILLAGE CARD TEST Num Action failure.

 After the village card is played, number of actions is lower than expected.

%****************************VILLAGE CARD TEST****************************%


 Unit Test for Village
Hand Count before Village Card is Played: 5
Num Action before Village Card is Played: 1

Hand Count Of the Player after village Card is Played:

No Errors were detected in the Village card. Hand Count is: 5

Num Action Of the Player after village Card is Played:

ERROR: Num Action Should be: 3. Instead Num Actions is: 2




&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&Note for Sean&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
SEE BUGSFIXES REPORT - I WAS WRONG
I have not detected any bugs in your Adventure card. However, when I looked
at your randomtestadventurer.out file, I've noticed that your testing was failing
and what caught my attention was the following sentence:

    "Basic Function Check: Didn't end up with net +1 cards in hand"

 The way how I understood adventure card was that the hadcount becomes +2 after the adventure card is played.
 I tested the original dominion.c file in the aburasali directory and got the following results:

     %****************************ADVENTURE CARD TEST****************************%


 Unit Test for ADVENTURE
Hand Count before Adventure Card is Played: 5

Hand Count after Adventure Card is Played:

No Errors were detected in the Adventure card. Hand Count is: 7

unit Test: Adventure test successful


As you can see the handccount +2 not +1.



DETECTED BUG #3: COUNCIL_ROOM card HANCOUNT has failed -- I THINK THERE IS A BUG IN MY TEST -- see BugFixes report

After the council_room card is played the handcount of the CURRENT player is
not accurate [its lower than expected].This was an interesting finding because when
I looked at Seans refactor.c file, this card was not changed. However, maybe there was a bug in the
original code or maybe my unit test is wrong; however, I got expected results when I tested my code

Here is the output my test [ card3.c] for the Seans council_room card.
%****************************COUNCIL_ROOM CARD TEST****************************%


 Unit Test for council_room
Hand Count of the CURRENT player before council_room Card is Played: 5
Hand Count of the OTHER player before council_room Card is Played: 0

Hand Count Of the CURRENT Player after council_room Card is Played:

ERROR: Hand Count Should be: 9. Instead Hand Count is: 8

Hand Count Of the OTHER Player after council_room Card is Played:

No Errors were detected in the Council_room card. Hand Count is: 1



=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===

Bugs in Samuel Theodore Schultz code

=== === === === === === === === === === === === === === === ===
=== === === === === === === === === === === === === === === ===


%****************************PLEASE NOTE THAT MY RANDOM TESTING WORKS ACCURATELY ONLY FOR player # 0,
so in case you decide to take a look at the randomtestestcard.out and randomtestadventure.out
only look at the results for PLAYER #0

DETECTED BUG #1: ADVENTURE card HANCOUNT has failed

After the adventure card is played, the handcount is higher than
exprected, it looks like that more than 2 treasures are added to the deck of the player
or some of the revealed cards that are not treasures are placed in the deck of the
player instead of the discard pile.

Here is the output my test [ card2.c] for the Sam's adventure card.

%****************************ADVENTURE CARD TEST****************************%

Unit Test for ADVENTURE
Hand Count before Adventure Card is Played: 5

Hand Count after Adventure Card is Played:

ERROR: Hand Count Should be: 7. Instead Hand Count is: 9


DETECTED BUG #2: SMITHY CARD RANDOM TESTING HANCOUNT has failed

After the smithy card is played the handcount of the player is lower than expected. Please note that
my test works accurately only for player 0.


Here is the output my test [ randomtestcard.c] for the Sam Schultzs Smithy card.

%****************************SMITHY CARD RANDOM TESTING****************************%

Test #: 0

Player #: 0
 steward,  adventurer,  gardens,  sea_hag,  remodel,  outpost,  smithy,  treasure_map,  adventurer,  baron,  council_room,  duchy,  steward,  ambassador,  mine,  smithy,  remodel,  copper,  baron,  gold,  cutpurse,  feast,  silver,  embargo,  embargo,  steward,  sea_hag,  province,  tribute,  salvager,  cutpurse,  curse,  silver,  ambassador,  village,  minion,  minion,  curse,  great_hall,  smithy,  copper,  village,  copper,  mine,  outpost,  great_hall,  salvager,  salvager,  ambassador,  duchy,  province,  province,  mine,  feast,  treasure_map,  embargo,  great_hall,  salvager,  village,  sea_hag,  cutpurse,  council_room,  village,  treasure_map,  minion,  estate,  silver,  outpost,  steward,  mine,  feast,  mine,  sea_hag,  province,  outpost,  cutpurse,  tribute,  feast,  steward,  estate,  mine,  embargo,  silver,  mine,  ambassador,  copper,  gold,  feast,  estate,  ambassador,  adventurer,  mine,  minion,  cutpurse,  curse,  salvager,  remodel,  silver,  ambassador,  province,  great_hall,  tribute,  province,  province,  embargo,  treasure_map,  salvager,  village,  feast,  silver,  copper,  feast,  great_hall,  feast,  cutpurse,  feast,  smithy,  curse,  adventurer,  province,  gardens,  copper,  copper,  great_hall,  village,  copper,  smithy,  treasure_map,  feast,  outpost,  steward,  baron,  baron,  embargo,  steward,  gardens,  gardens,  silver,  smithy,  tribute,  gardens,  gold,  duchy,  treasure_map,  great_hall,  remodel,  salvager,  steward,  estate,  copper,  mine,  mine,  salvager,  baron,  minion,  remodel,  tribute,  tribute,  curse,  minion,  baron,  council_room,  silver,  tribute,  province,  smithy,  steward,  duchy,  steward,  ambassador,  embargo,  estate,  curse,  smithy,  great_hall,  great_hall,  sea_hag,  smithy,  outpost,  treasure_map,  gold,  adventurer,  curse,  copper,  embargo,  gold,  great_hall,  province,  village,  silver,  cutpurse,  province,  smithy,  baron,  mine,  silver,  estate,  province,  council_room,  tribute,  remodel,  tribute,  feast,  remodel,  silver,  sea_hag,  minion,  tribute,  mine,  province,  adventurer,  adventurer,  gardens,  outpost,  mine,  embargo,  steward,  great_hall,  village,  gold,  cutpurse,  council_room,  sea_hag,  council_room,  smithy,  feast,  smithy,  village,  estate,  cutpurse,  outpost,  province,  smithy,  silver,  baron,  adventurer,  ambassador,  embargo,  baron,  ambassador,  sea_hag,  remodel,  curse,  salvager,  curse,
Handcount Before: 245
Handcount After: 246
	HANDCOUNT TEST FAILED




DETECTED BUG #3: ADVENTURE CARD RANDOM TESTING HANCOUNT and TREASUARE COUNTS have failed

After the adventure card is played the handcount of the player is higher than expected [the handcount should be +2]. This bug
has aready been detected and mention above when I ran my card1 test. However, my random test for the
adventure card is more thorough. I also check for the treasure counts. When i ran the randomtestadventure card
test, the teasure count has failed after the adventure card was played.
Please note that my test works accurately only for player 0.


Here is the output of my test [ randomtestadventure.c] for the Sams Adventure card.

%****************************ADVENTURE CARD RANDOM TESTING****************************%

ADVENTURE CARD RANDOM TESTING



Test #: 0

Player #: 0
Treasures Before: 28
Treasures After: 31
	TREASURE COUNT TEST FAILED
Handcount Before: 245
Handcount After: 250
	HANDCOUNT TEST FAILED










DETECTED BUG #4: COUNCIL_ROOM card HANCOUNT has failed --- I THINK THERE IS A BUG IN MY TEST

After the council_room card is played the handcount of the CURRENT player is
not accurate [its lower than expected].This was an interesting finding because when
I looked at Sams refacto.c file, this card was not changed. However, maybe there was a bug in the
original code or maybe my unit test is wrong, however, I got expected results whne I tested my code

Here is the output my test [ card3.c] for the Sams council_room card.
%****************************COUNCIL_ROOM CARD TEST****************************%


Unit Test for council_room
Hand Count of the CURRENT player before council_room Card is Played: 5
Hand Count of the OTHER player before council_room Card is Played: 0

Hand Count Of the CURRENT Player after council_room Card is Played:

ERROR: Hand Count Should be: 9. Instead Hand Count is: 8

Hand Count Of the OTHER Player after council_room Card is Played:

No Errors were detected in the Council_room card. Hand Count is: 1










