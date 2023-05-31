/*  inputTrip accepts user input and changes the value located on the address tripNum is pointing. The function will repeat until the trip number entered is valid.
    @param tripNum - string variable where user will input a value.
    @param *index - integer pointer that stores the index where the trip number is located after the function runs
    @return void - no return variable
    Pre-condition: none
*/
void
inputTrip ( char* tripNum,
            int *index)
{
    //initializing and defining for-loop variables
    int size = MANILA_SIZE + LAGUNA_SIZE;
    int i;
    int valid = 0;
    string5 tripNumList[LAGUNA_SIZE + MANILA_SIZE] = {"AE101", "AE102", "AE103", "AE104", "AE105", "AE106", "AE107", "AE108", "AE109", 
                                                    "AE150", "AE151", "AE152", "AE153", "AE154", "AE155", "AE156", "AE157", "AE158", "AE159", "AE160"};

    //if tripNum is empty, it means its meant to be user input rather than being loaded from a file
    if (tripNum[0] == '\0')
    {
    	printf("\nTrip Numbers: AE101 to AE109 (Manila to Laguna), AE150 to AE160 (Laguna to Manila)");
        printf("\nEnter your Trip number (case-sensitive): ");
        scanf(" %s", tripNum);
    }

    //loops through the tripNumList
    for (i = 0; i < size; i++)
    {
        //it compares it through the whole array, if it matches with one of the values, it is considered valid and the index containing the value is assigned to *index variable.
        if (strcmp(tripNum, tripNumList[i]) == 0)
        {
            *index = i;
            valid = 1;

            //so the loop stops
            i = size;
        }
    }

    //if the input does not match with anything on the array, the function runs again.
    if (valid == 0)
    {
        printf("[INPUT ERROR] Invalid Trip Number, please try again.\n");

        //"empties" the string
        tripNum[0] = '\0';
        inputTrip(tripNum, index);
    }
}

/*  inputIDNum accepts a string input and then checks if the string input matches the conditions of a basic Lasallian ID Number format, specifically 8 characters and all integers. 
    If it passes these conditions, function stops looping and the value of IDNum stays.
    @param IDNum - an IDString variable that will store the user input
    @return void - no return variables
    Pre-condition: none
*/
void
inputIDNum (IDString IDNum)
{
    char *ptr;

    //inputs the ID Number as string to avoid errors and to efficiently count ID Number length
    if (IDNum[0] == '\0')
    {
        printf("Enter your ID Number: ");
        scanf(" %s", IDNum);
    }

    //default Lasallian ID contains 8 digits, checks if it applies to the input, if not, ask for another input.
    if (strlen(IDNum) > 8 || strlen(IDNum) < 8)
    {
        printf ("[INPUT ERROR] Invalid ID Number Size, please try again\n");
        IDNum[0] = '\0';
        inputIDNum(IDNum);
    }

    //the pointer keeps on going as long as it detects an integer of BASE 10. Stops the pointer where it stops detecting an integer.
    strtol(IDNum, &ptr, 10);
    
    //if the pointer does not stop at NULL, it means something in the string can not be considered an integer, therefore it is an invalid input.
    if (*ptr != '\0')
    {
        printf ("[INPUT ERROR] ID Number contains invalid data type, please try again\n");
        IDNum[0] = '\0';
        inputIDNum(IDNum);
    }

}

/*  inputName asks the user for 2 inputs: their first name and last name. If any of the strings exceed 50 characters OR contains non-letter characters, print an error message and ask the user for another input.
    Also corrects the capitalization of the names.
    @param fullname - a string variable that will store the user's full name by the end of the function
    @return void - no return parameters
    Pre-condition: none
*/
void
inputName (string100 fullname)
{
    //initializing for loop counter
    int i ;
	int fullname_len = strlen(fullname);
    //asks for first name and last name inputs (includes spaces)
    if (fullname[0] == '\0')
    {
        printf("Enter your full name: ");
        scanf(" %[^\n]s", fullname);
    }
	
    //checks if the inputs exceed character limit
    if (fullname_len > 100)
    {
        printf("[INPUT ERROR] Name cannot exceed 100 characters\n");
        fullname[0] = '\0';
    }

    //loop to check each individual characters if there is a non-character present
    for (i = 0; fullname[i] != '\0'; i++)
    {
        if (fullname[i] != ' ' && isalpha(fullname[i]) == 0)
        {
            printf("[INPUT ERROR] Name can only contain letters (A-Z, a-z)\n");
            fullname[0] = '\0';
            fullname[i + 1] = '\0'; //stops the loop
        }
    }
    
    //if this condition is true again, it means it failed one of the validity checks
    if (fullname[0] == '\0')
    {
		inputName(fullname);
    }
    //loops to implement proper capitalization
    for (i = 0; fullname[i] != '\0'; i++)
    {
        //if current position of the index in the string is the first character or is a space
        if (i == 0 || fullname[i] == ' ')
        {
            //checks if the next character is uncapitalized and it is not the first character
            if (i > 0 && fullname[i + 1] >= 'a' && fullname[i + 1] <= 'z')
            {
                fullname[i + 1] -= 32; //sets the small letter to become capital
            } else if (i == 0 && fullname[i] >= 'a' && fullname[i] <= 'z') //if the character is the first one in the string and it is uncapitalized
            {
                fullname[i] -= 32;
            }
        }

        //if the current position of the index in the string is not the first character or is not after a space.
        if (fullname[i - 1] != ' ' && i > 0)
        {
            //if the character is a capital letter, convert it to its small letter equivalent
            if (fullname[i] >= 'A' && fullname[i] <= 'Z')
            {
                fullname[i] += 32;
            }
        }
    }
}

/*  inputPrio accepts an integer input corresponding to the Priority Numbers provided. Only accepts inputs from integers 1 to 6, asks for another input if the user enters an invalid input.
    @param input - current input, mainly for loading fron files, set to 0 if user has to enter
    @return input - returns an integer ranging from 1-6.
    Pre-condition: none
*/
int
inputPrio(int input)
{
    //user input variable declaration
    if (input < 1 || input > 6)
    {
        printf("\nPriority Groups:\n");
        printf("[1] Faculty and ASF with Inter-campus assignments\n");
        printf("[2] Students with inter-campus enrolled subjects or enrolled in thesis using inter-campus facilities\n");
        printf("[3] Researchers\n");
        printf("[4] School Administrators (Academic Coordinators level and up for Faculty and ASF, and Director level and up for APSP)\n");
        printf("[5] University Fellows\n");
        printf("[6] Employees and Students with official business\n");
    }

    //loops while the input is not in range 
    while (input < 1 || input > 6)
    {
        input = 0;
        printf("Enter your priority number: ");
        scanf(" %d", &input);

        //discards unwanted characters until the user presses enter
        while ( getchar() != '\n' );

        //error messsage
        if(input < 1 || input > 6)
        {
            printf("[INPUT ERROR] Invalid Input. Allowed inputs are integers 1-6.\n");
        }
    }

    return input;
}

/*  getEmbarkationPoint returns 1 if the trip is going from Manila to Laguna and returns 2 if the trip is going from Laguna to Manila
    @param tripIndex - an integer containing the position of the trip number in the array of trip numbers (tripNumList)
    @return int - returns 1 if the Embarkation Point is from Manila to Laguna (tripIndex = 0 to 8) or 2 if the Embarkation Point is from Laguna to Manila (tripIndex = 9 to 19)
    Pre-condition: tripIndex only contains an integer ranging from 0 to 19
*/
int
getEmbarkationPoint (int tripIndex)
{
    //The value of the index corresponds to the position of the user-inputted Trip Number in the list that is passed to the function inputTrip, it will always have a value that ranges from 0 - 19
    //where positions 0 - 8 contains trip numbers going from Manila to Laguna (1) and 9 - 19 contains trip numbers going from Laguna to Manila (2)
    if (tripIndex <= 8)
        return 1;
    else
        return 2;
}

/*  inputDropPoint asks for an integer input that would represent the Drop-off points of the shuttle routes. 
    The routes differ depending on the embarkation point that the user will take, where Manila to Laguna only has 3 drop-off points while Laguna to Manila has 4 drop off points to choose from.
    @param embarkPoint - an integer containing a value of either 1 or 2, where 1 = Manila to Laguna and 2 = Laguna to Manila.
    @param input - current input, mainly for loading fron files, set to 0 if user has to enter
    @return int - returns the user input if the input is valid (1-3 if embarkPoint = 1; 1-4 if embarkPoint = 2)
    Pre-condition: embarkPoint can only contain a value of 1 or 2
*/
int
inputDropPoint(int embarkPoint, int input)
{
    //variable for the upper limit of the accepted inputs
    int limit;

    //embarkPoint values: 1 = Manila to Laguna route, 2 = Laguna to Manila route
    if (embarkPoint == 1)
    {
        //Manila to Laguna drop-off points
        limit = 3;
        if (input < 1 || input > limit)
        {
            printf("\nDrop-Off Points (Manila to Laguna):\n");
            printf("[1] Mamplasan Toll Exit\n");
            printf("[2] Phase 5, San Jose Village\n");
            printf("[3] Milagros Del Rosario (MRR) Building - East Canopy\n");
        }
    }
    else
    {
        //Laguna to Manila drop-off points
        limit = 4;
        if (input < 1 || input > limit)
        {
            printf("\nDrop-Off Points (Laguna to Manila):\n");
            printf("[1] Petron Gasoline Station along Gil Puyat Avenue\n");
            printf("[2] Gate 4: Gokongwei Gate\n");
            printf("[3] Gate 2: North Gate (HSSH)\n");
            printf("[4] Gate 1: South Gate (LS Building Entrance)\n");
        }
    }

    //continues to ask user for an input until it gets an accepted integer
    while (input < 1 || input > limit)
    {
        input = 0;
        printf("Enter your drop point: ");
        scanf("%d", &input);
        //discards unwanted characters until the user presses enter
        while ( getchar() != '\n' );

        //if input is not in the range of 1-6
        if (input < 1 || input > limit)
        {
            printf("[INPUT ERROR] Invalid Input. Allowed inputs are integers 1-%d.\n", limit);
        }
    }
    return input;
}

/*  inputDate asks the user for a Date input (day, month, year)
    @param void - no parameters
    @return Date - a Date struct containing the day, month, and year that is inputted by the user
    Pre-condition: none
*/
Date
inputDate ()
{
    Date date;

    //initial assignments
    date.nDay = 0;
    date.nMonth = 0;
    date.nYear = 0;

    //keep asking user for input until they enter a valid input (1 - 31)
    while (date.nDay < 1 || date.nDay > 31)
    {
        printf("\nEnter Day: ");
        scanf("%d", &date.nDay);
        while ( getchar() != '\n' );

        if (date.nDay < 1 || date.nDay > 31)
            printf("\n[INPUT ERROR] Invalid Input. Allowed inputs are integers 1 to 31.");
    }

    //keep asking user for input until they enter a valid input (1 - 12)
    while (date.nMonth < 1 || date.nMonth > 12)
    {
        printf("\nEnter Month (in integer): ");
        scanf("%d", &date.nMonth);
        while ( getchar() != '\n' );

        if (date.nMonth < 1 || date.nMonth > 12)
            printf("\n[INPUT ERROR] Invalid Input. Allowed inputs are integers 1 to 12.");
    }

    //keep asking user for input until they enter a valid input (2020 - 2023)
    //limited to from 2020 because getting past trips from 2020 doesn't make much sense anyways
    while (date.nYear < 2020 || date.nYear > 2023)
    {
        printf("\nEnter Year (2020 - 2023): ");
        scanf("%d", &date.nYear);
        while ( getchar() != '\n' );

        if (date.nYear < 2020 || date.nYear > 2023)
            printf("\n[INPUT ERROR] Invalid Input. Allowed inputs are integers 2021 to 2023.");
    }

    //return the user inputs
    return date;
}
