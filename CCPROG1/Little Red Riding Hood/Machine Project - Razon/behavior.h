#define INV_SLOTS 20
void    startSimulation     (char (*cGrid)[15][15], 
                                int nGrid[2],
                                char cMode);
char    judgement           (char cExploredGrid[15][15], 
                            int nGrid[2], 
                            int nDirection, 
                            int nCurPos[2], 
                            char *cPrevRotation, 
                            char cInventory[INV_SLOTS], 
                            int nCurDistance);