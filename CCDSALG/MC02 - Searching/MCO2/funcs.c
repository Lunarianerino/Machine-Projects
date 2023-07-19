/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	funcs.c: This file handles the general functions used for displaying and generating the kMers.
*
* Last Modified: 09/12/2022
*/


#include "funcs.h"

/**
 * @brief Generate the DNA sequence in an inputString
 * 
 * @param inputString is the inputString for the program
 * @param n in the length of the string
 */
void initializeString(String inputString, int n)
{
    int i;
    for(i = 0; i < n; i++) //Go through the string's character array
    {
        int n_rand = rand() % 4;
        //Generate a random character {a, c, g, t}
        char c = 'a';
        switch(n_rand)
        {
            case 1:
                c = 'c';
                break;
            case 2:
                c = 'g';
                break;
            case 3:
                c = 't';
                break;
        }
        inputString[i] = c;
    }
    inputString[i] = '\0'; //End with zero pointer
}


/**
 * @brief Generate the kMers that will be stored and then searched in the data structure to be used
 * 
 * @param kMers is the array storing all the unique kMers
 * @param bigString is the bigString from which the kMers came from
 * @param n is the length of the string
 * @param k is the length of each kMer
 */
void generatekMers(StringDist kMers[], String bigString, int n, int k){
    int i,j,x;
    int found;

    String7 temp;

    printf("Generating KMers!\n");
    for (i = 0; i < n - k + 1; i ++)
    {
        strcpy(temp, ""); //reset temp 
        found = 0;

        //Create the kMer string
        for (j = i; j < k+i; j++)
            temp[j-i]= bigString[j]; //copy the current k-Mer to temp
        temp[k] = '\0';

        //checks if the current k-Mer is already found in the list of k-Mers
        for(x = 0; x < kSIZE; x++)
        { 
                if(strcmp(kMers[x].data, temp) == 0)
                {
                    found = 1;
                    break;
                }
        }

        //if k-Mer is not found, find the first empty slot in kMers array and store the unique k-Mer
        if (found == 0)
        {
            for(x = 0; x < kSIZE; x++)
            {
                if(strcmp(kMers[x].data, "") == 0)
                {
                        strcpy(kMers[x].data, temp);
                        break;
                }
            }
        }
    }    
}

/**
 * @brief Insert the kMers into a Binary Search Tree for searching later on
 * 
 * @param BST is the binary search tree
 * @param bigString is the bigString from which the kMers came from
 * @param n is the length of the string
 * @param k is the length of each kMer
 */
void insertkMersBST(Node* BST, String bigString, int n, int k){

    int i,j;
    String7 temp; //reset temp 
    for (i = 0; i < n - k + 1; i ++)
    {
        strcpy(temp, "");
        for (j = i; j < k+i; j++)
            temp[j-i]= bigString[j]; //copy the current k-Mer to temp
        temp[k] = '\0';

        //adds temp into the BST as a node
        BST = insert(BST, temp);
    }
}

/**
 * @brief Search the Binary Search Tree to determine the kMer distribution
 * 
 * @param kMers is the array storing all the unique kMers
 * @param BST is the binary search tree
 */
void createBSTDistribution(StringDist kMers[], Node* BST){
    int i; 
    
    //Go through the kMers array
    for(i = 0; i < kSIZE; i ++)
    {
        if(strcmp(kMers[i].data, "") == 0) return; //stops function from accessing empty structs        

        //Search the Binary Search tree
        while(search(BST, kMers[i].data) != NULL)
        {
            BST = delete(BST, kMers[i].data);
            kMers[i].count ++;
        }
        
    }
}

/**
 * @brief Insert the kMers into a Hash Table for searching later on
 * 
 * @param table is the hash table to use
 * @param kMers is the array storing all the unique kMers
 * @param bigString is the bigString from which the kMers came from
 * @param n is the length of the string
 * @param k is the length of each kMer
 * @param hash_func is the hashing function to be used
 * @param collisions is the variable that stores the frequency of collisions
 */
void insertkMersHT (HashTable* table, StringDist kMers[], String bigString, int n, int k, int hash_func, int* collisions)
{
    int i,j;
    String7 temp; //reset temp 
    char key[8];

    printf("Bigstring: %s\n\n", bigString);
    for (i = 0; i < n - k + 1; i ++)
    {
        strcpy(temp, "");
        
        for (j = i; j < k+i; j++)
            temp[j-i]= bigString[j]; //copy the current k-Mer to temp
        temp[k] = '\0';

        //adds temp into the BST as a node
        sprintf(key, "%d", i);
        
        ht_insert(table, key, temp, hash_func, collisions);
    }

    printf("Generated HashTable:\n");
    ht_print(table);
}

/**
 * @brief Search the Hash Table to determine the kMer distribution
 * 
 * @param kMers is the array storing all the unique kMers 
 * @param table is the hash table
 * @param n is the length of the string
 * @param k is the length of each kMer
 * @param hash_func is the hashing function to be used
 */
void createHTDistribution (StringDist kMers[], HashTable *table, int n, int k, int hash_func)
{
    printf("\nCreating HashTable Distribution!\n");

    //Loop UNTIL bucket is empty.

    Bucket * removed_bucket = ht_remove(table);

    //Loop through all of the buckets inside the hash table until it runs out
    while(removed_bucket != NULL)
    {
        //Check if the removed bucket has duplicates in the kMers
        
        int i;
        for (i = 0; i < n - k + 1; i++)
        {
            //If that bucket's element is found in the kMers array, increment the number of times it was seen
            if (strcmp(removed_bucket->element, kMers[i].data) == 0)
            {
                kMers[i].count++;
                break;
            }
               
        }
        removed_bucket = ht_remove(table);
    }
}

/**
 * @brief Generates a test file detailing the kMer distribution generated from the chosen data structure
 * 
 * 
 * @param kMers is the array storing all the unique kMers 
 * @param k is the length of each kMer
 * @param alg is the algorithm chosen for the kMer distribution
 * @param hash_function is the hashing function to be used (If hash tables were used)
 */
void createkMerFile(StringDist kMers[], int k, int alg, int hash_function){
    int counter = 0;
    FILE *fp = NULL;
    int i;
    

    //Make the file
    if(alg == 1)
    {
        if (hash_function == 1) 
            fp = fopen("kMers_HT_CRC32.txt", "w");
        else
            fp = fopen("kMers_HT_MURMUR.txt", "w");
    }  
    else
        fp = fopen("kMers_BST.txt", "w");
    
    fprintf(fp, "%d-mer | # of occurences\n", k);
    

    //Show each kmer with its count
    for(i = 0; i < kSIZE; i ++)
    {
        if(kMers[i].data[0] != '\0')
        {
            fprintf(fp, "%s | %d\n", kMers[i].data, kMers[i].count);
            counter ++;
        }
    }

    //YAY!
    if(alg == 1)
    {
        if (hash_function == 1) 
            printf("BST k-Mer distribution file: kMers_HT_CRC32.txt; count: %d\n", counter);
        else
            printf("BST k-Mer distribution file: kMers_HT_MURMUR.txt; count: %d\n", counter);
    }  
    else
        printf("BST k-Mer distribution file: kMers_BST.txt; count: %d\n", counter);
        
    fclose(fp);
}


/**
 * @brief Create a test file showing the DNA sequence used for kMer distribution
 * 
 * @param bigString is the string with the DNA sequence
 */
void createBigStringFile(String bigString){
    FILE *fp = NULL;
    int i;
    fp = fopen("bigString.txt", "w");
    
    for(i=0;i<MAX + 1;i++)
    {
        if(bigString[i] == '\0')
        {
            fclose(fp);
            printf("BigString file: bigString.txt\n");
            return;
        }
        fprintf(fp, "%c", bigString[i]);
    }
    fclose(fp);
}