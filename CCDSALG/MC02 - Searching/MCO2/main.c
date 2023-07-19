/*
* Programmed By: CCDSALG S11 Group 4
*
* Description:
* 	main.c: This file is the main c file for MCO2 - Searching. 
*   It generates a random DNA sequence, and then proceeds to compute its kMer distribution.
*   The kMer distribution can be searched and stored using: Binary Search Trees (BSTs) or Hashing Functions (crc32 & murmurhash) and HashTables*
* 
* Last Modified: 09/12/2022
* Acknowledgements: 
*       Measuring time in between functions - https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
*/

#include "funcs.c"

int main()
{
    srand(time(0));

    int i;
    int n;
    int k;
    int alg;
    int hash_func;
    int collisions = 0;
    
    String bigString;
    struct StringDist kMers[kSIZE]; //Will contain the UNIQUE Kmers generated
    
	
    //initialize variables
    for(i = 0; i < kSIZE; i ++){
        strcpy(kMers[i].data, "");
        kMers->count = 0;
    }

    //input DNA sequence length n
    while(1){
        printf("Enter n (7 - 1,000,000): ");
        scanf("%d", &n);

        if(n >= 7 && n <= 1000000){
            break;
        }else
            printf("Invalid selection! Please try again.\n");
    }
    
    //input k 
    while(1){
        printf("Enter k (5 - 7): ");
        scanf("%d", &k);

        if(k >= 5 && k <= 7){
            break;
        }else
            printf("Invalid selection! Please try again.\n");
    }


    printf("n = %d:\n", n);
    printf("k = %d:\n", k);

    //Choose the algorithm
    while(1){
        printf("Please choose an algorithm:\n");
        printf("1: Hash Table\n2: Binary Search Tree\n");
        printf("Enter selection: ");
        scanf("%d", &alg);
        if(alg == 1 || alg == 2){
            break;
        }else
            printf("Invalid selection! Please try again.\n");
    }

    /*Used to measure time between functions
    Measuring time between functions from:
    https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
    */
    clock_t start = -1;
    clock_t end = -1;

    //generate random DNA sequence S with length n
    initializeString(bigString, n);
    //strcpy(bigString, "taccaccaccatag"); //MCO2 example test

    //generates kMers and stores in a String array
    generatekMers(kMers, bigString, n, k); 

    switch (alg){
        case 1:
            //Choose hashing function first
            while(1)
            {
                printf ("Choose hashing function (1: crc32, 2: murmurhash3): ");
                scanf("%d", &hash_func);
                if(hash_func == 1 || hash_func == 2){
                    break;
                }else
                    printf("Invalid selection! Please try again.\n");
            }
            
            //Perform the Hash Table Stuff
            start = clock();
            HashTable* table = create_table (n);
		    insertkMersHT(table, kMers, bigString, n, k, hash_func, &collisions);
		    createHTDistribution(kMers, table, n, k, hash_func);
            end = clock();
            
            free_table(table);
            printf("Number of collisions: %d\n", collisions);
        break;
        case 2:

            //Perform the BST stuff
            start = clock();
            struct TreeNode BST;
            createBST(BST);

            insertkMersBST(&BST, bigString, n, k);
            
            //create distribution
            createBSTDistribution(kMers, &BST);
            end = clock();
            
            //frees memory for next lines of code
            destroy(&BST);
        break;
    }

    //Save results to text files
    createkMerFile(kMers, k, alg, hash_func);
    createBigStringFile(bigString);


    //Print out the running time
    printf("\n\nRunning time of the algorithm for n = %d: %.20lf seconds", n, ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}