#if !defined(CONDITIONS_H) //redefinition error if this is not included
#define CONDITIONS_H
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "conditions.h"
#define INV_SLOTS 20

/*  Checks if LRRH has met the needed requirements to Win or Lose by the contents of her inventory.

     @param  (char*) cInventory[INV_SLOTS]  is the array representing the contents of LRRH's inventory to check if she has certain objects that would merit a win or a lose.

     @return  (int)  returns the integer representing if the game is over or continuing. 0 = Game goes on, 1 = Win, 2 = Lose

*/
int
checkConditions (char (*cInventory)[INV_SLOTS])
{ 
        //0 = None, 1 = Win, 2 = Lose
        int nCheckFlower = 0, nCheckBread = 0, nCheckWolf = 0, nCheckMan = 0, nCheckGranny = 0, nCheckPit = 0; //0 = False, 1 = True
        int nBreadSlot, nWolfSlot;
        char cItem;
        int nSlot;
        for (nSlot = 0; nSlot <= INV_SLOTS; nSlot++) {
                cItem = (*cInventory)[nSlot];
                if (cItem != '\0') {
                        switch (cItem) {
                        case 'G':
                                nCheckGranny = 1;
                                break;

                        case 'L':
                                nCheckMan = 1;
                                break;

                        case 'W':
                                nCheckWolf = 1;
                                nWolfSlot = nSlot;
                                break;

                        case 'B':
                                nCheckBread = 1;
                                nBreadSlot = nSlot;
                                break; 

                        case 'P':
                                nCheckPit = 1;
                                break;
                            
                        case 'F':
                                nCheckFlower = 1;
                                break;
                        }
                } else
                        break;
        }

        //Lose Conditions
        if (nCheckWolf == 1) {
                if (nCheckBread == 1) {
                        printf ("Bread has been EATEN by the Wolf.\n");
                        (*cInventory)[nBreadSlot] = '_';
                        (*cInventory)[nWolfSlot] = '\0'; //Wolf will always be the last one anyways
                        return 0;
                } else {
                        printf ("YOU LOST! \n\tYou are EATEN by the Wolf.\n");
                        return 2;
                }
        } else if (nCheckPit == 1) {
                printf ("YOU LOST! \n\tYou FELL in a Pit.\n");
                return 2;
        } else if (nCheckGranny == 1 && (nCheckBread == 0 || nCheckFlower == 0 || nCheckMan == 0)) {
                printf ("YOU LOST! \n\tYou and Granny are EATEN by the Wolf (Reason: Missing Flower/Bread/Woodsman).\n");
                return 2;
        }

        //Win Condition
        if (nCheckGranny == 1 && nCheckBread == 1 && nCheckFlower == 1 && nCheckMan == 1) {
                printf ("YOU WIN! \n\tCongratulations on reaching Granny's House safely!\n");
                return 1;
        } else
                return 0;
}

/*  Checks if the location in front of LRRH is a valid point in the board

     @param  (int) nGrid[2]  is the array representing the maximum range of the board to check if point in front of LRRH is over the border.
     @param  (int) nDirection  is the integer representing the direction LRRH is facing to determine whether to check the Y borders or the X borders.
     @param  (int) nCurPos[2]  is the array representing the current position of LRRH.

     @return  (int)  returns 1 if the location in front of LRRH is a valid point, 0 if it is not.

*/
int
isValidStep (int nGrid[2], 
                int nDirection, 
                int nCurPos[2]) 
{
        if (nDirection >= 4)
                nDirection -= 4;
        else if (nDirection < 0)
                nDirection += 4;
        
        switch (nDirection) {
        case 0: //West
                if ((nCurPos[0] - 1) <= -1)
                        return 0;
                break;

        case 1: //North
                if ((nCurPos[1] - 1) <= -1)
                        return 0;
                break;
            
        case 2: //East
                if ((nCurPos[0] + 1) > nGrid[0])
                        return 0;
                break;
        
        case 3: //South
                if ((nCurPos[1] + 1) > nGrid[1])
                        return 0;
                break;
        }
        return 1;
}

/*  Checks if the location in front of LRRH is safe to step forward to (not wolf or pit)

     @param  (char) cSense  is the character representing the element in front of LRRH.

     @return  (int)  returns 1 if the element is considered safe, 0 otherwise.

*/
int 
isSafe (char cSense) 
{
        if (cSense == 'B' || cSense == 'o' || cSense == 'F' || cSense == '_' || cSense == 'R' ||  cSense == 'L' || cSense == ' ')
                return 1;
        else
                return 0;
}

/*  Checks if the object specified is within range (up/down/left/right)

     @param  (char) cGrid[15][15]  is the 2d array containing the game baord (usually the board representing LRRH's memory)
     @param  (char) cObject  is character that this function will search for.
     @param  (int) nPos[2]  is the array containing the position in the board where the function will look in.

     @return  (int)  returns 1 if the object is present within the vicinity, 0 otherwise.

*/
int 
ifInRange (char cGrid[15][15], 
                char cObject, 
                int nPos[2]) 
{
        //if target object is in vicinity, return 1
        int nPosX = nPos[0], nPosY = nPos[1];
        char cUp = cGrid[nPosX][nPosY - 1], cDown = cGrid[nPosX][nPosY + 1], cLeft = cGrid[nPosX - 1][nPosY], cRight = cGrid[nPosX + 1][nPosY];
        if (cUp == cObject || cDown == cObject || cLeft == cObject || cRight == cObject)
                return 1;
        else
                return 0;


}

/*  Checks if a route can be made towards the object by checking if there is a space that is safe for Red to walk to.

     @param  (char) cGrid[15][15]  is the 2d array containing the game baord (usually the board representing LRRH's memory)
     @param  (int) nGrid[2]  is the array containing the maximum range of the grid.
     @param  (char) cObject  is character that this function will search for.

     @return  (int)  returns 1 if there is a safe space around the object, 0 otherwise

*/
int
hasValidPath (char cGrid[15][15],
                int nGrid[2],
                char cObject)
{
        //checks if the object can still be passed through
        int cUp, cDown, cLeft, cRight;
        int x, y, nX, nY;
        int nPosArr[2];

        //looking for the element
        for (y = 0; y <= nGrid[1]; y++) {
                for (x = 0; x <= nGrid[0]; x++) {
                        if (cGrid[x][y] == cObject) {
                                nX = x;
                                nY = y;
                                break;
                        }
                }
        }
        nPosArr[0] = nX;
        nPosArr[1] = nY;

        cUp = (isSafe(cGrid[nX][nY - 1]) && isValidStep(nGrid, 1, nPosArr));
        cDown = (isSafe(cGrid[nX][nY + 1]) && isValidStep(nGrid, 3, nPosArr));
        cLeft = (isSafe(cGrid[nX - 1][nY]) && isValidStep(nGrid, 0, nPosArr));
        cRight = (isSafe(cGrid[nX + 1][nY]) && isValidStep(nGrid, 2, nPosArr));
        if (cUp == 1 || cDown == 1 || cLeft == 1 || cRight == 1)
                return 1;
        else
                return 0;
}

/*  Checks if a route can be made towards a specific coordinate by checking if there is a space that is safe for Red to walk to.

     @param  (char) cGrid[15][15]  is the 2d array containing the game baord (usually the board representing LRRH's memory)
     @param  (int) nGrid[2]  is the array containing the maximum range of the grid.
     @param  (int) nPos[2]  is the array containing the coordinates

     @return  (int)  returns 1 if there is a safe space around the coordinate, 0 otherwise

*/
int
hasValidPathCoords (char cGrid[15][15],
                        int nGrid[2],
                        int nPos[2])
{
        int cUp, cDown, cLeft, cRight;
        int nX = nPos[0], nY = nPos[1];
        cUp = (isSafe(cGrid[nX][nY - 1]) && isValidStep(nGrid, 1, nPos));
        cDown = (isSafe(cGrid[nX][nY + 1]) && isValidStep(nGrid, 3, nPos));
        cLeft = (isSafe(cGrid[nX - 1][nY]) && isValidStep(nGrid, 0, nPos));
        cRight = (isSafe(cGrid[nX + 1][nY]) && isValidStep(nGrid, 2, nPos));
        if (cUp == 1 || cDown == 1 || cLeft == 1 || cRight == 1)
                return 1;
        else
                return 0;
}

/*  Counts how many objects there are in the grid and returns the value

     @param  (char) cGrid[15][15]  is the 2d array containing the game baord (usually the board representing LRRH's memory)
     @param  (int) nGrid[2]  is the array containing the maximum range of the grid.
     @param  (char) cObject  is the character representing the object to be searched for.

     @return  (int)  returns the amount of objects found

*/
int
countElement (char cGrid[15][15], 
                int nGrid[2], 
                char cObject)
{
        int x, y, nCounter = 0;
        for (y = 0; y <= nGrid[1]; y++) {
                for (x = 0; x <= nGrid[0]; x++) {
                        if (cGrid[x][y] == cObject || cGrid[x][y] == '_')
                                nCounter++;
                }

        }  
        return nCounter;
}

/*  Tries to convert user input into integer

     @param  (char) sDigit[2]  is the string containing the user input

     @return  (int)  returns the converted integer

*/
int
convertToDigit (char sDigit[2]) 
{      
        int n;
        char sInt[2];
        for (n = 0; n <= 1; n++) {
                sInt[n] = sDigit[n];
        }
        //since I only need to iterate it from [0] - [1]
        for (n = 0; n <= 1; n++) {
                if (sInt[n] == '.' && isdigit (sInt[0]) != 0) //corresponds to a float
                        break;
                while (isdigit (sInt[n]) == 0) {
                        if (sInt[n] == '\0')
                                break;
                        n = 0;
                        printf ("\n\t[ERROR] Invalid input. (Only unsigned positive numbers are allowed, float gets converted to integer) \n\tEnter new coordinates: ");
                        scanf (" %2s", &sInt);
                        fflush(stdin);
                }
        }
        return atoi(sInt);
}

/*  Counts how many objects there are in the grid and returns the value

     @param  (char) cGrid[15][15]  is the 2d array containing the game baord (usually the board representing LRRH's memory)
     @param  (int) nGrid[2]  is the array containing the maximum range of the grid.
     @param  (char) cObject  is the character representing the object where the function will check for the wolf.

     @return  (int)  returns 1 if the wolf is in the vicinity, 0 otherwise

*/
int
ifHasWolf (char cGrid[15][15], 
                int nGrid[2], 
                char cObject) 
{
        char cUp, cDown, cLeft, cRight;
        int nX, nY;
        int x, y;
        for (y = 0; y <= nGrid[1]; y++) {
                for (x = 0; x <= nGrid[0]; x++) {
                        if (cGrid[x][y] == cObject) {
                                nX = x;
                                nY = y;
                                break;
                        }
                }
        }
        cUp = cGrid[nX][nY - 1];
        cDown = cGrid[nX][nY + 1];
        cLeft = cGrid[nX - 1][nY];
        cRight = cGrid[nX + 1][nY];

        if (cUp == 'W' || cDown == 'W' || cLeft == 'W' || cRight == 'W')
                return 1;
        else
                return 0;
}
#endif
