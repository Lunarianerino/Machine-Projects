#if !defined(GRID_H) //redefinition error if this is not included
#define GRID_H
#include <stdio.h>
#include "grid.h"
#include "conditions.c"
#include <ctype.h>
#include <unistd.h>
#define INV_SLOTS 20 


/*   Responsible for displaying the contents of the grid. Prints the contents per row times the number of column depending on the dimensions of the grid specified by the user.

     @param  (char)  cGrid[15][15]  is the array representing the grid containing the elements and their positions to be displayed on the console.
     @param  (int)  nGrid[2]  is the array containing the maximum grid sizes specified by the user. Used for the expression in the for loop to know what position of the array to print.

     @return  (void) no return value

*/ 
void 
displayGrid (char cGrid[15][15], 
                int nGrid[2]) 
{
        int x, y;
        for (y = 0; y <= nGrid[1]; y++) {
                for (x = 0; x <= nGrid[0]; x++)
                        printf ("[%c]", cGrid[x][y]);

                printf ("\n");
        }   
        printf ("\n");
}

/*  Assigns the element to a position on the grid specified by the user.

     @param  (char*)  cGrid[15][15]  is the array representing the grid where the element will be placed.
     @param  (int)  nGrid[2]  is the array containing the maximum grid sizes specified by the user. Used to check if the coordinates the user input is valid.
     @param  (char)  cObject  is the character representing the element on the grid.

     @return  (void) no return value

*/ 
void 
assignGrid (char (*cGrid)[15][15], 
                int nGrid[2], 
                char cObject)
{
        char cCoordsX[2], cCoordsY[2];
        int nCoords[2];
        int nCheckingErr = 1; //1 = True; 0 = False

        printf ("Enter Coordinates -  ");

        switch (cObject) {
        case 'G':
                printf ("Granny [G]: ");
                break;

        case 'L':
                printf ("Woodsman [L]: ");
                break;

        case 'W':
                printf ("Wolf [W]: ");
                break;

        case 'B':
                printf ("Bakeshop [B]: ");
                break; 

        case 'P':
                printf ("Pit [P]: ");
                break;
        
        case 'F':
                printf ("Flower [F]: ");
                break;
        }


        //Error checking
        while (nCheckingErr != 0) {
                printf ("\n\t[X]: ");
                scanf (" %2s", &cCoordsX);
                fflush(stdin); //clears the input buffer so when someone inputs more than 1 character, it gets cleared (i.e. '2.5')
                nCoords[0] = convertToDigit (cCoordsX);
                fflush(stdin);

                printf ("\n\t[Y]: ");
                scanf (" %2s", &cCoordsY);
                fflush(stdin);
                nCoords[1] = convertToDigit (cCoordsY);
                fflush(stdin);
                
                //offset
                nCoords[0]--;
                nCoords[1]--;
                if (nGrid[0] < nCoords[0] || nGrid[1] < nCoords[1]) {
                        printf ("\t[ERROR] Coordinates exceeded grid dimensions \n\tEnter new coordinates: ");
                        nCheckingErr = 1;
                }
                else if (nCoords[0] < 0 || nCoords[1] < 0) {
                        printf ("\t[ERROR] Coordinates subceed grid dimensions \n\tEnter new coordinates: ");
                        nCheckingErr = 1;
                }
                else if ((*cGrid)[nCoords[0]][nCoords[1]] != '_') {
                        printf ("\t[ERROR] Coordinates already taken \n\tEnter new coordinates: ");
                        nCheckingErr = 1;
                }
                else 
                        nCheckingErr = 0;
              
        }
    
        (*cGrid)[nCoords[0]][nCoords[1]] = cObject;

        displayGrid (*cGrid, nGrid);


}

/*  Prints the counters for the amount of forwards, rotates, and senses used.

     @param  (int)  nCounters[3]  is the array containing the amount of moves used. nCounters[0] = # of Forwards, [1] = Rotates, and [2] = Senses.

     @return  (void) no return value

*/ 
void 
displayCounters (int nCounters[3]) 
{
        printf ("Foward: %d, Rotate: %d, Sense: %d\n", nCounters[0], nCounters[1], nCounters[2]);
}

/*  Prints the direction to which Little Red Riding Hood is facing.

     @param  (int) nDirection  is the integer that represents what direction LRRH is facing. 0 = Left, 1 = Up, 2 = Right, 3 = Left.

     @return  (void) no return value

*/ 
void 
displayDirection (int nDirection) 
{

        printf ("Direction: ");

        switch (nDirection) {
        case 0:
                printf ("Left");
                break;

        case 1:
                printf ("Up");
                break;

        case 2:
                printf ("Right");
                break;
    
        case 3:
                printf ("Down");
                break;
        }

        printf ("\n");
}

/*  Prints the contents of Little Red Riding Hood's inventory.

     @param  (char) cInventory[INV_SLOTS]  is the array that contains the objects that LRRH has picked up.

     @return  (void) no return value

*/ 
void 
displayInventory (char cInventory[INV_SLOTS]) 
{
        printf ("Inventory:");

        int nSlot;

        //since cInventory is filled with null characters when it was initialized, prints the not null character values.
        for (nSlot = 0; nSlot <= INV_SLOTS; nSlot++) {
                if (cInventory[nSlot] != '\0')
                        printf (" %c,", cInventory[nSlot]);
                else 
                        break;
        }

        printf ("\n");
}


/*  Prints the corresponding "scent" detected by the parameter cSense.

     @param  (char) cSense  is the character that represents the element that is detected by LRRH when she uses the "sense" ability.

     @return  (void) no return value

*/ 
void
displaySense (char cSense) 
{

        printf ("Sense: ");

        switch (cSense) {
        case 'G':
                printf ("Light");
                break;

        case 'L':
                printf ("Sound");
                break;

        case 'W':
                printf ("Howl");
                break;

        case 'B':
                printf ("Heat");
                break;

        case 'F':
                printf ("Scent");
                break;

        case 'P':
                printf ("Breeze");
                break;
        default:
                printf ("None");

        }
        printf ("\n");
    
}

/*  Prints the action performed by LRRH.

     @param  (char) cAction  is the character that represents the action that was performed by LRRH.

     @return  (void) no return value

*/ 
void
displayAction (char cAction) 
{
        printf ("Action: ");
        switch (cAction){
                case 'f':
                        printf ("Forward");
                        break;

                case 'r':
                        printf ("Turn Right");
                        break;

                case 'l':
                        printf ("Turn Left");
                        break;

                case 's':
                        printf ("Sense");
                        break;
                
                default:
                        printf ("Thinking...");
        }
        printf ("\n");
}

/*  Prints the legend of the different tiles in the grid.

     @param  (void) no parameters

     @return  (void) no return value

*/ 
void
displayLegend () 
{
        printf ("Legend: \n");
        printf ("\tAgent: Default - [R] | When stepping on Wolf - [!] || on Bakeshop - [b] || on Flower - [f] || on Woodsman - [l]\n");
        printf ("\tElements: Wolf - [W] | Pit - [P] | Bakeshop - [B] | Woodsman - [L] | Flower - [F] | Granny - [G]\n");
        printf ("\tGrid (Memory View): Traversed Tile - [o] | Unexplored Tile - [ ] | Cornered Tile - [X] | Route Tile - [*]\n");


}
/*  Calls the display functions in a certain order to ensure uniformity.

     @param  (char) cGrid[15][15]  is the array representing the grid containing the elements and their positions to be displayed on the console.
     @param  (int) nGrid[2]  is the array containing the maximum grid sizes specified by the user. Used for the expression in the for loop to know what position of the array to print.
     @param  (int) nCounters[3]  is the array containing the amount of moves used. nCounters[0] = # of Forwards, [1] = Rotates, and [2] = Senses.
     @param  (int) nDirection  is the integer that represents what direction LRRH is facing. 0 = Left, 1 = Up, 2 = Right, 3 = Left.
     @param  (char) cSense  is the character that represents the element that is detected by LRRH when she uses the "sense" ability.
     @param  (char) cInventory[INV_SLOTS]  is the array that contains the objects that LRRH has picked up.
     @param  (char) cAction  is the action or movement that was performed by LRRH

     @return  (void) no return value

*/ 
void 
displayAll (char cGrid[15][15], 
                int nGrid[2], 
                int nCounters[3], 
                int nDirection, 
                char cSense, 
                char cInventory[INV_SLOTS],
                char cAction) 
{
        displayGrid (cGrid, nGrid);
        displayCounters (nCounters);
        displayDirection (nDirection);
        displaySense (cSense);
        displayInventory (cInventory);
        displayAction (cAction);
        printf ("\n");
        displayLegend ();
        printf ("\n");
        printf ("===========================================================\n");
}

/*  Assigns the elemenet detected by LRRH on a seperate grid to remember its position and places the element "o" signifying that LRRH has been in that position before already.

     @param  (char*) cExploredGrid[15][15]  is the 2d array representing the grid that is identical to the game's main board. Used to edit variables inside the grid.
     @param  (int) nDirection  is the variable representing the direction LRRH is currently facing
     @param  (int) nCurPos[2]  is the array containing the current position of LRRH on the grid. [0] = X, [1] = Y
     @param  (char) cSense  is the character that represents the element that is detected by LRRH when she uses the "sense" ability. When LRRH uses sense, the char in this variable is used to update LRRH's own board.
     @param  (char) cAction  is the action or movement that was performed by LRRH. Used to determine if LRRH is moving forward or using sense.

     @return  (void)  no return value

*/ 
void 
drawGrid (char (*cExploredGrid)[15][15], 
            int nDirection, 
            int nCurPos[2], 
            char cSense,
            char cAction) 
{
        int nX = nCurPos[0], nY = nCurPos[1];
        char cObject;

        cObject =  (*cExploredGrid)[nX][nY];
        //(*cExploredGrid)[nX][nY] = 'R'; //fills up previous path, maybe probably only for testing
        
        //If LRRH moved forward instead of using sense, make her previous position an 'o'
        if (cAction == 'f') {
                switch (cObject) {
                case 'W':
                        (*cExploredGrid)[nX][nY] = '!';
                        break;

                case 'B':
                        (*cExploredGrid)[nX][nY] = 'b';
                        break;

                case 'F':
                        (*cExploredGrid)[nX][nY] = 'f';
                        break;

                case 'L':
                        (*cExploredGrid)[nX][nY] = 'l';
                        break; 

                case '_':
                case '*':
                        (*cExploredGrid)[nX][nY] = 'R';
                        break;

                }
                //cObject =  (*cExploredGrid)[nX][nY];

                //since it is previous position, everything is inversed to get where LRRH came from
                switch (nDirection) {
                case 0: //left
                        nX += 1;
                        break;
        
                case 1: //Up
                        nY += 1;
                        break;

                case 2: //Right
                        nX -= 1;
                        break;

                case 3: //Down
                        nY -= 1;
                        break;
                } 

                switch ((*cExploredGrid)[nX][nY]) {
                case '!':
                        (*cExploredGrid)[nX][nY] = 'W';
                        break;

                case 'b':
                        (*cExploredGrid)[nX][nY] = 'B';
                        break;

                case 'f':
                        (*cExploredGrid)[nX][nY] = 'F';
                        break;

                case 'l':
                        (*cExploredGrid)[nX][nY] = 'L';
                        break; 

                case 'R':
                case '*':
                        (*cExploredGrid)[nX][nY] = 'o';
                        break;
                }
        } else if (cAction == 's') {
                switch (nDirection) {
                case 0: //left
                        nX -= 1;
                        break;
        
                case 1: //Up
                        nY -= 1;
                        break;

                case 2: //Right
                        nX += 1;
                        break;

                case 3: //Down
                        nY += 1;
                        break;
                }
                //only fills up the space if it is empty
                if (cSense != ' ')
                        (*cExploredGrid)[nX][nY] = cSense;
        }

    

}

/*  Creates a route outlined by '*' going towards the target object. Limited by only being allowed to go through a specific object (usually 'o'). 

     @param  (char*) cGrid[15][15]  is the 2d array representing the baord that LRRH has in memory. Used as the basis when creating the path.
     @param  (int) nGrid[2]  is the array that contains the upper limits of the board. Used to check if a certain move is valid.
     @param  (char) nCurPos[2]  is the array containing the current position of LRRH on the grid. [0] = X, [1] = Y
     @param  (char) cSearchObject  is the object that will be searched for in the board before making a route towards it.
     @param  (char) cPathObj  is the character in the board that the function is allowed to create a route on. Usually 'o' to simulate LRRH only creating a route based on what she currently "knows".

     @return  (void)  no return value

*/ 
void 
createRoute (char (*cGrid)[15][15],
                int nGrid[2],
                int nCurPos[2],
                char cSearchObject,
                char cPathObj)
{
        int nDist = 100; //so the first object found will always overwrite this
        int x, y;
        int nTargetX, nTargetY;
        int nPosX = nCurPos[0], nPosY = nCurPos[1];
        int nVertical, nHorizontal; //-1 for Up, 1 for Down; -1 for Left, 1 for Right
        int nPosArr[2];
        int cUp, cDown, cLeft, cRight;
        nPosArr[0] = nPosX;
        nPosArr[1] = nPosY;


        //Finding the closest object (position wise) relative to the position of LRRH
        for (y = 0; y <= nGrid[1]; y++) {
                for (x = 0; x <= nGrid[0]; x++) {
                        if ((*cGrid)[x][y] == cSearchObject) {
                                int nTempArr[2];
                                nTempArr[0] = x;
                                nTempArr[1] = y;

                                /*
                                cUp = (isSafe((*cGrid)[x][y - 1]) && isValidStep(nGrid, 1, nTempArr));
                                cDown = (isSafe((*cGrid)[x][y + 1]) && isValidStep(nGrid, 3, nTempArr));
                                cLeft = (isSafe((*cGrid)[x- 1][y]) && isValidStep(nGrid, 0, nTempArr));
                                cRight = (isSafe((*cGrid)[x + 1][y]) && isValidStep(nGrid, 2, nTempArr));*/
                                //if a path can be created towards the current element found, carry on
                                //if (cUp == 1 || cDown == 1 || cLeft == 1 || cRight == 1) {
                                        if ((nDist >= (abs(nCurPos[0] - x) + abs(nCurPos[1] -  y))) && hasValidPathCoords (*cGrid, nGrid, nTempArr)) {
                                                //If the distance towards the previous nearest > current distance
                                                
                                                nDist = (abs(nCurPos[0] - x) + abs(nCurPos[1] -  y));
                                                nTargetX = x;
                                                nTargetY = y;
                                                if (cSearchObject != ' ') //If its not looking for a blank tile, theres most likely only one instance of it and it doesnt need to find any more.
                                                        break;
                                        }
                                //}
                        }
                }
        }

        //runs the code while target is not in the vicinity of the latest placed "*"
        while (ifInRange (*cGrid, cSearchObject, nPosArr) != 1) {

                //If target is below, nVertical = 1, above = -1
                if (nTargetY > nPosY)
                        nVertical = 1;
                else if (nTargetY < nPosY)
                        nVertical = -1;
                
                //tries to get closer to the target vertically while avoiding obstacles
                for (y = 0; y != abs(nTargetY - nCurPos[1]); y++) {
                        nPosArr[0] = nPosX;
                        nPosArr[1] = nPosY;

                        //break out of loop when it has reached its desired destination
                        if (ifInRange (*cGrid, cSearchObject, nPosArr) == 1)
                                break;
                        //If it is allowed to make a path to it (ex, previously explored path), continue

                        if ((*cGrid)[nPosX][nPosY + nVertical] == cPathObj && (nPosY <= nGrid [1] && nPosY >= 0)) {
                                nPosY += nVertical;
                                (*cGrid)[nPosX][nPosY] = '*';
                        } else if ((*cGrid)[nPosX][nPosY + nVertical] != cSearchObject){ //change to isSafe kekw
                                if ((*cGrid)[nPosX + 1][nPosY] == cPathObj && (nPosX + 1) <= nGrid[0]) {//if encountered an obstacle, move 1 space to the right, if right is also empty and if it is valid
                                        nPosX += 1;
                                        (*cGrid)[nPosX][nPosY] = '*';
                                        y -= 1; //reset y to previous value to redo the thingy
                                } else if ((*cGrid)[nPosX - 1][nPosY] == cPathObj && (nPosX - 1) >= 0) { //if right is not empty, try left.
                                        nPosX -= 1;
                                        (*cGrid)[nPosX][nPosY] = '*';
                                        y -= 1; //reset y to previous value to redo the thingy
                                } else { //if neither works, move 1 space backwards and label it as a trap (X)
                                        //If behind is R or X, it meaans R is trapped, so end the function.
                                        if (ifInRange(*cGrid, 'R', nPosArr) == 1 && ifInRange(*cGrid, 'X', nPosArr)) {
                                                (*cGrid)[nPosX][nPosY] = 'X';
                                                return;
                                        }
                                        else {
                                                (*cGrid)[nPosX][nPosY] = 'X';
                                                nPosY -= nVertical;
                                                y -= 1;
                                        }
                                }
                        }
                }   
                if (nTargetX > nPosX)
                        nHorizontal = 1;
                else if (nTargetX < nPosX)
                        nHorizontal = -1;
                        
                //tries to get closer to the target horizontally while avoiding obstacles
                for (x = 0; x != abs(nTargetX - nCurPos[0]); x++ ) {
                        nPosArr[0] = nPosX;
                        nPosArr[1] = nPosY;
                        
                        //break out of loop when it has reached its desired destination
                        if (ifInRange (*cGrid, cSearchObject, nPosArr) == 1)
                                break;
                                
                        if ((*cGrid)[nPosX + nHorizontal][nPosY] == cPathObj && (nPosX <= nGrid[0] && nPosX >=0)) {
                                nPosX += nHorizontal;
                                (*cGrid)[nPosX][nPosY] = '*';
                        } else if ((*cGrid)[nPosX + nHorizontal][nPosY] != cSearchObject) {
                                if ((*cGrid)[nPosX][nPosY + 1] == cPathObj  && (nPosY + 1) <= nGrid[1]) {
                                        nPosY += 1;
                                        (*cGrid)[nPosX][nPosY] = '*';
                                        x -= 1;
                                } else if ((*cGrid)[nPosX][nPosY - 1] == cPathObj && (nPosY - 1) >= 0) { //if up is not empty, try down.
                                        nPosY -= 1;
                                        (*cGrid)[nPosX][nPosY] = '*';
                                        x -= 1; //reset x to previous value to redo the thingy
                                } else { //if neither works, move 1 space backwards and label it as a trap (X)
                                        if (ifInRange(*cGrid, 'R', nPosArr) == 1 && ifInRange(*cGrid, 'X', nPosArr)) {
                                                (*cGrid)[nPosX][nPosY] = 'X';
                                                return;
                                        }
                                        else {
                                                (*cGrid)[nPosX][nPosY] = 'X';
                                                nPosY -= nVertical;
                                                y -= 1;
                                        }
                                }
                        } 
                }            
        }
}

/*  Determiens if the game will run on Manual Mode or Fast Mode

     @param  (char) cChoice  the character representing the mode that the user input.

     @return  (void) no return value

*/ 
void
mode (char cChoice)
{
        switch (cChoice) {
        case 'F': 
        case 'f':
                sleep (1);
                break;
        case 'M':
        case 'm':
                printf ("\nPress Enter to Continue\n\n");
                while ( getchar() != '\n' );
        }
}
#endif
