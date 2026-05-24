#ifndef STRAT_CALC_H
#define STRAT_CALC_H

// Find minimum value
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Values that can be editied depending on race conditions
const int TARGET = 33; // Optimal length of a stop
const int TOTAL = 200; // All laps during race (yellow and green)

// Contains prompts to ask user for values
int main();

// 'main' method for calculating strategy
// finds tire age, finds stints, then prints those stints
int* calcStrat(int lap, int sincePit, int underCaution);

// All laps under caution are considered 0.5 of a lap
// This is not a convinience number and tracks with 2015 where the race started under caution
int calcTireAge(int sincePit, int underCaution);

// Finds teh total number of stints and how long the should last
int* findStints(int laps, int tireAge);

// Subtracts lapsToAdd from laps and adds it to stint (in array stints[int])
void addLapsToStint(int* lapsPtr, int* stintPtr, int lapsToAdd);

// Puts the stints in an optimized order, pushing off longer and shorter stints
// Keeps 0s at end since they are ignored later
int* orderStints(int* stints);

// Generic swap function
void swap(int*, int*);

// Displays last stop, remaining stops, and lengths of each stint to user
void printStints(int lap, int* stints);

#endif