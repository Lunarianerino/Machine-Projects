/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	BST.h: The file contains the structs and prototypes used for BST.c
*
* Last Modified: 09/12/2022
* Acknowledgements: 
*/

#include "structs.h"

//STRUCTURES USED FOR BSTS
typedef struct TreeNode{
    String7 data;

    struct TreeNode* left;
    struct TreeNode* right;
} Node;

void    createBST   (Node root);
Node*   findMin     (Node* root);
Node*   insert      (Node* root, 
                    String7 x);
Node*   search      (Node* root, 
                    String7 x);
Node*   delete      (Node* root, 
                    String7 x);
void    inorder     (Node* root);
void    destroy     (Node* root);
