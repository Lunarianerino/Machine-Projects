/*  getDate returns a Date struct type that contains the date when the function is called. It also writes the date in "Date.txt" in the format "dd-mm-yyyy"
    @param void - there are no parameters
    @return date - date.nDay = integer of the day today, date.nMonth = integer of the current month, and date.nYear = integer of the current year
    Pre-condition: there are no pre-conditions
*/
Date
getDate() 
{
    Date date;

    //Getting Month, Day, and Year Variables
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    date.nDay = tm.tm_mday;
    date.nMonth = tm.tm_mon + 1; //default value is -1 from the current month
    date.nYear = tm.tm_year + 1900; //default value of the year starts counting after 1900; 2022 = 122
    return date;
}


/*  saveFile saves all the contents of the trips array in a txt file named after the contents of the date variables.
    @param trips - a Trips structure array that contains all the trips and the embarkation cards
    @param date - a Date struct containing the date of the trips which will be used when specifying the file name.
    @return void - no return parameters
    Pre-condition: the contents of trips are all assumed to be valid.
*/
void
saveFile (Trip trips[], Date date)
{
    EmbarkCard passenger;
    string100 dropPoint;
    string100 embarkPoint;

    char dateNum[5];
    char holder[6] = "-";
    char filename[50] = "Trip";
    
    FILE *tripFile;

    int i, j;
    int notEmpty = 0; //1 if all arrays are empty, 0 otherwise

    //adds the day to the file name
    //converts base10 integer to string
    itoa(date.nDay, dateNum, 10);
    //if date is a single digit, add a 0 at the start
    if (strlen(dateNum) == 1)
    {
        dateNum[1] = dateNum[0];
        dateNum[0] = '0';
    }

    //concatenates the string version of the date with a "-" into the filename
    strcat(holder, dateNum);
    strcat(filename, holder);

    //resets the value of holder
    strcpy(holder, "-");
    
    //adds the month to the file name
    itoa(date.nMonth, dateNum, 10);
    if (strlen(dateNum) == 1)
    {
        dateNum[1] = dateNum[0];
        dateNum[0] = '0';
    }
    strcat(holder, dateNum);
    strcat(filename, holder);

    strcpy(holder, "-");

    //adds the year to the file name
    itoa(date.nYear, dateNum, 10);
    strcat(holder, dateNum);
    strcat(filename, holder);

    //final result: filename.txt
    strcat(filename,".txt");
    

    //checks if all the trips are empty, if it is, dont save file
    for (i = 0; i < MANILA_SIZE + LAGUNA_SIZE; i++)
    {
        //its empty if the return of countEmpty is the same as the TRIP_SIZE
        if (countEmpty(trips[i]) < TRIP_SIZE)
        {
            notEmpty = 1;
            i = MANILA_SIZE + LAGUNA_SIZE;
        }
    }
    //opens the file if the array is not empty, does not create new file otherwise
    if (notEmpty == 1)
        tripFile = fopen(filename, "w");
    else
    {
        printf("\n[WARNING] There are currently no inputs, so no new file was created");
        printf("\n[NOTIFICATION} Terminating Program now...");
        return;
    }

    //loops for the different trips
    for (i = 0; i < MANILA_SIZE + LAGUNA_SIZE; i++)
    {
        //loops for the different embarkation cards inside each trip
        for (j = 0; j < TRIP_SIZE; j++)
        {
            //assigning the current embarkation card to a variable for easier access
            passenger = trips[i][j];
            //if the embarkation card for a seat has been filled, continue, else check the next card.
            if (passenger.filled == 1)
            {
                //assigns the appropriate string representations for the embarkation point and drop points to the embarkPoint and dropPpint strings respectively
                if (passenger.embarkPoint == 1)
                {
                    strcpy(embarkPoint, "1 - Manila to Laguna");
                    switch(passenger.nDrop)
                    {
                        case 1:
                            strcpy(dropPoint, "1 - Mamplasan Toll Exit");
                            break;
                        case 2:
                            strcpy(dropPoint, "2 - Phase 5, San Jose Village");
                            break;
                        case 3:
                            strcpy(dropPoint, "3 - Milagros Del Rosario Building");
                    }
                } else if (passenger.embarkPoint == 2)
                {
                    strcpy(embarkPoint, "2 - Laguna to Manila");
                    switch(passenger.nDrop)
                    {
                        case 1:
                            strcpy(dropPoint, "1 - Petron Gasoline Station along Gil Puyat Avenue");
                            break;
                        case 2:
                            strcpy(dropPoint, "2 - Gate 4: Gokongwei Gatee");
                            break;
                        case 3:
                            strcpy(dropPoint, "3 - Gate 2: North Gate (HSSH)");
                            break;
                        case 4:
                            strcpy(dropPoint, "4 - Gate 1: South Gate (LS Building Entrance)");
                    }
                }

                //inputs the embarkation card into a text file with the specified format
                fprintf(tripFile, "%s\n%s\n%s\n%s\n%d\n%s\n\n", passenger.tripNum, 
                                                                embarkPoint,
                                                                passenger.fullname,
                                                                passenger.idNum,
                                                                passenger.nPrio,
                                                                dropPoint);
            }
        }
    }

    fclose(tripFile);
    printf("\n[SUCCESS] All inputs have been encoded in **%s**", filename);
    printf("\n[NOTIFICATION} Terminating Program now...");

}

/*  loadCard scans a file (filename determined by user input) and assigns the contents into an embarkation card according to the trip number
    @param trips - a Trips structure array where the embarkation card from the text file will be placed.
    @return void - no return variable
    Pre-condition: 
        The text file follows the specified output format: 
            <trip number><new line> 
            <embarkation point><new line>  
            <passenger name><new line>  
            <id number><new line>  
            <priority number><new line> 
            <drop-off point><new line> 
*/
void 
loadCard (Trip trips[])
{
    FILE *card;
    EmbarkCard passenger;
    Date date = getDate();

    string100 embarkPoint;
    string100 dropPoint;

    //FILENAME_MAX is defined in stdio.h. Max characters in a file name in Windows is 255, FILENAME_MAX = 260
    char filename[FILENAME_MAX];
    
    string5 tripList[LAGUNA_SIZE + MANILA_SIZE] = {"AE101", "AE102", "AE103", "AE104", "AE105", "AE106", "AE107", "AE108", "AE109", 
                                                    "AE150", "AE151", "AE152", "AE153", "AE154", "AE155", "AE156", "AE157", "AE158", "AE159", "AE160"};

    int tripIndex;
    int ePoint;

    //for inputting the filename
    printf("Enter the file name of the card (exclude \".txt\"): ");
    scanf(" %[^\n]s", filename);

    //adds .txt to the end of the filename
    strcat(filename, ".txt");
    
    //tries to open the file
    card = fopen(filename, "r");

    //if file does not exist
    if (card == NULL)
    {
        printf("[INPUT ERROR] %s does not exist, please try again.\n", filename);
        return;
    }
    
    //if file exists
    printf("\n[NOTIFICATION] Loading %s...", filename);

    //initial assignment
    passenger.filled = 0;
    passenger.date = date;

    //scans the first line which contains the trip number
    fscanf(card, " %[^\n]s\n", passenger.tripNum);
    inputTrip(passenger.tripNum, &tripIndex); //checks if the trip number is valid, asks for input if invalid

    //scans the second line for the embarkation point
    fscanf(card, " %[^\n]s\n", embarkPoint);
    passenger.embarkPoint = embarkPoint[0] - '0'; //converts first character ("<num> - <Embarkation Point>") to integer
    ePoint = getEmbarkationPoint(tripIndex); //checks if the embarkation point is valid, if embarkation point is not valid, automatically assign correct one based on the trip number

    //notifies user about the embarkation point change
    if (ePoint != passenger.embarkPoint)
    {
        printf("\n[WARNING] Embarkation Point changed from %d to %d. (This is due to your embarkation point not matching your Trip Number", passenger.embarkPoint, ePoint);
        passenger.embarkPoint = ePoint;
    }

    //scans third line for the full name of the passenger
    fscanf(card, " %[^\n]s", passenger.fullname);
    inputName(passenger.fullname); //checks if the name is valid, asks for input if invalid

    //scans fourth line for the ID number
    fscanf(card, " %[^\n]s", passenger.idNum);
    inputIDNum(passenger.idNum); //checks if ID number is valid, asks for input if invalid
    
    //scans fifth line for the priority number
    fscanf(card, "%d",  &passenger.nPrio);
    inputPrio(passenger.nPrio); //check if valid, ask for input if invalid.

    fscanf(card, "%s\n", dropPoint); //scans last line for the drop point
    passenger.nDrop = dropPoint[0] - '0'; //converts first character ("<num> - <Drop-off Point>") to integer
    passenger.nDrop = inputDropPoint(passenger.embarkPoint, passenger.nDrop); //check if drop point is valid, ask for input if invalid

    //if all is valid, the card is considered filled
    passenger.filled = 1;

    //after all inputs are confirmed to be valid, print the embarkation card to show the user
    printEmbarkCard(passenger);
    assignTrip(passenger, trips, tripList, tripIndex); //then assign the embarkation card to the specified trip
    fclose(card); //close the file
}

/*  loadTrip scans the file corresponding to a specific date for the embarkation cards submitted during that day
    @param trips - a Trip struct array where the values of taken from the file will be assigned
    @param date - contains the date today where the file name will be referenced from
    @return void - there are no return variables
    Pre-condition: The inputs are assumed to be following the format and correct since it is loading the past save file
*/
void
loadTrip (Trip trips[], Date date)
{
    FILE *tripFile;
    EmbarkCard passenger;
    EmbarkCard default_user;
    default_user.filled = 0;

    char dateNum[5];
    char holder[6] = "-";
    char filename[50] = "Trip";

    string100 embarkPoint;
    string100 dropPoint;

    string5 tripList[LAGUNA_SIZE + MANILA_SIZE] = {"AE101", "AE102", "AE103", "AE104", "AE105", "AE106", "AE107", "AE108", "AE109", 
                                                    "AE150", "AE151", "AE152", "AE153", "AE154", "AE155", "AE156", "AE157", "AE158", "AE159", "AE160"};

    int tripIndex;

    int i, j;

    //technically "empties" all the trip arrays (by considering them not filled)
    for (i = 0; i < LAGUNA_SIZE + MANILA_SIZE; i++)
    {
        for (j = 0; j < TRIP_SIZE; j++)
        {
            trips[i][j].filled = 0;
        }
    }

    //same way to get filename as the one in the savefile() function
    //day
    //converts base10 integer to string
    itoa(date.nDay, dateNum, 10);
    //if date is a single digit, add a 0 at the start
    if (strlen(dateNum) == 1)
    {
        dateNum[1] = dateNum[0];
        dateNum[0] = '0';
    }
    strcat(holder, dateNum);
    strcat(filename, holder);

    strcpy(holder, "-");
    
    //month
    itoa(date.nMonth, dateNum, 10);
    if (strlen(dateNum) == 1)
    {
        dateNum[1] = dateNum[0];
        dateNum[0] = '0';
    }
    strcat(holder, dateNum);
    strcat(filename, holder);

    strcpy(holder, "-");

    //year
    itoa(date.nYear, dateNum, 10);
    strcat(holder, dateNum);
    strcat(filename, holder);

    strcat(filename,".txt");
    
    tripFile = fopen(filename, "r");

    //if file does not exist, inform user and end the function
    if (tripFile == NULL)
    {
        printf("\n[INPUT ERROR] %s does not exist. If this is your first time running today, please ignore this message.\n", filename);
        return;
    }

    //loops until the end of file is detected
    while (!feof(tripFile))
    {
        passenger.filled = 0;
        //although the pre-condition states that all parts of the file is correct, loop checks for vallidity just in case
        
        //assigns date to the embarkation card
        passenger.date = date;

        //scans the line corresponding to the trip number
        fscanf(tripFile, " %[^\n]s\n", passenger.tripNum);
        inputTrip(passenger.tripNum, &tripIndex); //check if the trip number is valid, ask for new input otherwise

        //scans the line corresponding to the embarkation point
        fscanf(tripFile, " %[^\n]s\n", embarkPoint);
        passenger.embarkPoint = embarkPoint[0] - '0'; //converts first character ("<num> - <Embarkation Point>") to integer then assigns it to the embarkation card

        //scans the line corresponding to the full name
        fscanf(tripFile, " %[^\n]s\n", passenger.fullname);
        inputName(passenger.fullname); //checks if the full name is valid, also applies appropriate capitalization

        //scans the line corresponding to the id number
        fscanf(tripFile, " %[^\n]s\n", passenger.idNum);
        inputIDNum(passenger.idNum); //checks if the id number applies the correct parameters

        //scans the line corresponding to the priority number
        fscanf(tripFile, "%d\n",  &passenger.nPrio);
        inputPrio(passenger.nPrio);

        //scans the line corresponding to the drop point
        //\n is necessary so that the pointer goes to the new line. Helps with looping the code to scan the next person
        fscanf(tripFile, "%[^\n]s", dropPoint);
        passenger.nDrop = dropPoint[0] - '0'; //converts first character ("<num> - <Drop-off Point>") to integer then assigns it to the embarkation card variable
        inputDropPoint(passenger.embarkPoint, passenger.nDrop);

        //scans the next line, helps to solve the problem where the while loop runs one too many times
        fscanf(tripFile, "\n");
        passenger.filled = 1;

        //prints the embarkation card to show the user
        printEmbarkCard(passenger);

        //assigns the embarkation card from taken from the file to the trips array
        assignTrip(passenger, trips, tripList, tripIndex);
        
        //resets the embarkation card to an empty state
        passenger = default_user;
    }
}
