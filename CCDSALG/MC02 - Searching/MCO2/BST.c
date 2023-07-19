/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	BST.c: The file contains all the functions needed for creating and manipulating binary search trees
*
* Last Modified: 09/12/2022
* Acknowledgements: 
*       Creating a Binary Search Tree - https://gist.github.com/harish-r/da5fc1d0a2e63e0d60b0
*/

#include "BST.h"


/**
 * @brief Create a Binary Search Tree
 * 
 * @param root is the root of the binary search tree
 */
void createBST(Node root)
{
    strcpy(root.data, "");
    root.left = NULL;
    root.right = NULL;
}

/**
 * @brief Get the minimum value in the binary search tree
 * 
 * @param root is the root of the BST
 * @return Node* a pointer to the node with the lowest value found in the BST
 */
Node* findMin(Node* root)
{
    if(root == NULL) //root has no value
    	return NULL;
    else if(root->left == NULL) //root has no left subtree, hence, the root is the lowest value
    	return root;
    else
    	return findMin(root->left); //Walk to the left of the BST
}

/**
 * @brief Insert a value in the BST
 * 
 * @param root is the root of the BST
 * @param x is the value to be inserted
 * @return Node* the node at which the value is inserted
 */
Node* insert(Node* root, String7 x)
{
    if(root == NULL){ //Allocate memory for the node at which x will be inserted to
        root = malloc(sizeof(Node) * 2); 
        strcpy(root->data, x);
        root->left = root->right = NULL;
    }
    else if(strcmp(x, root->data) <= 0) //Go to left of root if x is a lower value
        root->left = insert(root->left, x);
    else if(strcmp(x, root->data) > 0)
        root->right = insert(root->right, x); //Go to right of root if x is a higher value
   
    return root;
}


/**
 * @brief Search for a value inside the BST
 * 
 * @param root is the root of the BST
 * @param x is the value to be searched
 * @return Node* is the pointer at which the value is found. returns NULL if not found
 */
Node* search(Node* root, String7 x)
{
    if(root == NULL)
        return NULL;
    else if(strcmp(x, root->data) < 0) //Go to left of root if x is a lower value
        return search(root->left, x);
    else if(strcmp(x, root->data) > 0) //Go to right of root if x is a higher value
        return search(root->right, x);
    else //Found the value
        return root;
}

/**
 * @brief Delete a value in the BST
 * 
 * @param root is the root of the BST
 * @param x is the value to be deleted
 * @return Node* is the pointer at which the deleted value can be found
 */
Node* delete(Node* root, String7 x)
{
    Node* temp;
    if(root == NULL) //Root is null
        return NULL;
    else if(strcmp(x, root->data) < 0)  //Go to left of root if x is a lower value
        root->left = delete(root->left, x);
    else if(strcmp(x, root->data) > 0)
        root->right = delete(root->right, x); //Go to right of root if x is a higher value
    else if(root->left && root->right){ //X is equal to the root
        temp = findMin(root->right); //Get the successor of X (case 1: leftmost node at right subtree)
        strcpy(root->data, temp->data);
        root->right = delete(root->right, root->data);
    }
    else{
        //Get the successor of X (case 2: lowest ancestor of X at which x is a left children of the ancestor)
        temp = root;
        if(root->left == NULL)
            root = root->right;
        else if(root->right == NULL)
            root = root->left;
        free(temp);
    }
    return root;
}


/**
 * @brief Perform an inorder walk of the BST
 * 
 * @param root is the root of the BST
 */
void inorder(Node* root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    printf("%s", root->data); //prints nodes inorder traversal
    inorder(root->right);
}

/**
 * @brief Destroy the BST
 * 
 * @param root is the root of the BST
 */
void destroy(Node* root)
{
    //Free all values of the BST, starting from the leaves
    if(root == NULL)
        return;
    destroy(root->left);
    destroy(root->right);

    //post-order traversal deletion of nodes
    free(root->left);
    free(root->right);

    root->left = NULL;
    root->right = NULL;
}