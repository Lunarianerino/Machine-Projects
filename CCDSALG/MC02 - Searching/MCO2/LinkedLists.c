/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	LinkedLists.c: The file contains all the functions needed for creating and manipulating linked lists in the program
*
* Last Modified: 09/12/2022
* Acknowledgements: 
*       Adaptation & Modification of Hashing Function - https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
*/

#include "LinkedLists.h"


/**
 * @brief Allocate memory for a linked list
 * 
 * @return LinkedList* is the created linked list object after memory allocation
 */
LinkedList * allocate_list () {
    // Allocates memory for a Linkedlist pointer
    LinkedList * list = (LinkedList*) malloc (sizeof(LinkedList));

    return list;
}

/**
 * @brief Insert a bucket inside a linked list
 * 
 * @param head is the head of the linked list
 * @param bucket is the bucket to be inserted in the linked list
 * @return LinkedList* is the linked list which contains the inserted bucket
 */
LinkedList * linkedlist_insert(LinkedList* head, Bucket* bucket) 
{
    //Linked list at key currently looks like this:
    // [THING] - [?] - [?] - [?]
    
    //Get the bucket which has a NULL value connected next to it
    LinkedList* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    
    //Insert the NEW bucket to the NULL value pointer
    LinkedList* node = allocate_list();
    node->bucket = bucket;
    node->next = NULL;
    temp->next = node;
        
    return head;
}


/**
 * @brief Free the memory allocated for the linked list and delete it.
 * 
 * @param list is the linked list to delete.
 */
void free_linkedlist(LinkedList* list) {

    //Go through all the buckets in the linked list and free the memory used.
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->bucket->key);
        free(temp->bucket->element);
        free(temp->bucket);
        free(temp);
    }
}
