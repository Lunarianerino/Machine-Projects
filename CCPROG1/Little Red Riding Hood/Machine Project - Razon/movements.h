#define INV_SLOTS 20
int     rotate          (int nDirection, 
                        char cRotation);
void    forward         (char (*cGrid)[15][15],  
                        int (*nCurPos)[2], 
                        int nDirection,
                        char (*cInventory)[INV_SLOTS]);
char    sense           (char cGrid[15][15], 
                        int nDirection, 
                        int nCurPos[2]);