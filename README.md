Aman Agarwal
806085297	
amana1@iastate.edu

				
				Project Part-4
				--------------
					
			Solitaire: interactive terminal game
			____________________________________	
	

				Introduction
				------------

This part is the final product of the project which utilizes all the 3
parts to build a interactive terminal game for users to play. The following program
uses -f switch to take the filename, -s switch to take the seed value in order to generate
a random game, -1 for turn 1 and -3 for turn 3 and -l Limit , initial value for 
limit is set as infinity. The following game also has the ability to undo the last 
move and restart a new game or start the same game from begining.



	

				Overview
				--------


The following code uses a config class from part2 to store the game configuration 
at all times. Everytime a move is played, the move being played is checked whether
it is valid or not.
If valid, then the current turnbox window is cleared and the previous class is changed
to the mainclass and the move is played class. The resultant configuration is then
displayed again on the termbox window. 
The game runs on the following hot keys:
'.' - draw a card
'r' - reset waste pile
'R' - restart the game
'q' - quit the game
'n' - new game
'w' - waste
'f' - foundations
'1'..'7' - Tableau rows

			
				Files Included
				--------------

1. winnable.cpp
2. check.h
3. advance.c
4. MAKEFILE
5. README.md
6. DEVELOPERS.md
7. config.hh
8. game.cpp 


