/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	HashTables.c: This file contains the complete functions used for creating and manipulating hash tables
*
* Last Modified: 09/12/2022
* Acknowledgements: 
*       Adaptation & Modification of Hashing Function - https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
*/

#include "HashTables.h"

/**
 * @brief Create and allocate memory for a bucket object
 * 
 * @param key is the key of the bucket
 * @param element is the element stored in the bucket
 * @return Bucket * a pointer to the created bucket 
 */
Bucket* create_bucket(char* key, char* element) 
{
    // Allocates memory for the bucket object
    Bucket* bucket = (Bucket*) malloc (sizeof(Bucket));
    bucket->key = (char*) malloc (strlen(key) + 1);
    bucket->element = malloc (strlen(element) + 1);
    
    //Copy the values of the strings
    strcpy(bucket->key, key);
    strcpy(bucket->element, element);

    //Since we have allocated memory for the bucket object,
    //we can return the pointer for the object, even if it is a local variable.
    return bucket;
}

/**
 * @brief Create and allocate memory for a hash table object
 * 
 * @param size is the size of the table object
 * @return HashTable * a pointer to the created hash table
 */
HashTable* create_table(int size) {

    // Allocates memory for the Hash Table object
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    
    // Multiply the size by some abritary number for some breathing size, basically.
    // Adopted from: https://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-8.html
    table->size = (int) (size * 1.3f);
    table->count = 0;

    //Create the array of bucket_lists
    table->bucket_lists = (LinkedList**) create_bucket_lists(table);
    
    //Since we have allocated memory for the hash table object,
    //we can return the pointer for the object, even if it is a local variable.
    return table;
}


/**
 * @brief Create a bucket lists object, 
 * which is an array of linked lists for each object in the hash table
 * 
 * @param table is the hash table which will contain the bucket_lists
 * @return LinkedList** is the pointer to the allocated memory for the bucket lists
 */
LinkedList** create_bucket_lists(HashTable* table) {

    // Create the overflow buckets; an array of linkedlists
    LinkedList** buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    
    int i;
    for (i = 0; i < table->size; i++)
        *(buckets + i) = NULL;

    return buckets;
}

/**
 * @brief Free the memory used for the hash table's linked lists
 * 
 * @param table is the hash table
 */
void free_bucket_lists(HashTable* table) {

    // Get the linked lists
    LinkedList** buckets = table->bucket_lists;
    
    //Go through the linked lists
    int i;
    for (i=0; i<table->size; i++)
        free_linkedlist(buckets[i]); //Free each linked list
    
    //Free the array of linked lists itself
    free(buckets);
}

/**
 * @brief Free the memory used for the hash table
 * 
 * @param table is the hash table
 */
void free_table(HashTable* table) {
    free_bucket_lists(table);
    free(table);
}

/**
 * @brief Print the contents of the hash table for each 
 * 
 * @param table 
 */
void ht_print(HashTable * table)
{
    int i;


    //Go through the table
    for(i = 0; i < table->size; i++)
    {
        //Get the current linked list
        LinkedList * head = table->bucket_lists[i];

        if(head != NULL){
            printf("[Index: %d]=", i);
            //Keep printing the list if not null
            while(head != NULL)
            {
                printf("[Key:%s | Element:%s]-", head->bucket->key, head->bucket->element);
                head = head->next;
            }

            printf("!\n");
        }
    }
}

/**
 * @brief Insert an element with a key inside the hash table
 * 
 * @param table is the hash table 
 * @param key is the key to be used for hashing 
 * @param element is the element to store
 * @param hash_func is the hashing function to be used
 * @param collisions is the variable that stores the frequency of collisions
 */
void ht_insert(HashTable* table, char* key, char* element, int hash_func, int* collisions)
{
    // Create the bucket
    Bucket* bucket = create_bucket(key, element);

    // Compute the index using the hashing function
    unsigned int index = hashing_function (key, table->size, hash_func);

    //Check the very head (start) of the linked lists AT THAT index
    LinkedList* head = table->bucket_lists[index];


    if (head == NULL) { //If the head of the linked lists is empty, test first is there is still space
        if (table->count == table->size) {
            // Hash Table Full
            printf("ERROR! Hash Table is full!\n");
            // Remove linked list
            free_linkedlist(head);
        } 
        else 
        {
            //If hash table space is available, allocate memory for the start.
            // We need to create the list
            head = allocate_list();

            //Add the data for the element
            head->bucket = bucket;        

            //Assign back the head at the start    
            table->bucket_lists[index] = head;

            //Initialize the pointer for the next linked list at the chain
            head->next = NULL;
            

            //Increase the count of elements in the hash table
            table->count++;
        }
    }
    else {
        //increments variable storing number of collisions
        *collisions += 1;
        // Insert to the list IF there is already an element inside the head (Chaining resolution)
        table->bucket_lists[index] = linkedlist_insert(head, bucket);
    }
}

/**
 * @brief Get the index of the bucket_list that is at the very top of the hash table (Closest to index 0)
 * 
 * @param table is the hash table
 * @return int is the index of the closest used bucket_list
 */
int ht_bucket_list_head(HashTable * table)
{
    int i;
    for(i = 0; i < table->size; i++)
    {
        LinkedList * curr_list = *(table->bucket_lists + i);
        //Check if not null, then return if so
        if(curr_list != NULL){
            return i;
        }
    }

    return -1;
}

/**
 * @brief Remove a bucket in the head of the hash table and return the bucket
 * 
 * @param table is the hash table
 * @return Bucket* is the removed bucket
 */
Bucket * ht_remove (HashTable* table)
{
    // Get the linked list with the key
    int index = ht_bucket_list_head(table);

    if(index != -1)
    {

        LinkedList * head = *(table->bucket_lists + index);
        Bucket * bucket = create_bucket(head->bucket->key, head->bucket->element);
        
        // Removes the head from the linked list
        // and returns the bucket of the popped element
        LinkedList * temp = head;
        (*table).bucket_lists[index] = (*table).bucket_lists[index]->next;
        temp->next = NULL;
        //Bucket is now separated from the hash table
        
        //Free space for the head of the hash table
        if(head != NULL)
        {
            free(temp->bucket->key);
            free(temp->bucket->element);
            free(temp->bucket);
            free(temp);
        }
        
        //Give back the bucket
        return bucket;
    }
    else
        return NULL;
}

/**
 * @brief The hashing function used for the hash table 
 * 
 * @param key is the key used for generating the hash
 * @param table_size is the size of the table
 * @param hash_function is the hash function to be used
 * @return unsigned int is the generated index of the bucket
 */
unsigned int hashing_function (char* key, int table_size, int hash_function)
{
    // Compute the index
    uint32_t seed = 0; //can change
    
    switch (hash_function)
    {
        case 1: return crc32(key, strlen(key)) % table_size;
        case 2: return murmurhash3_32(key, (uint32_t) strlen(key), seed) % table_size;
    }

    return -1;
}