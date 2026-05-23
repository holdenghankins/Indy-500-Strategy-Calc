#include "strat_calc.h"
#include <stdio.h>

int* calcStrat(int lap, int sincePit, int underCaution) {
    int tireAge = calcTireAge(sincePit, underCaution);
    int* stints = findStints(TOTAL - lap, tireAge);
    return stints;
}

int calcTireAge(int sincePit, int underCaution) {
    printf("calc age");
    return sincePit + (underCaution / 2);
}

int* findStints(int laps, int tireAge) {
    printf("find stints");
    int stints[6];
    stints[0] = tireAge;\
    addLapsToStint(&laps, &stints[5], 30);

    int stint = 0;
    while (laps >= TARGET) {
        printf("%d", laps);
        addLapsToStint(&laps, &stints[stint], TARGET - stints[stint]);
        stint++;
    }

    if (laps >= 20) {
        addLapsToStint(&laps, &stints[stint], laps);
        return orderStints(stints);
    }

    while (laps != 0) {
        stint = 0;
        while (stints[stint] != 0) {
            addLapsToStint(&laps, &stints[stint], MIN(laps, 4));
        }
    }
    return orderStints(stints);
}

int* orderStints(int* stints) {
    return stints;
}

void addLapsToStint(int* lapsPtr, int* stintPtr, int lapsToAdd) {
    *stintPtr += lapsToAdd;
    *lapsPtr -= lapsToAdd;
}

int main() {
    printf("running...");
    int* stints = calcStrat(0, 0, 0);
    for (int i = 0; i < 6; i++) {
        printf("%d ", stints[i]);
    }
    return 0;
}