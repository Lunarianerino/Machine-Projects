#include "behavior.h"
#include "conditions.c"
#include "movements.c"
#include "grid.c"
#include "woodsman.c"

#include <unistd.h>
#define INV_SLOTS 20

/*  Function that carries on the actions LRRH would perform based on specific conditions. Also contains a new board where it is filled with the knowledge LRRH has gathered while going through the board.

     @param  (char*) cGrid[15][15]  is the board where LRRH will be playing which contains the elements and their positions.
     @param  (int) nGrid[2]  is the array representing the maximum range of the board to emulate a seperate empty board with the same dimensions.
     @param  (char) cMode  is the character that dictates if the game will run on Fast Mode or Manual Mode.
     
     @return  (void)  no return value

*/
void 
startSimulation (char (*cGrid)[15][15], 
                    int nGrid[2],
                    char cMode)
{
        int nCurDistance; //distance to granny relative to current position
        int nCondition = 0; //0 = Game is still going on, 1 = Win, 2 = Lose
        char cSense = '\0';
        int nCurPos[2]; //Current Position of RRH
        nCurPos[0] = 0;
        nCurPos[1] = 0;
        
        char cPreviousRotation = 'r';
        char cAction = '\0';
        char cConReason;

        int nDirection = 1, nPastDirection; //0 = Left, 1 = Up, 2 = Right, 3 = Down

        char cInventory[INV_SLOTS];
        int nSlot; //for the for loop



        //Inventory Set=up
        for (nSlot = 0; nSlot <= INV_SLOTS; nSlot++) //setting all slots to NULL cus they have a random assignment, makes for easier checking
                cInventory[nSlot] = '\0'; //NULL character, setting to NULL itself results in a warning
        

        int nCounters[3]; //[0] Forward, [1] Rotate, [2] Sense
        nCounters[0] = 0;
        nCounters[1] = 0;
        nCounters[2] = 0;


        char cExploredGrid[15][15];
        int x, y; //for the for loops

        for (x = 0; x <= nGrid[0]; x++) {
                for (y = 0; y <= nGrid[1]; y++)
                        cExploredGrid[x][y] = ' ';
        }
        
        cExploredGrid[0][0] = 'R'; //initializing Red's position
        //decision making loop
        while (nCondition == 0){
                nCurDistance = woodsmanGuide (*cGrid, cInventory, nGrid, nCurPos[0], nCurPos[1]);
                cAction = judgement (cExploredGrid, nGrid, nDirection, nCurPos, &cPreviousRotation, cInventory, nCurDistance);
                nPastDirection = nDirection;

                //actions to perform based on judgement
                switch (cAction){
                case 'f':
                        forward (&(*cGrid), &nCurPos, nDirection, &cInventory);
                        nCounters[0] += 1;
                        drawGrid (&cExploredGrid, nDirection, nCurPos, cSense, cAction);
                        break;

                case 'r':
                case 'l':
                        nDirection = rotate (nDirection, cAction);
                        nCounters[1] += 1;
                        break;
                case 's':
                        cSense = sense (cExploredGrid, nDirection, nCurPos);
                        //if LRRH does not know what is in front, this is the only time when she will use "sense" on the official game board.
                        if (cSense == ' ') {
                                cSense = sense (*cGrid, nDirection, nCurPos);
                                nCounters[2] += 1;
                                drawGrid (&cExploredGrid, nDirection, nCurPos, cSense, cAction);
                        }
                        break;
                case 'c': //creates route towards blank space if trapped
                        createRoute (&cExploredGrid, nGrid, nCurPos, ' ', 'o');
                        break;
                case 'g': //creates a route towards granny (only goes thru places shes been in already)
                        createRoute (&cExploredGrid, nGrid, nCurPos, 'G', 'o');
                        break;
                        //this crashes, try adding nGrid limits to the route creation, maybe thats hwy it crashes
                case 'w': 
                        for (y = 0; y <= nGrid[1]; y++) {
                                for (x = 0; x <= nGrid[0]; x++)
                                        if (cExploredGrid[x][y] == 'W') {
                                                cExploredGrid[x][y] = 'o';
                                                break;
                                        }
                        }
                        break;
                
                case 'b': //creates a route towards bread
                        createRoute (&cExploredGrid, nGrid, nCurPos, 'B', 'o');
                }

                printf ("\nMemory View: \n");
                displayGrid (cExploredGrid, nGrid);
                printf ("Player View: \n"); //make a display all function
                displayAll (*cGrid, nGrid, nCounters, nDirection, cSense, cInventory, cAction);
                cSense = ' ';
                
                //if LRRH or Granny is not trapped, check win conditions
                if (cAction != 'e' && cAction != 't')
                        nCondition = checkConditions (&cInventory);
                else {
                        nCondition = 1;
                        if (cAction == 'e')
                                printf ("YOU LOST! \n\tIt is not possible to reach Granny.");
                        else if (cAction == 't')
                                printf ("YOU LOST! \n\tLittle Red Riding Hood is trapped.");        
                }

                if (nCondition == 0) {
                        mode (cMode);
                } else {
                        printf ("\nPress Enter to Exit\n\n");
                        while ( getchar() != '\n' );
                        exit(0);
                }
        }
}


/*  Function that judges the best possible action for LRRH to perform depending on specific conditions.

     @param  (char) cExploredGrid[15][15]  is the board containing LRRH's knowledge on her previous encounters and its lcoations.
     @param  (int) nGrid[2]  is the array representing the maximum range of the board to check the borders.
     @param  (int) nDirection  is the integer that determines what direction LRRH is facing.
     @param  (int) nCurPos[2]  is the array containing LRRH's current position on the baord.
     @param  (char*) cPrevRotation  contains the character representing the way LRRH last rotated.
     @param  (char) cInventory[INV_SLOTS]  is the array containing the objects LRRH has encountered and picked up.
     @param  (int*) nPrevDistance  is the previous distance between LRRH and Granny taken from the previous loop.
     @param  (int) nCurDistance  is the current distance between LRRH and Granny taken from the newly called function before calling this function.

     @return  (char)  returns the character representing the action that LRRH will do. f = forward, l = turn left, r = turn right, s = sense, c = create a path towards a blank tile, g = create a path towards granny, e = end game due to Granny being trapped, t = end game due to Red being trapped, w = ignore wolf (make him safe), b = creates route towards bread

*/
char 
judgement (char cExploredGrid[15][15], 
                int nGrid[2],  
                int nDirection, 
                int nCurPos[2], 
                char *cPrevRotation, 
                char cInventory[INV_SLOTS], 
                int nCurDistance)
{

        char cAction;

        //Dependent on Memory of her surroundings
        char cSenseFront, cSenseLeft, cSenseRight, cSenseBack; //the value of what Red knows is in front (' ' if she doesn't)

        //if forward, or rotating is safe. 1 = True, 0 = False
        int nSafeL, nSafeR, nSafeF, nSafeB;

        //if forward, or rotating is valid. 1 = True, 0 = False
        int nValidF, nValidR, nValidL, nValidB;

        int nHasBread = 0, nHasFlower = 0, nHasMan = 0; //1 = True, 0 = False

        int nBreadAmount = 0;

        int nGrannyX = -1, nGrannyY = -1; //Position of granny, -1 if unknown

        int nSlot, x, y;

        int nDistToUnknown = 100, nCoordToUnknown[2]; //Distance and coordinates towards to the closest unknown square
       
        //checks if Bread, Woodsman, and Flower is present in the inventory
        for (nSlot = 0; nSlot <= INV_SLOTS; nSlot++) {
                if (cInventory[nSlot] != '\0') {
                        if (cInventory[nSlot] == 'B') {
                                nHasBread = 1;
                                nBreadAmount ++;
                        }
                        if (cInventory[nSlot] == 'L')
                                nHasMan = 1;
                        if (cInventory[nSlot] == 'F')
                                nHasFlower = 1;
                } else {
                        break;
                }
        }


        printf ("Thought: \n");
        //[GATHERING DATA that is already known to LRRH. Unknown data are represented as whitespaces (' ').]
        //Front and Back: Checking if it is valid and what objects are in it.
        cSenseFront = sense (cExploredGrid, nDirection, nCurPos);
        cSenseBack = sense (cExploredGrid, (nDirection + 2), nCurPos);
        nValidF = isValidStep (nGrid, nDirection, nCurPos);
        nValidB = isValidStep (nGrid, (nDirection + 2), nCurPos);

        //Left and Right: Checking if it is valid and what objects are in it.
        //NOTE: Left and Right are inverted when facing downwards
        if (nDirection == 3) {
                cSenseLeft = sense (cExploredGrid, (nDirection + 1), nCurPos);
                cSenseRight = sense (cExploredGrid, (nDirection - 1), nCurPos);
                nValidL = isValidStep (nGrid, (nDirection + 1), nCurPos);
                nValidR = isValidStep (nGrid, (nDirection - 1), nCurPos);
        } else {
                cSenseLeft = sense (cExploredGrid, (nDirection - 1), nCurPos);
                cSenseRight = sense (cExploredGrid, (nDirection + 1), nCurPos);
                nValidL = isValidStep (nGrid, (nDirection - 1), nCurPos);
                nValidR = isValidStep (nGrid, (nDirection + 1), nCurPos);       
        }

        //Checking if it is safe (not wolf or pit or invalid) around LRRH (depending on what she currently knows).
        nSafeF = isSafe (cSenseFront);
        nSafeL = isSafe (cSenseLeft);
        nSafeR = isSafe (cSenseRight);
        nSafeB = isSafe (cSenseBack);

        //[END OF GATHERING DATA]


        
        //If a route is present, prioritize the route. (only creates route when it is stuck or when she knows where granny is and is about to end the game.)
        if (cSenseFront == '*') {
                printf ("I am following the route I created.");
                cAction = 'f';
        }
        else if (cSenseFront == 'B' || cSenseFront == 'F' || cSenseFront == 'L') {
                printf ("I sense an item here, going forward.");
                cAction = 'f';
        }
        else if (cSenseRight == '*') {
                printf ("I am following the route I created.");
                cAction = 'r';
        }
        else if (cSenseLeft == '*') {
                printf ("I am following the route I created.");
                cAction = 'l';
        }
        else if (cSenseBack == '*') {
                printf ("I am following the route I created.");
                cAction = *cPrevRotation;
        }
        else if (nValidF == 1) { 
                printf("I can take a step FORWARD, there I assess the situation further.\n");
                if (cSenseFront == ' ') {
                        //If wherever Red is facing is unknown, sense
                        printf ("I do not know what is in front, therefore I use SENSE\n");
                        cAction = 's';
                } else if (cSenseFront == 'G') {
                        //If Red is facing Grandma
                        if (nHasFlower == 1 && nHasBread == 1 && nHasMan == 1) {
                                //If Red has all the requirements, goes forward and ends game
                                printf ("I have everything. Going to Granny now\n");
                                cAction = 'f';
                        } else {
                                printf ("I still lack something. I'm going to ROTATE and come back later.\n");
                                if (nSafeR == 1 && nSafeL == 0) {
                                        //If Turning RIGHT is Safe while Turning LEFT is not, return Right
                                        printf ("I have decided that turning RIGHT is the best option.\n");
                                        cAction = 'r';
                                } else if (nSafeL == 1 && nSafeR == 0) {
                                        //If Turning LEFT is Safe and Valid while Turning RIGHT is not, return Right
                                        printf ("I have decided that turning LEFT is the best option.\n");
                                        cAction = 'l';
                                } else {
                                        printf("Anywhere I turn is valid, therefore I shall turn towards the last direction I turned");
                                        cAction = *cPrevRotation;
                                }
                                //cAction = *cPrevRotation;
                        }
                } else { 
                        if (nHasFlower == 1 && nHasBread == 1 && nHasMan == 1) {
                                printf("I have everything now \n");
                                //Scanning on known positions if Granny's Location has been discovered
                                for (y = 0; y <= nGrid[1]; y++) {
                                        for (x = 0; x <= nGrid[0]; x++)
                                                if (cExploredGrid[x][y] == 'G') {
                                                        nGrannyX = x;
                                                        nGrannyY = y;
                                                        break;
                                                }
                                }
                                if (nGrannyX == -1 && nGrannyY == -1) { // If the location of Granny is unknown, go to nearest blank tile
                                        //If there is one empty element remaining
                                        if (countElement(cExploredGrid, nGrid, ' ') == 1) {
                                                //if a path can be generated towards that last available tile, else, check if LRRH has 2 bread.
                                                printf ("There is only one unknown tile remaining and I do not know where Granny is so that must be her location...\n");
                                                if (hasValidPath(cExploredGrid, nGrid, ' ') == 1) {
                                                        if (cSenseRight == ' ')
                                                                cAction = 'r';
                                                        else if (cSenseLeft == ' ')
                                                                cAction = 'l';
                                                        else if (cSenseBack == ' ')
                                                                cAction = *cPrevRotation;
                                                        else {
                                                                printf ("Creating path towards that tile now.\n");
                                                                cAction = 'c';
                                                        }
                                                } else {
                                                        if (nBreadAmount > 1) {
                                                                //check if one of the things surrounding Granny is the Wolf
                                                                if (ifHasWolf(cExploredGrid, nGrid, ' ') == 1)
                                                                        cAction = 'w';
                                                                else {
                                                                        printf ("That tile is surrounded, there is no way I am getting to Granny like this.\n");
                                                                        cAction = 'e';
                                                                }

                                                        } else {
                                                                if (cExploredGrid[nCurPos[0]][nCurPos[1]] == 'b') {
                                                                        printf ("I need more bread, but I am already standing in a bakeshop...");
                                                                        if (cSenseFront == ' ' || cSenseFront == 'o')
                                                                                cAction = 'f';
                                                                        else if (cSenseRight == ' ' || cSenseRight == 'o')
                                                                                cAction = 'r';
                                                                        else if (cSenseLeft == ' ' || cSenseLeft == 'o')
                                                                                cAction = 'l';
                                                                        else if (cSenseBack == ' ' || cSenseBack == 'o')
                                                                                cAction = *cPrevRotation;
                                                                        else {
                                                                                printf ("Creating path towards that tile now.\n");
                                                                                cAction = 'c';
                                                                        }
                                                                } else {
                                                                        if (cSenseFront == 'B' )
                                                                                cAction = 'f';
                                                                        else if (cSenseRight == 'B')
                                                                                cAction = 'r';
                                                                        else if (cSenseLeft == 'B')
                                                                                cAction = 'l';
                                                                        else if (cSenseBack == 'B')
                                                                                cAction = *cPrevRotation;
                                                                        else {
                                                                                printf ("Creating path towards the bakeshop now.\n");
                                                                                cAction = 'b';
                                                                        }
                                                                }
                                                        }
                                                }
                                        } else if (nCurDistance == 1) { //If granny is in the vicinity, according to the woodsman
                                                if (cSenseRight == ' ')
                                                        cAction = 'r';
                                                else if (cSenseLeft == ' ')
                                                        cAction = 'l';
                                                else if (cSenseBack == ' ')
                                                        cAction = *cPrevRotation;
                                        
                                        } else if (cSenseFront == '_')
                                                cAction = 'f';
                                        else if (cSenseRight == ' ')
                                                cAction = 'r';
                                        else if (cSenseLeft == ' ')
                                                cAction = 'l';
                                        else if (cSenseBack == ' ')
                                                cAction = *cPrevRotation;
                                        else {
                                                printf ("Creating path towards blank tiles now\n");
                                                cAction = 'c';
                                        }   //if there is no blank tiles anywhere, create route to blank tile
                                } else if (nGrannyX != -1 && nGrannyY != -1) {
                                                //if Red knows Granny's Location, create route going to Granny.
                                                printf ("I know where Granny is. Creating Path to her now.");
                                                if (ifInRange(cExploredGrid, 'G', nCurPos) == 1) {//If granny is around LRRH, rotate to Granny
                                                        if (cSenseRight == 'G') //Front not included since it checks if Granny is in front first.
                                                                cAction = 'r';
                                                        else if (cSenseLeft == 'G')
                                                                cAction = 'l';
                                                        else if (cSenseBack == 'G')
                                                                cAction = *cPrevRotation;
                                                } else  
                                                        cAction = 'g'; 
                                        }
                                               
                        } else { //LRRH doesnt have everything
                                //If there is one empty element remaining
                                if (countElement(cExploredGrid, nGrid, ' ') == 1) {
                                        //if a path can be generated towards that last available tile, else, end game.
                                        printf ("There is only one unknown tile remaining and I still lack something, so I go to that unknown tile\n");
                                        if (hasValidPath(cExploredGrid, nGrid, ' ') == 1) {
                                                if (cSenseRight == ' ')
                                                        cAction = 'r';
                                                else if (cSenseLeft == ' ')
                                                        cAction = 'l';
                                                else if (cSenseBack == ' ')
                                                        cAction = *cPrevRotation;
                                                else {
                                                        printf ("Creating path towards that tile now.\n");
                                                        cAction = 'c';
                                                }
                                        } else {
                                                //it requires 2 bread to get past wolf to get item, then leaving, and an extra is required for Granny
                                                if (nBreadAmount > 2) {
                                                        //check if one of the things surrounding the object is the Wolf
                                                        if (ifHasWolf(cExploredGrid, nGrid, ' ') == 1) {
                                                                printf ("A wolf is blocking the path and I have enough bread to go in and out...");
                                                                cAction = 'w';
                                                        }
                                                        else {
                                                                printf ("That tile is surrounded, there is no way I am getting to Granny like this.\n");
                                                                cAction = 'e';
                                                        }

                                                } else {
                                                        if (nHasBread == 1) { //if LRRH has atleast 1 bread, it means she knows where the Bread is, therefore make route to get more bread
                                                                if (cSenseRight == 'B')
                                                                        cAction = 'r';
                                                                else if (cSenseLeft == 'B')
                                                                        cAction = 'l';
                                                                else if (cSenseBack == 'B')
                                                                        cAction = *cPrevRotation;
                                                                else {
                                                                        //If Red is already in the bread space
                                                                        if (cExploredGrid[nCurPos[0]][nCurPos[1]] == 'b') {
                                                                                printf ("I need more bread, but I am already standing in a bakeshop...");
                                                                                if (cSenseFront == ' ' || cSenseFront == 'o')
                                                                                        cAction = 'f';
                                                                                else if (cSenseRight == ' ' || cSenseRight == 'o')
                                                                                        cAction = 'r';
                                                                                else if (cSenseLeft == ' ' || cSenseLeft == 'o')
                                                                                        cAction = 'l';
                                                                                else if (cSenseBack == ' ' || cSenseBack == 'o')
                                                                                        cAction = *cPrevRotation;
                                                                                else {
                                                                                        printf ("Creating path towards that tile now.\n");
                                                                                        cAction = 'c';
                                                                                }
                                                                        } else {
                                                                                printf ("Creating path towards the bakeshop now.\n");
                                                                                cAction = 'b';
                                                                        }
                                                                }
                                                        } else {
                                                                printf ("There is no way for me to get the last item needed, I automatically lose.\n");
                                                                cAction = 'e';
                                                        }
                                                }
                                        }
                                } else if (cSenseFront == 'o') {
                                        //if where Red is facing has already been travelled to before, consider rotating
                                        printf("I've been here before... Assessing my options... \n");
                                        if (cSenseRight != 'o' && nSafeR == 1 && cSenseRight != 'G' && nValidR == 1) {
                                                //If Turning RIGHT is Safe while Turning LEFT is not, return Right
                                                //Granny is not considered "safe" here since it has been established that Red does not have the materials yet.
                                                printf ("I have decided that turning RIGHT is the best option.\n");
                                                cAction = 'r';
                                        } else if (cSenseLeft != 'o' && nSafeL == 1 && cSenseLeft != 'G' && nValidL == 1) {
                                                //If Turning LEFT is Safe and Valid while Turning RIGHT is not, return Right
                                                printf ("I have decided that turning LEFT is the best option.\n");
                                                cAction = 'l';
                                        } else if (cSenseBack != 'o' && nSafeB == 1 && cSenseBack != 'G' && nValidB == 1) {
                                                //If left/right is invalid/ventured, check backwards
                                                printf ("Back is safe, rotating backwards now.");
                                                cAction = *cPrevRotation;
                                        } else {
                                                //If everywhere has already been ventured/invalid, go to nearest unknown tile.
                                                //creates route to nearest unknown tile (Only applies to cExploredGrid; the only route it takes towards the unknown tile is thru the ones it already took)
                                                printf ("I am trapped. Creating path towards blank tiles now.\n");
                                                cAction = 'c';
                                        }
                                } else if (nSafeF == 0) {
                                        //If Front is dangerous, consider ROTATING
                                        printf ("It is dangerous up ahead, therefore I think of what will happen when I ROTATE\n");
                                        
                                        if (nSafeR == 1 && (nSafeL == 0 || nValidL == 0)) {
                                                //If Turning RIGHT is Safe while Turning LEFT is not, return Right
                                                printf ("I have decided that turning RIGHT is the best option.\n");
                                                cAction = 'r';
                                        } else if (nSafeL == 1 && (nSafeR == 0 || nValidR == 0)) {
                                                //If Turning LEFT is Safe and Valid while Turning RIGHT is not, return Right
                                                printf ("I have decided that turning LEFT is the best option.\n");
                                                cAction = 'l';
                                        } else {
                                                //If turning EITHER WAY is dangerous or safe
                                                printf ("Looks like turning either way is");
                                                if (nSafeL == 0 && nSafeR == 0) {
                                                        //If Turning either way is dangerous, Check if back is safe, no need to check if valid
                                                        printf (" DANGEROUS, therefore I'll check if behind me is safe\n");
                                                        if (nSafeB == 1) {
                                                                //If back is safe, rotate
                                                                printf ("It is safe behind me, therefore I'll slowly rotate back\n");
                                                                cAction = *cPrevRotation;
                                                        } else {
                                                                //Everwhere is not safe
                                                                printf ("It is not safe or valid anywhere, I am trapped, I give up...\n");
                                                                cAction = 't';
                                                        }
                                                } else if (nSafeL == 1 && nSafeR == 1) {
                                                        //If turning either way is safe, rotate left if previously rotated left and right if right.
                                                        printf (" SAFE, therefore I keep turning the way I was turning. \n");
                                                        cAction = *cPrevRotation;
                                                }
                                        } 
                                } else {
                                        //If front is safe and valid, not grandma, and still has incomplete requirements, go forward
                                        printf("Going FORWARD is safe, therefore I go on.");
                                        cAction = 'f';
                                }
                        }
                }
        } else {
                printf ("I cannot move forward, therefore I rotate.\n");
                if ((nSafeR == 1 && nValidR == 1) && nSafeL == 0 || nValidL == 0) {
                        //If Turning RIGHT is Safe while Turning LEFT is not, return Right
                        printf ("I have decided that turning RIGHT is the best option.");
                        cAction = 'r';
                } else if ((nSafeL == 1 && nValidL == 1) && nSafeR == 0 || nValidR == 0) {
                        //If Turning LEFT is Safe and Valid while Turning RIGHT is not, return Right
                        printf ("I have decided that turning LEFT is the best option.");
                        cAction = 'l';
                } else {
                        //If turning EITHER WAY is dangerous or safe
                        printf ("Looks like turning either way is");
                        if (nSafeL == 0 && nSafeR == 0) {
                                //If Turning either way is dangerous, Check if back is safe, no need to check if valid
                                printf (" DANGEROUS, therefore I'll check if behind me is safe\n");
                                if (nSafeB == 1) {
                                        //If back is safe, rotate
                                        printf ("It is safe behind me, therefore I'll slowly rotate back\n");
                                        cAction = *cPrevRotation;
                                } else {
                                        //Everwhere is not safe
                                        printf ("It is not safe or valid anywhere, Accepting Fate...\n");
                                        cAction = 'f';
                                }
                        } else if (nSafeL == 1 && nSafeR == 1) {
                                //If turning either way is safe, rotate left if previously rotated left and right if right.
                                printf (" SAFE, therefore I keep turning the way I was turning. \n");
                                cAction = *cPrevRotation;
                        }
                }
        }


        
        if (nDirection == 3) {
                if (cAction == 'l')
                        cAction = 'r';
                else if (cAction == 'r')
                        cAction = 'l';
        }
        if (cAction == 'r' || cAction == 'l') {
                *cPrevRotation = cAction;
        }
        return cAction;
}


