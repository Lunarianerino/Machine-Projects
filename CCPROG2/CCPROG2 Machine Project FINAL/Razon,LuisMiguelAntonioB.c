/*********************************************************************************************************  
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts 
learned.  I have constructed the functions and their respective algorithms and corresponding code by myself.  The 
program was run, tested, and debugged by my own efforts.  I further certify that I have not copied in part or whole or 
otherwise plagiarized the work of other students and/or persons.                                                                                                                  
																													Luis Miguel Antonio B. Razon, DLSU ID# 12115681
*********************************************************************************************************/ 





#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "vars.h"

#include "tripFunctions.c"
#include "printFunctions.c"
#include "arrayControls.c"
#include "fileControls.c"

int 
main ()
{
    Date date;
    
    //assigns the date today to the Date struct
    date = getDate();

	//initializing all of the possible trips (there are 20 total trips)
    Trip trips[LAGUNA_SIZE + MANILA_SIZE];

    //trip numbers for both of the two routes combined, AE101 - AE109 = Manila to Laguna, AE150 - AE160 = Laguna to Manila
    string5 tripList[LAGUNA_SIZE + MANILA_SIZE] = {"AE101", "AE102", "AE103", "AE104", "AE105", "AE106", "AE107", "AE108", "AE109", 
                                                    "AE150", "AE151", "AE152", "AE153", "AE154", "AE155", "AE156", "AE157", "AE158", "AE159", "AE160"};
	
	//array variables
	int tripIndex;
    int i, j;

    //initializing the input variables
    int input = 1;
    int arrow_input = -1;
    int trip_input = 0;

	//user variables
    string5 tripNum;
    Trip tempTrip;
    EmbarkCard user;
    user.filled = 0;
    int vacant;

    //initializes all the EmbarkCard.filled to 0 and the priority is initialized to 7 (to prevent possible garbage values)
    for (j = 0; j < MANILA_SIZE + LAGUNA_SIZE; j++)
    {
        for (i = 0; i < TRIP_SIZE; i++)
        {
            trips[j][i].filled = 0;
            //lowest priority
            trips[j][i].nPrio = 7;
        }
    }


    //loads the text file for the trip today (if it exists)
    loadTrip(trips, date);

    //Main loop starts until user decides to exit
    while(arrow_input != 0) 
    {
        printf("\nToday is %.2d/%.2d/%d", date.nDay, date.nMonth, date.nYear);

        printf("\n[1] Passenger\n[2] Arrows Express Personnel\nEnter the number corresponding to your status: ");
        scanf("%d", &input);
        //discards unwanted characters until the user presses enter
        while ( getchar() != '\n' );
        
        if (input == 1)
        {
            //declares an empty variable again
            user.filled = 0;
            user.date = date;
            printf("\n");

            //INPUTS FOR THE REQUIRED DETAILS
            //"empties" the string to prepare for a new input
            user.tripNum[0] = '\0';
            inputTrip(user.tripNum, &tripIndex);

            vacant = countEmpty(trips[tripIndex]);
            //notify the user if the trip they selected is full
            if(vacant == 0)
                printf("\n[WARNING] Current Trip is full. You will be automatically moved to the next available trip if you have the LOWEST PRIORITY NUMBER compared to everyone else.\n");

            printf("\n");
            user.fullname[0] = '\0';
            inputName(user.fullname);

            printf("\n");
            user.idNum[0] = '\0';
            inputIDNum(user.idNum);

            printf("\n");
            user.nPrio = inputPrio(0);

            printf("\n");
            user.embarkPoint = getEmbarkationPoint(tripIndex);

            printf("\n");
            user.nDrop = inputDropPoint(user.embarkPoint, 0);
            user.filled = 1;

            printEmbarkCard(user);
            assignTrip(user, trips, tripList, tripIndex);
        }
        else if (input == 2)
        {
            printf("\n[1] View Trip Information");
            printf("\n[2] Load Passenger Information");
            printf("\n[3] Search Passenger");
            printf("\n[4] View Past Trips");
            printf("\n[0] Exit");
            printf("\nEnter the number corresponding to your status: ");
            scanf("%d", &arrow_input);
            //discards unwanted characters until the user presses enter
            while ( getchar() != '\n' );
            if (arrow_input == 1)
            {
                //Input for trip number to be used as a reference for the rest of the inputs
                tripNum[0] = '\0';
                inputTrip(tripNum, &tripIndex);

                printf("\nTrip: %s", tripNum);
                printf("\n[1] View Trip Info");
                printf("\n[2] View Drop-off information");
                printf("\n[3] View passenger information");
                printf("\nEnter the number corresponding to your choice: ");
                scanf("%d", &trip_input);
                //discards unwanted characters until the user presses enter
                while ( getchar() != '\n' );
                printf("\n");

                if (trip_input == 1)
                {
                    //prints the trip in the specified order
                    printTripInfo (trips[tripIndex]);
                }
                else if (trip_input == 2)
                    printDropInfo(trips[tripIndex], getEmbarkationPoint(tripIndex)); //prints how many people are dropping to a specific drop point
                else if (trip_input == 3)
                {
                    //sorts the specified trip by priority
                    copyTrip(tempTrip, trips[tripIndex]); //copies the trip to a temporary one to not change the order of the original
                    sort(tempTrip); //sorts by priority
                    printTrip(tempTrip); //prints the sorted trip
                } else
                    printf("\n[INPUT ERROR] Invalid Input, please refer to the numbers beside the choices.");
            } 
            else if (arrow_input == 2)
                loadCard(trips); //loads user embarkation card
            else if (arrow_input == 3)
                searchPassenger(trips); //searches for a specific passenger (by last name)
            else if (arrow_input == 4)
            {
                //loads trips from a previous date (by "emulating" that day)
                date = inputDate();
                loadTrip(trips, date);
            } 
            else if (arrow_input == 0)
                saveFile(trips, date); //saves all the trips into a text file in a specific format
            else 
                printf("\n[INPUT ERROR] Invalid Input, please refer to the numbers beside the choices.");
        } 
        else 
            printf("\n[INPUT ERROR] Invalid Input, please refer to the numbers beside the choices.");
    }
    
    return 0;
}
