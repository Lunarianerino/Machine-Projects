/*  printEmbarkCard prints the embarkation card based from previous user inputs into a specific format on the screen
    @param user - a struct variable named EmbarkCard containing necessary details found inside an embarkation card.
    @return void - no return variables
    Pre-condition: the contents of user is valid and filled
*/
void
printEmbarkCard (EmbarkCard user)
{
    printf("\n================Embarkation Card================\n");
    printf("Trip Number: %s\n", user.tripNum); //prints trip number
    printf("Embarkation Point: ");
    
    //print embarkation point depending on the value of the integer
    //Embarkation points represented by the values
    switch (user.embarkPoint)
    {
        case 1:
            printf("Manila to Laguna\n");
            break;
        case 2:
            printf("Laguna to Manila\n");
    }

    //prints the full name
    printf("Passenger Name: %s\n", user.fullname);
    printf("ID Number: %s\n", user.idNum); //prints the ID number
    printf("Priority Number: %d\n", user.nPrio); //prints the priority number of the user
    printf("Date of Trip (dd/mm/yyyy): %.2d/%.2d/%d\n", user.date.nDay, user.date.nMonth, user.date.nYear); //prints the date of the trip
    printf("Drop-off point: ");

    //Prints drop-off points based on the embarkation point and the drop-off point the user specified.
    if (user.embarkPoint == 1)
    {
        switch(user.nDrop)
        {
            case 1:
                printf("Mamplasan Toll Exit\n");
                break;
            case 2:
                printf("Phase 5, San Jose Village\n");
                break;
            case 3:
                printf("Milagros Del Rosario (MRR) Building - East Canopy\n");
        }
    } else
    {
        switch(user.nDrop)
        {
            case 1:
                printf("Petron Gasoline Station along Gil Puyat Avenue\n");
                break;
            case 2:
                printf("Gate 4: Gokongwei Gatee\n");
                break;
            case 3:
                printf("Gate 2: North Gate (HSSH)\n");
                break;
            case 4:
                printf("Gate 1: South Gate (LS Building Entrance)\n");
        }
    }
    printf("================================================\n");
}

/*  printTrip prints all the embarkation cards of all the trips
    @param trip - the trip that contains the embarkation cards to be printed
    @return void - no return variable
    Pre-condition: none
*/
void
printTrip (Trip trip)
{
    int i = 0;

    //loops through the trip
    for (i = 0; i < TRIP_SIZE; i++)
    {
        //since the embarkation cards are appended to the end of the trip array, if it detects an embarkation card that is not filled then it is safe to assume that the rest after the array is also not filled
        if (trip[i].filled == 0)
            i = TRIP_SIZE; //breaks out of the for loop
        else
        {
            printEmbarkCard(trip[i]); //prints the embarkation card for the specific index
        }
    }
}

/*  printTripInfo prints a specific trip layout where each seat is marked 'X' if it has a passenger, 'O' if it is empty
    @param trip - the array containing the passengers (or embarkation cards)
    @return void - no return variable
    Pre-condition: none
*/
void
printTripInfo (Trip trip)
{
    int passenger = 0;
    int i, j;

    int stopIndex = 0;

    //count how many passengers there are in a trip
    for (i = 0; i < TRIP_SIZE; i++)
    {
        if (trip[i].filled == 1)
            passenger++;
    }

    //diff seating arrangements if passengers are less than or more than 13
    if (passenger <= 13)
    {
        //stops at 14 to accomodate the 2 driver slots
        while (stopIndex < 14)
        {
            //loops for every row
            for (i = 0; i < 3; i++)
            {
                //if its the last 2 driver slots, print blank
                //else if, it is an occupied seat, print [X]
                //else, print [O]
                if (stopIndex + i == 13 || stopIndex + i == 14)
                    printf("[D]");
                else if (trip[stopIndex + i].filled == 1)
                    printf("[X]");
                else
                    printf("[O]");
                
            }

            //to prevent the index from going further
            if (stopIndex + i == 14)
            {
                stopIndex = 13;
            }

            //increments by 3s since the for loop loops 3 times
            stopIndex += i;
            printf("\n");
        }
    } else
    {
        //18 because highest index in array is 15 + 1 blank spot + 2 driver slots
        for (j = 0; j < 3; j++)
        {
            for (i = 0; i < 4; i++)
            {
                if (trip[stopIndex + i].filled == 1)
                    printf("[X]");
                else
                    printf("[O]");
            }
            printf("\n");
            stopIndex += i;
        }

        printf ("   ");

        for (i = 0; i < 3; i++)
        {
            if (trip[stopIndex + i].filled == 1)
                printf("[X]");
            else
                printf("[O]");  
        }
        stopIndex += i;

        printf("\n");

        stopIndex += 1;
        if (trip[stopIndex].filled == 1)
            printf("[X]");
        else
            printf("[O]");  

        //2 driver slots with the space in between last passenger and driver
        printf("   [D][D]");
    }
    
}

/*  printDropInfo prints the amount of passengers that are dropping off on each drop-off points in a specific trip
    @param trip - an array containing the embarkation cards
    @param embarkPoint - the integer that corresponds to the embarkation point (Manila to Laguna/Laguna to Manila) of the trip
    @return void - no return variable
    Pre-condition: embarkPoint is correct based on the trip number
*/
void
printDropInfo (Trip trip, int embarkPoint)
{
    printf("\nDrop-off points: <passenger count>");
    printf("\n-------------------------------");
    //Drop-off representations ([index] = <Drop-off point number>)
    //[0] = 1; [1] = 2; [2] = 3; [3] = 4
    int passengers[4] = {0,0,0,0};
    int i;
    
    //counts the number of passengers for different drop-off points
    for (i = 0; i < TRIP_SIZE; i++)
    {
        //use the nDrop - 1 as index
        passengers[trip[i].nDrop - 1] += 1;
    }

    //prints the drop-off points (based on the embarkation point) and the count
    if (embarkPoint == 1)
    {
        printf("\nMamplasan Toll Exit:                                 %d", passengers[0]);
        printf("\nPhase 5, San Jose Village:                           %d", passengers[1]);
        printf("\nMilagros Del Rosario (MRR) Building – East Canopy:   %d", passengers[2]);
    } else if (embarkPoint == 2)
    {
        printf("\nPetron Gas Station:                                  %d", passengers[0]);
        printf("\nGate 4: Gokongwei Gate:                              %d", passengers[1]);
        printf("\nGate 2: North Gate (HSSH):                           %d", passengers[2]);
        printf("\nGate 1: South Gate (LS Building Entrance):           %d", passengers[3]);
    }  

    printf("\n");
}

/*  searchPassenger searches the trips for last names asked by the user and prints their embarkation cards and the amount of matches
    @param trips - the array containing all the trips to scan from
    @return void - no return variable
    Pre-condition: none
*/
void 
searchPassenger (Trip trips[])
{
    string100 space = " ";
    string100 lastname;
    string100 fullname;
    EmbarkCard passenger;

    int i, j;
    int lastnameLength = 0, fullnameLength = 0;
    int counter = 0;
    int startIndex;

    //search query input
    printf ("\nEnter last name: ");
    scanf (" %s", lastname);

    //adds a space on the last name
    strcpy(lastname, strcat(space, lastname));
    
    //gets the length of the last name as a reference to where the index of the full name string where the comparing will start
    lastnameLength = strlen(lastname);

    //loop trips
    for (i = 0; i < MANILA_SIZE + LAGUNA_SIZE; i++)
    {
        //loop embarkation cards per trip
        for (j = 0; j < TRIP_SIZE; j++)
        {
            passenger = trips[i][j];
            if (passenger.filled  == 1)
            {
                strcpy(fullname, passenger.fullname);
                fullnameLength = strlen(fullname);
                //the index where fullname will start, this makes sure that it is only looking at the "last name" part of the string
                startIndex = fullnameLength - lastnameLength;

                //strcmpi is just non-case sensitive strcmp
                if (strcmpi(lastname, (fullname + startIndex)) == 0) //(fullname + startIndex) treats fullname[startIndex] as the start of the string instead of fullname[0]
                {
                    printEmbarkCard(passenger);
                    counter++;
                }
            }
        }
    }

    //pointer dereference removes the program-added space
    printf("\n[NOTIFICATION] %d people with the lastname \"%s\" found.", counter, (lastname + 1));
}