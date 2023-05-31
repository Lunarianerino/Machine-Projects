

//number of trips Manila to Laguna
#define LAGUNA_SIZE 9
//number of trips Laguna to Manila
#define MANILA_SIZE 11

//Maximum Size of the Bus
#define TRIP_SIZE 16

typedef char string5[6];
typedef char string100[101];

typedef char IDString[9];

typedef struct 
{
    int nDay;
    int nMonth;
    int nYear;
}Date;

typedef struct 
{   
    //0 if the card is not filled up yet, 1 if it is.
    int filled;
    Date date;
    string5 tripNum;

    string100 fullname;
 

    IDString idNum;

    /*
        1 - Faculty and ASF with Inter-campus assignments
        2 - Students with Inter-campus enrolled subjects or enrolled in thesis using Inter-campus facilities 
        3 - Researchers
        4 - School Administrators (Academic Coordinators level and up for Faculty and ASF, and Director level and up for APSP)
        5 - University Fellows
        6 - Employees and Students with official business
    */
    int nPrio;

    /*
        Drop-off points
        1 - Mamplasan Toll Exit / Petron Gas Station
        2 - Phase 5, San Jose Village / Gate 4: Gokongwei Gate 
        3 - Milagros Del Rosario (MRR) Building – East Canopy / Gate 2: North Gate (HSSH)
        4 - NULL / Gate 1: South Gate (LS Building Entrance)  
    */
    int nDrop;

    /*
        1 = Manila to Laguna 
        2 = Laguna to Manila
    */
    int embarkPoint;
}EmbarkCard;

typedef EmbarkCard Trip[TRIP_SIZE];
