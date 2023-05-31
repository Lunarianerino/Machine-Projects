/*  countEmpty returns the number of elements where trip[i].filled = 0
    @param trip - an alias containing an array of size 16 containing EmbarkCard types
    @return int - the number of elements in trip that is considered "empty"
    Pre-conditioon: Trip structs always contain 16 elements of EmbarkCard structs
*/
int
countEmpty (Trip trip)
{
    int counter = 0;
    int i;

    for (i = 0; i < TRIP_SIZE; i++)
    {
        //if the trip[i].filled is empty, add 1 to the counter
        if (trip[i].filled != 1)
            counter++;
    }

    return counter;

}

/*  getLowestPrio returns the first element with the lowest priority number that is present in a trip (1 is the highest and 6 is the lowest)
    @param trip - an alias called Trip that contains 16 elements of EmbarkCard
    @return int - returns the lowest priority present in the list
    Pre-condition: trip[i].nPrio can only be between or equal to 1 and 7.
*/
int 
getLowestPrio (Trip trip,  int currPrio)
{
    int i;
    int lowest = currPrio; //lowest > higher priority (highest priority is 1)
    for (i = 0; i < TRIP_SIZE; i++)
    {
        //if nPrio is lower than the current lowest in the priority scale, make nPrio the new lowest
        if (trip[i].nPrio > lowest)
            lowest = trip[i].nPrio;
    }

    return lowest;
}

/*  moveUser moves the user variable to an element of curr if it contains an element that has a lower priority than user. It moves the replaced variable into an element in destination that has a lower priority 
    @param destination - is a Trip alias where one of the elements will be replaced by user
    @param user - is an EmbarkCard struct that will be assigned to one of the elements in destination that currently has a lower priority value
    @return EmbarkCard - returns the EmbarkCard replaced by the user.
    Pre-condition: destination already contains an EmbarkCard with a lower priority number than user
*/
EmbarkCard 
moveUser (  Trip destination,
            EmbarkCard user)
{
    int i;
    int destinationIndex;
    EmbarkCard temp;

    temp = user;
    for (i = 0; i < TRIP_SIZE; i++)
    {
        //switch user with the element with a lower priority
        if (destination[i].nPrio >= temp.nPrio)
        {
            destinationIndex = i;
            temp = destination[i];
        }
    }
    destination[destinationIndex] = user;
    return temp;
}

/*  sort sorts the array using the selection sort algorithm
    @param trip - is an array of EmbarkCards that will be sorted by priority
    @return void - no return variable
    Pre-condition: All values of trip[n].nPrio are positive integers
*/
void
sort (Trip trip)
{
    int i, j;
    int min;
    EmbarkCard temp;

    //first index to compare
    for (i = 0; i < TRIP_SIZE - 1; i++)
    {
        min = i;

        //second index to compare
        for (j = i + 1; j < TRIP_SIZE; j++)
        {
            //if priority of the first index is lower than the second one
            //OR if the value of the first index is higher than the second one
            //if true, set min to j
            if (trip[min].nPrio > trip[j].nPrio)
                min = j;
        }

        //swap the values of min and i; the values change if the if statement before is true, otherwise it will remain the same
        temp = trip[i];
        trip[i] = trip[min];
        trip[min] = temp;
    }
}

/*  assignTrip assigns the EmbarkCard struct type (user) to an empty element in a struct Trip variable (a struct type containing a size 16 array of EmbarkCard)
    @param user - an EmbarkCard struct type that contains the data to be appended to an empty element on the Trip
    @param trip - an alias that contains an array of EmbarkCard
    @return void - no return variable
    Pre-condition: user.filled = 1 and there is an element in trip where trip[index].filled = 0;
*/
void 
assignTrip (EmbarkCard user, 
            Trip trips[],
            string5 tripList[],
            int tripIndex)
{  
    int i = 0;
    int replacingOnIndex = 0;
    int vacant;

    EmbarkCard default_user;
    default_user.filled = 0;

    //while the current user variable is not empty
    while (user.filled != 0)
    {
        replacingOnIndex = 0;
        vacant = countEmpty(trips[tripIndex]);
        
        //if there are vacant slots, in a specific trip, assign user to that trip
        if (vacant > 0)
        {
            
            //loops through the trip until it finds an element thats not filled8
            while (trips[tripIndex][i].filled != 0)
                i++;

            //i is positioned in an index that has .filled = 0
            trips[tripIndex][i] = user;
            
            printf("\n[SUCCESS] ID %s has been placed on the trip %s!\n", user.idNum, tripList[tripIndex]);

            //assign user variable with blank values so it exits the loop and asks the user for another input.
            user = default_user;
        }
        else
        {
            //if the trip is full, try to find the next available trip
            //if the user is taking a trip from Manila to Laguna
            if (user.embarkPoint == 1)
            {
                //iterate through every trips index assigned to the Manila to Laguna Embarkation Points (index 0 - 8)
                for (i = tripIndex; i < LAGUNA_SIZE; i++)
                {
                    //if it finds a trip with a vacant slot OR a trip that has someone with a lower prio than EmbarkCard user, save the index corresponding to the trip and exit the loop.
                    if (countEmpty(trips[i]) > 0 || getLowestPrio(trips[i], user.nPrio) > user.nPrio)
                    {
                        replacingOnIndex = 1;
                        tripIndex = i;
                        i = LAGUNA_SIZE;
                    }
                }
            } else if (user.embarkPoint == 2)
            {
                //iterate through every trips index assigned to the Laguna to Manila Embarkation Points (index 9 - 19)
                for (i = tripIndex; i < LAGUNA_SIZE + MANILA_SIZE; i++)
                {
                    //if it finds a trip with a vacant slot OR a trip that has someone with a lower prio than EmbarkCard user, save the index corresponding to the trip and exit the loop.
                    if (countEmpty(trips[i]) > 0 || getLowestPrio(trips[i], user.nPrio) > user.nPrio)
                    {
                        replacingOnIndex = 1;
                        tripIndex = i;
                        i = MANILA_SIZE + LAGUNA_SIZE;
                    }
                }
            }

            //at this point user.tripNum hasn't been changed yet, so if there is no difference between tripList[tripIndex] and user.tripNum,
            //it means that the value of tripIndex hasnt changed and there are no available slots in any of the trips, meaning it is all full with no lower priority present
            //else, switch the user and the current EmbarkCard present on the tripIndex, causing the loop to happen again if the NOW CURRENT user is not empty.
            if (strcmp(tripList[tripIndex], user.tripNum) == 0 && replacingOnIndex == 0)
            {
                printf("\n[ERROR] All trips are full so ID %s has been removed to accomodate higher priority passengers, SORRY!\n", user.idNum);
                user = default_user; //reset user values, it will just loop the whole thing again and again anyways.
            }
            else
            {
                printf("\n[SUCCESS] ID %s has been MOVED/PLACED on the trip %s!\n", user.idNum, tripList[tripIndex]);
                strcpy(user.tripNum, tripList[tripIndex]);
                user = moveUser(trips[tripIndex], user);
            }

        }
    }
}

/*  copyTrip copies the contents of one trip to another
    @param dest - the trip variable where the trip will copied to
    @param source - the trip variable where the trip will be copied from
    @return void - no return variable
    Pre-condition: none
*/
void
copyTrip(Trip dest, Trip source)
{
    int i;
    //loop for the index of the trip
    for (i = 0; i < TRIP_SIZE; i++)
    {
        //copies source to destination
        dest[i] = source[i];
    }
}