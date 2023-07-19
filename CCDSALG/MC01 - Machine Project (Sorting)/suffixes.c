#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SUFFIX_LENGTH 65536

typedef char StringBig[MAX_SUFFIX_LENGTH + 1];

/**
 * @brief Swaps the values of 2 integer variables via pass by reference
 * 
 * @param index1 is the pointer to the first integer
 * @param index2 is the pointer to the second integer
 */
void swap_indices(int * index1, int * index2)
{
    int nTemp = *index1;

    *index1 = *index2;
    *index2 = nTemp;

}

/**
 * @brief Initializes the array which contains the indices of the suffixes of a given string
 * 
 * @param SuffixIndices is the array which has the indices
 * @param n is the string length
 */
void initializeSuffixIndicesArray(int SuffixIndices[], int n)
{
    int i;

    for(i = 0; i < n ; i++){
        SuffixIndices[i] = i;
    }
}

/**
 * @brief Prints the suffixes of a given string
 * 
 * @param mainString is the given string
 * @param SuffixIndices is the indices that correspond to the suffixes
 * @param n is the string length
 */
void printSuffixArray(StringBig mainString, int SuffixIndices[], int n)
{
    int i;
    for(i = 0; i < n; i++)
        if(strlen(mainString + SuffixIndices[i]) > 0)
            printf("%2d: %s\n", SuffixIndices[i], mainString + SuffixIndices[i]);

    printf("\nSUCCESSFUL PRINT!\n");
}

/**
 * @brief Initializes the input string to be used
 * 
 * @param inputString will store the generated string
 * @param n is the specified string length
 */
void initializeString(StringBig inputString, int n)
{
    int i;
    for(i = 0; i < n - 2; i++) //Go through the string's character array
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

    //Add the null character at the end to complete the string :D
    inputString[n-1] = '\0';
    printf("\nInput String: %s\n", inputString);
}
