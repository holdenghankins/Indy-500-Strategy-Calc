#include "strat_calc.h"
#include <stdio.h>
#include <stdlib.h>

int* calcStrat(int lap, int sincePit, int underCaution) {
    int tireAge = calcTireAge(sincePit, underCaution);
    int* stints = findStints(TOTAL - lap, tireAge);
    return stints;
}

int calcTireAge(int sincePit, int underCaution) {
    printf("calc age\n");
    return sincePit + (underCaution / 2);
}

int* findStints(int laps, int tireAge) {
    printf("find stints\n");
    int* stints = calloc(6, sizeof(int));

    stints[0] = tireAge;

    addLapsToStint(&laps, &stints[5], 30);

    int stint = 0;
    while (laps >= TARGET) {
        addLapsToStint(&laps, &stints[stint], TARGET - stints[stint]);
        stint++;
    }

    printf("calculated laps\n");
    if (laps >= 20) {
        addLapsToStint(&laps, &stints[stint], laps);
        return orderStints(stints);
    }

    while (laps != 0) {
        stint = 0;
        while (stints[stint] != 0) {
            addLapsToStint(&laps, &stints[stint], MIN(laps, 4));
            stint++;
        }
    }
    return orderStints(stints);
}

void addLapsToStint(int* lapsPtr, int* stintPtr, int lapsToAdd) {
    *stintPtr += lapsToAdd;
    *lapsPtr -= lapsToAdd;
}

int* orderStints(int* stints) {
    for (int i = 0; i < 5; i++) {
        for (int l = 0; l < 5 - i; l++) {
            if (stints[l] > 33 && stints [l + 1] > 32 && stints[l] < stints[l + 1]) {
                swap(&stints[l], &stints[l + 1]);
            }
        }
    }
    return stints;
}

void swap(int* n1, int* n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int main() {
    printf("running...\n");
    int* stints = calcStrat(0, 0, 0);
    for (int i = 0; i < 6; i++) {
        printf("%d ", stints[i]);
    }
    free(stints);
    return 0;
}