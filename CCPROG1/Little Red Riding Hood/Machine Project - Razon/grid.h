#define INV_SLOTS 20
void    displayGrid         (char cGrid[15][15], 
                            int nGrid[2]);
void    assignGrid          (char (*cGrid)[15][15], 
                            int nGrid[2], 
                            char cObject);
void    displayCounters     (int nCounters[3]);
void    displayDirection    (int nDirection);
void    displayInventory    (char cInventory[INV_SLOTS]);
void    displaySense        (char cSense);
void    displayAction       (char cAction);
void    displayLegend       ();
void    displayAll          (char cGrid[15][15], 
                            int nGrid[2], 
                            int nCounters[3], 
                            int nDirection, 
                            char cSense, 
                            char cInventory[INV_SLOTS],
                            char cAction);
void    drawGrid            (char (*cExploredGrid)[15][15], 
                            int nDirection, 
                            int nCurPos[2], 
                            char cSense,
                            char cAction);
void    createRoute         (char (*cGrid)[15][15],
                            int nGrid[2],
                            int nCurPos[2],
                            char cSearchObject,
                            char cPathObj);
void    mode                (char cChoice);