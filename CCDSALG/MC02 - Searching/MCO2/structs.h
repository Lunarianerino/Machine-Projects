#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#ifndef STRUCTS_H_
#define STRUCTS_H_

//GENERAL CONSTANTS FOR PROGRAM
#define MAX 1000000
#define kMAX 7
#define kSIZE 16400

typedef char String[MAX + 1];
typedef char String7[kMAX + 1];

typedef struct StringDist{
    String7 data;
    int count;
} StringDist;

#endif
