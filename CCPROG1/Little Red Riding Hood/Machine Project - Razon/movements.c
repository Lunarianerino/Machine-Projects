#if !defined(MOVEMENTS_H) //redefinition error if this is not included
#define MOVEMENTS_H

#include "movements.h"
#define INV_SLOTS 20 


/*  Changes the direction LRRH is facing depending on which direction she rotates. -1 for rotating leftwards, +1 for rotating rightwards

     @param  (int) nDirection  is the variable representing the direction LRRH is currently facing. 0 = Left, 1 = Up, 2 = Right, 3 = Left.
     @param  (char) cRotation  is the character that would indicate if LRRH is rotating towards the left or the right. 'l' for left, 'r' for right.

     @return  (int)  returns the new direction LRRH is facing.

*/ 
int 
rotate (int nDirection, 
        char cRotation) 
{
        switch (cRotation) {
        case 'l':
                nDirection -= 1;
                break;

        case 'r':
                nDirection += 1;
                break;
        }

        //to make sure value stays between 0 - 3
        if (nDirection >= 4)
                nDirection -= 4;
        else if (nDirection < 0)
                nDirection += 4;
    
        return nDirection;
}

/*  Moves LRRH forward by adding or subtracting 1 from her current position depending on where she is facing.

     @param  (char*) cGrid[15][15]  the grid where LRRH's position will be changed when she goes forward.
     @param  (int*) nCurPos[2]  the array representing the position of LRRH in X and Y coordinates. nCurPos[0] = X, [1] = Y.
     @param  (int) nDirection  the integer representing the direction where LRRH will move forward to.
     @param  (char*) cInventory[INV_SLOTS]  the array representing the inventory for when LRRH goes to a spot with an object present.

     @return  (void)  no return value

*/ 
void
forward (char (*cGrid)[15][15],  
            int (*nCurPos)[2], 
            int nDirection, 
            char (*cInventory)[INV_SLOTS]) 
{
        char cSense;
        int nX = (*nCurPos)[0], nY = (*nCurPos)[1], nSlot;

        //Return the object that LRRH is stepping on to its original location
        switch ((*cGrid)[nX][nY]) {
        case '!':
                (*cGrid)[nX][nY] = 'W';
                break;
        case 'b':
                (*cGrid)[nX][nY] = 'B';
                break;
        case 'f':
                (*cGrid)[nX][nY] = 'F';
                break;
        case 'l':
                (*cGrid)[nX][nY] = 'L';
                break; 
        case 'R':
                (*cGrid)[nX][nY] = '_';
                break;
        }

        //adjust the position based on the direction
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

        //if there is something in front of LRRH before moving forward, put that item in the Backpack
        cSense = sense ((*cGrid), nDirection, *nCurPos);
        //for putting the detected object to an empty space in the inventory array
        if (cSense != ' ' && cSense != '_') {
                for (nSlot = 0; nSlot <= INV_SLOTS; nSlot++) {
                        if ((*cInventory)[nSlot] == '_' || (*cInventory)[nSlot] == '\0') {
                                (*cInventory)[nSlot] = cSense;
                                break;
                        }
                }
        }

        //Initializing Red to Current Position
        switch ((*cGrid)[nX][nY]) {
        case 'W':
                (*cGrid)[nX][nY] = '!';
                break;
        case 'B':
                (*cGrid)[nX][nY] = 'b';
                break;
        case 'F':
                (*cGrid)[nX][nY] = 'f';
                break;
        case 'L':
                (*cGrid)[nX][nY] = 'l';
                break; 
        case '_':
                (*cGrid)[nX][nY] = 'R';
                break;
        }
        (*nCurPos)[0] = nX;
        (*nCurPos)[1] = nY;

}

/*  Returns the character representing the object that is in front of LRRH when this function is called.

     @param  (char) cGrid[15][15]  is the array representing the board containing the elements in order to know if there is something in front of LRRH
     @param  (int) nDirection  is the integer representing the direction LRRH is facing to know what direction LRRH is going to use sense on.
     @param  (int) nCurPos[2]  is the array representing LRRH's position to avoid having to find LRRH's position in the board everytime this function is called.

     @return  (char)  returns the character representing the object sensed in front.

*/ 
char
sense (char cGrid[15][15], 
        int nDirection, 
        int nCurPos[2]) 
{
        char cSensed;
        int nX = nCurPos[0];
        int nY = nCurPos[1];

        if (nDirection >= 4)
                nDirection -= 4;
        else if (nDirection < 0)
                nDirection += 4;
    
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
        cSensed = cGrid[nX][nY];
        return cSensed;
}
#endif