#include <stdio.h>
#include <string.h>

typedef struct Bucket
{
    char * key;
    char * element;
}Bucket;

typedef struct LinkedList
{
    Bucket * bucket;
    struct LinkedList * next;
} LinkedList;

typedef struct HashTable
{
    LinkedList** bucket_lists;
    int size;
    int count;
} HashTable;

LinkedList *    allocate_list       ();
LinkedList *    linkedlist_insert   (LinkedList* head, 
                                     Bucket* bucket);
void            free_linkedlist     (LinkedList* list);
void            linkedlist_remove   (LinkedList* list);