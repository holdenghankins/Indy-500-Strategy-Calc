#ifndef STRAT_CALC_H
#define STRAT_CALC_H

#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int TARGET = 33;
const int TOTAL = 200;

int main();
int* calcStrat(int lap, int sincePit, int underCaution);
int calcTireAge(int sincePit, int underCaution);
int* findStints(int laps, int tireAge);
void addLapsToStint(int* lapsPtr, int* stintPtr, int lapsToAdd);
int* orderStints(int* stints);
void swap(int*, int*);

#endif