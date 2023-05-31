#if !defined(WOODSMAN_H) //redefinition error if this is not included
#define WOODSMAN_H

#include "woodsman.h"
#define INV_SLOTS 20

/*  Returns the distance between LRRH and Granny if the Woodsman is already acquired.

     @param  (char) cGrid[15][15]  is the array representing the board containing the elements. Used to get Granny's location.
     @param  (char) cInventory[INV_SLOTS]  is the array representing the contents of LRRH's inventory to check if the Woodsman is present.
     @param  (int) nGrid[2]  is the array representing the maximum range of the board.
     @param  (int) nCurPosX  is the current position of LRRH in the X axis.
     @param  (int) nCurPosY  is the current position of LRRH in the Y axis.

     @return  (int)  returns the distance between LRRH and Granny.

*/ 
int
woodsmanGuide (char cGrid[15][15], 
                    char cInventory[INV_SLOTS], 
                    int nGrid[2], 
                    int nCurPosX, 
                    int nCurPosY) 
{
        int nGrannyX, nGrannyY;
        int nHasWoodsman = 0; //0 = False, 1 = True;
        char cItem;
        int nSteps = -1; //returns -1 if there is no woodsman
        int x, y, nSlot; //for the for loops

        //checks if woodsman is in inventory
        for (nSlot = 0; nSlot <= INV_SLOTS; nSlot++) {
                cItem = cInventory[nSlot];
                if (cItem != '\0') {
                        if (cItem == 'L') {
                                nHasWoodsman = 1;
                                break;
                        }
                } else 
                        break;
        }

        //if woodsman is in inventory, if true, get Granny's distance and print.
        if (nHasWoodsman == 1) {
                for (y = 0; y <= nGrid[1]; y++) {
                        for (x = 0; x <= nGrid[0]; x++) {
                                if (cGrid[x][y] == 'G') {
                                        nGrannyX = x;
                                        nGrannyY = y;
                                        break;
                                }
                        }
                }

                nSteps = abs(nCurPosX - nGrannyX) + abs(nCurPosY -  nGrannyY);
                printf ("Woodsman: \"%d more steps until we reach Granny's House\"\n", nSteps);
        
        }
        return nSteps;
}

#endif