Aman Agarwal
806085297
amana1@iatate.edu


					Project Part 4
				
				Solitaire: interactive terminal game
				-------------------------------------

This is the final product of all the previous parts which builds a interactive user interface 
of a solitaire game for users to play. It utilizes code from all the previous parts and other functions
as listed below.




				Functions Used:
				----------------
			1. int index(char a)
			2. void fillInstructionBox();
			3. void updateWaste();
			4. void updateTab();
			5. void generateRandomGame(int seed, int turn)
			6. void FillRest()
			7. void Basic(int argc, char* argv[])
			8. bool contains(char a)
			9. int main(int argc, char* argv[])
			10.void Tab(char a,char b)
			11. void dot()
			12. void reset()
			



Function Defination:

1. int index(char a)
	
Returns the index of the following char in the suits array


2. void fillInstructionBox()

Used tp draw the interstruction box with the hotkeys on the termbox terminal

3.void updateWaste()

Used to draw the waste card and Stock pile section of the termbox terminal

4.void updateTab()

Used to draw the Tableau card  section of the termbox terminal

                       
5. void generateRandomGame(int seed, int turn)

Used to generate a random game if no filename is passed, depending upon the provided seed and turn
value. Default Value for turn is set to 1 and Default value for limit count is set to infinity


6. void FillRest()

Used while generating a new random game, generates the Tableau part


7. void Basic(int argc, char* argv[])

Used to parse the input as per part1, throws errors when nessesary!

                
 8. bool contains(char a)

returns whether the following char is in the list of valid characters or not.


                       
9. int main(int argc, char* argv[])

Utilizes all the fuctions in order to produce the required output!

10.void Tab(char a,char b)

Used to perform a Tableau or foundation move to the configuration

                        
11. void dot()
 
Used to draw a card from the stock pile to the waste
                     
12. void reset()

Used to reset the waste pile back to stock if limit allows!



