#include "suffixes.c"

/**
 * @brief Partition function for quick sort of strings
 * 
 * @param mainString is the given string
 * @param SuffixIndices is the indices of the suffixes of the given string
 * @param n is the length of the string
 * @param left is the leftmost index of the subarray
 * @param right is the rightmost index of the subarray
 * @return int is the index of the partition created
 */
int Partition(StringBig mainString, int SuffixIndices[], int n, int left, int right)
{
    StringBig pivot_string;
    strcpy(pivot_string, mainString + SuffixIndices[right]); //get pivot string

    int i = left - 1;
    int j;

    //loop through subarray
    for(j = left; j < right; j++)
    {
        StringBig curr_string;
        strcpy(curr_string, mainString + SuffixIndices[j]);

        int str_diff = strcmp(curr_string, pivot_string); //compare strings

        if(str_diff <= 0) //current string has a lower lexicographic value compared to pivot
        {
            i++;
            swap_indices(SuffixIndices + i, SuffixIndices + j); //Only swap the indices
        }
    }
    swap_indices(SuffixIndices + i + 1, SuffixIndices + right);
    return i+1;
}

/**
 * @brief Sorts an array of indices corresponding to a suffix of a given string using a 
 * modified quicksort algorithm
 * 
 * @param mainString is the given string
 * @param SuffixIndices is the indices of the suffixes of the given string
 * @param n is the length of the string
 * @param left is the leftmost index of the subarray
 * @param right is the rightmost index of the subarray
 */
void quick_sort(StringBig mainString, int SuffixIndices[], int n, int left, int right)
{
    if(left < right)
    {
        int q = Partition(mainString, SuffixIndices, n, left, right); //Get partition

        //Sort rest of the array
        quick_sort(mainString, SuffixIndices, n, left, q - 1); 
        quick_sort(mainString, SuffixIndices, n, q + 1, right);
    }
}

/**
 * @brief Sorts an array of indices corresponding to a suffix of a given string using a 
 * modified selection sort algorithm
 * 
 * @param mainString is the given string
 * @param SuffixIndices is the indices of the suffixes of the given string
 * @param n is the length of the string
 */
void selection_sort(StringBig mainString, int SuffixIndices[], int n)
{
    int i, j;

    //Loop through all the elements (Except the end no need for that)
    for(i = 0; i < n - 1; i++)
    {
        int selected_index = i;
        StringBig selected_string;
        strcpy(selected_string, mainString + SuffixIndices[i]); //Get the current string


        //Check out all the other strings after the current string
        for(j = i; j < n; j++)
        {
            StringBig curr_string;
            strcpy(curr_string, mainString + SuffixIndices[j]);  

            //Compare the other strings with the selected string
            int str_diff = strcmp(curr_string, selected_string);

            if(str_diff <= 0) //current string has a lower lexicographic value compared to selected string
            {
                //Select THIS current string, since it has a lower value
                strcpy(selected_string, curr_string);
                selected_index = j;
            }
        }

        //Put the lowest found unsorted string at the very front
        swap_indices(SuffixIndices + i, SuffixIndices + selected_index);
    }
    
}