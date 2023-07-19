/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	funcs.h: The file contains the structs and prototypes used for funcs.c
*
* Last Modified: 09/12/2022
*/

#ifndef FUNCS_H_
#define FUNCS_H_

#include "BST.c"
#include "HashTables.c"
void    initializeString        (String inputString, 
                                int n);
void    generatekMers           (StringDist kMers[], 
                                String bigString, 
                                int n, 
                                int k);
void    insertkMersBST          (Node* BST,
                                String bigString, 
                                int n, 
                                int k);
void    createkMerFile          (StringDist kMers[], 
                                int k, 
                                int alg, 
                                int hash_function);
void    createBigStringFile     (String bigString);
void    createBSTDistribution   (StringDist kMers[], 
                                Node* BST);
void    insertkMersHT           (HashTable* table, 
                                StringDist kMers[], 
                                String bigString, 
                                int n, 
                                int k, int hash_func,
                                int* collisions);
void    createHTDistribution    (StringDist kMers[], 
                                HashTable *table, 
                                int n, 
                                int k, 
                                int hash_func);
#endif