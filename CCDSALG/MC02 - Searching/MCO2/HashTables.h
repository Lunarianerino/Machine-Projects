/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	HashTables.h: The file contains the structs and prototypes used for HashTables.c
*
* Last Modified: 09/12/2022
* Acknowledgements: 
*       Adaptation & Modification of Hashing Function - https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
*/

#include "crc32.c"
#include "LinkedLists.c"
#include "murmurhash.c"
#include <string.h>

Bucket *        create_bucket       (char * key, 
                                    char * element);
HashTable*      create_table        (int size);
LinkedList**    create_bucket_lists (HashTable* table);
void            free_bucket         (Bucket* bucket);
void            free_bucket_lists   (HashTable* table);
void            ht_insert           (HashTable* table, 
                                    char* key, 
                                    char* element, 
                                    int hash_func,
                                    int* collisions);
unsigned int    hashing_function    (char* key, 
                                    int table_size, 
                                    int hash_function);