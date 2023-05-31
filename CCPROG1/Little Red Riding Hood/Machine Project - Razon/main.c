/*   Programmed by:    RAZON, Luis Miguel Antonio B.  S16B

     Description:      It instructs the user to construct a board game where Little Red Riding Hood will try to get to Granny's house while collecting the required items and avoiding obstacles that the user has placed.

     Last modified:    February 06, 2022 

*/

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "grid.c"
#include "conditions.c"
#include "movements.c"
#include "woodsman.c"
#include "behavior.c"

#define INV_SLOTS 20


/*   Starts the game by initializing the grid and its contents. Asks for user input for the Grid Size and the position of elements before starting the simulation. 

     [@param  (none)  no parameters needed] 

     [@return  (void) no return value] 
*/ 
void 
startGame () 
{
		int nGrid[2];
		char cGridX[2], cGridY[2];

		char cGrid[15][15]; //[x][y]
		char cMode = 'a';

		char cAmount = 'a';
		int nAmount = 0;

		int x, y, i; //for the for loops

		int nError = 1; //1= Error, 0 = Safe

		printf ("WELCOME TO THE LITTLE RED RIDING HOOD SIMULATION MADE BY LUIS MIGUEL RAZON OF S16B!!!\n\n");
		printf ("Objective: Create a grid that Little Red Riding Hood will traverse in order to reach Grandma.\n");
		printf ("You get to dictate the location of the traps as well as items that will challenge/help LRRH succeed!\n");
		printf ("Good luck and Have fun!!!\n\n");

		printf ("First off, you need to choose a mode. \n[F] Fast Mode - Automatically runs the simulation every 1 second \n[M] Manual Mode - You need to press Enter in order for the simulation to move forward. \n\n");
		printf ("\nEnter the letter corresponding to your choice: ");
		scanf (" %c", &cMode);
		fflush(stdin);

		while (cMode != 'F' && cMode != 'f' && cMode != 'M' && cMode != 'm') {
				printf("\n\t Invalid Input, please try again: ");
				scanf (" %c", &cMode);
				fflush(stdin);
		}

		printf ("\nNext, you will enter the grid size of your choice... \n");
		printf ("Enter Grid Dimensions [8 (min) - 15 (max)]: ");

		
		while (nError == 1) {

				printf ("\n\t[X]: ");
				scanf (" %2s", &cGridX);
				fflush(stdin); //clears the input buffer so when someone inputs more than 1 character, it gets cleared (i.e. '2.5')
				nGrid[0] = convertToDigit (cGridX);

				printf ("\n\t[Y]: ");
				scanf (" %2s", &cGridY);
				fflush(stdin);
				nGrid[1] = convertToDigit (cGridY);

				if (nGrid[0] < 8 || nGrid[0] > 15 || nGrid[0] < 8 || nGrid[0] > 15) {
						printf("\n\t[ERROR] Invalid Grid Dimensions, out of range. \n\tEnter new Grid Dimensions: ");

				} else {
						nError = 0;
						break;
				}
		}


		//grid offsets
		nGrid[0]--;
		nGrid[1]--;

		for (x = 0; x <= nGrid[0]; x++) {
				for (y = 0; y <= nGrid[1]; y++)
						cGrid[x][y] = '_';
		}


		//Initial Location of Red Riding Hood (first square)
		cGrid[0][0] = 'R';
		printf ("Lastly, you will need to enter the locations for each of the elements on the board. \n[Note] Some elements may ask you to dictate the amount of elements you want present in the board.\n");
		//Asks the user input for positions for:
		//1. Granny
		assignGrid (&cGrid, nGrid, 'G');

		//2. Wolf
		assignGrid (&cGrid, nGrid,'W');

		//3. Woodsman
		assignGrid (&cGrid, nGrid, 'L');

		//4. Bakeshop
		printf ("Amount of Bakeshops [Min: 1 | Max: 3 (x < 1 = 1 | x > 3 = 3)]: ");
		scanf (" %c", &cAmount);
		fflush(stdin);

		while (isdigit (cAmount) == 0) { //error checking
			printf ("\n\t[ERROR] Invalid input. (Only unsigned positive numbers are allowed, float gets converted to integer) \n\tEnter new coordinates: ");
			scanf (" %c", &cAmount);
			fflush(stdin);
		}
		
		nAmount = cAmount - '0'; //converts a single character to int

		if (nAmount > 3)
				nAmount = 3;
		else if (nAmount < 1)
				nAmount = 1;
				
		for (i = 0; i < nAmount; i++)
				assignGrid (&cGrid, nGrid, 'B');

		//5. Flower
		printf ("Amount of Flower [Min: 1 | Max: 3 (anything higher will be set to 3)]: ");
		scanf (" %c", &cAmount);
		fflush(stdin);

		while (isdigit (cAmount) == 0) { //error checking
			printf ("\n\t[ERROR] Invalid input. (Only unsigned positive numbers are allowed, float gets converted to integer) \n\tEnter new coordinates: ");
			scanf (" %c", &cAmount);
			fflush (stdin);
		}
		
		nAmount = cAmount - '0'; //converts a single character to int

		if (nAmount > 3)
				nAmount = 3;
		else if (nAmount < 1)
				nAmount = 1;
				
		for (i = 0; i < nAmount; i++)
				assignGrid (&cGrid, nGrid,'F');

		//6. Pit
		printf ("Amount of Pit [Min: 1 | Max: 3 (anything higher will be set to 3)]: ");
		scanf (" %c", &cAmount);
		fflush (stdin);

		while (isdigit (cAmount) == 0) { //error checking
			printf ("\n\t[ERROR] Invalid input. (Only unsigned positive numbers are allowed, float gets converted to integer) \n\tEnter new coordinates: ");
			scanf (" %c", &cAmount);
			fflush (stdin);
		}
		
		nAmount = cAmount - '0'; //converts a single character to int

		if (nAmount > 3)
				nAmount = 3;
		else if (nAmount < 1)
				nAmount = 1;
				
		for (i = 0; i < nAmount; i++)
				assignGrid (&cGrid, nGrid, 'P');

		printf ("\n\n================[Simulation Start]================\n");
		fflush(stdin);
		//behavior code execution
		startSimulation (&cGrid, nGrid, cMode);
}

/*   The main function. Used to start the game. 

     [@param  (none)  no parameters needed] 

     [@return  (void) no return value] 
*/ 
int 
main ()
{
		startGame ();
		return 0;
}
