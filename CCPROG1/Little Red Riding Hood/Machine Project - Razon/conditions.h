#define INV_SLOTS 20
int     checkConditions     (char (*cInventory)[INV_SLOTS]);

int     isValidStep         (int nGrid[2], 
                            int nDirection, 
                            int nCurPos[2]);

int     isSafe              (char cSense);

int     ifInRange           (char cGrid[15][15], 
                            char cObject, 
                            int nPos[2]);
int     hasValidPath        (char cGrid[15][15],
                            int nGrid[2],
                            char cObject);
int     hasValidPathCoords  (char cGrid[15][15],
                            int nGrid[2],
                            int nPos[2]);
int     countElement        (char cGrid[15][15], 
                            int nGrid[2], 
                            char cObject);
int     convertToDigit      (char sDigit[2]);
int     ifHasWolf           (char cGrid[15][15], 
                            int nGrid[2], 
                            char cObject); 

