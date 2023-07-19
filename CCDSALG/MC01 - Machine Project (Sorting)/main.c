#include "sorting_algs.c"

int main()
{
    //Random Seed
    srand(time(0));

    //Array which stores the indices that correspond to the suffix at that position
    int SuffixIndices[MAX_SUFFIX_LENGTH];
    
    //Main given string
    StringBig mainString;

    //Get string length thru user input
    int n;
    while(1){
        printf("Please enter the length of the string (1 - 65536):");

        scanf(" %d", &n);
        if(n >= 1 && n <= MAX_SUFFIX_LENGTH)
        {
            initializeString(mainString, n+2);
            //strcpy(mainString, "tgtgtgtgcaccg"); example from MCO1 page to test if the sorting is correct
            break;
        }
        else
            printf("Invalid Number! Please try again!\n");
    }

    //Init the suffixes indices
    initializeSuffixIndicesArray(SuffixIndices, n);

    /*Used to measure time between functions
    Measuring time between functions from:
    https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
    */
    clock_t start = -1;
    clock_t end = -1;


    while(1){
        printf("Please choose a sorting algorithm (q for QuickSort, s for SelectionSort): ");

        char c;
        scanf(" %c", &c);

        //Selection Sort is selected
        if(c == 's')
        {
            printf("\n-=-Selection Sort-=-\n");
            start = clock();
            selection_sort(mainString, SuffixIndices, n);
            end = clock();
            printf("\n=-=-=-=-=SUCCESSFUL SELECTION SORT=-=-=-=-=\n");
            break;
        } 
        else if (c == 'q') // QuickSort is selected
        {
            printf("\n-=-Quick Sort-=-\n");
            start = clock();
            quick_sort(mainString, SuffixIndices, n, 0, n-1);
            end = clock();
            printf("\n=-=-=-=-=SUCCESSFUL QUICKSORT=-=-=-=-=\n");
            break;
        } else
            printf("Invalid Input! Please try again!\n"); 
    }

    //Print out the sorted suffixes
    printf("\n-=-=-=-=Sorted Suffixes:=-=-=-=-\n");
    printSuffixArray(mainString, SuffixIndices, n);

    //Print out the running time
    printf("\n\nRunning time of the sorting algorithm for n = %d: %.20lf seconds", n, ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}