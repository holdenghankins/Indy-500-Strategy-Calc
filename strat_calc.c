#include <stdio.h>
#include <stdlib.h>
#include "strat_calc.h"

int* calcStrat(int lap, int sincePit, int underCaution) {
    int tireAge = calcTireAge(sincePit, underCaution);
    int* stints = findStints(TOTAL - lap, tireAge);

    /*
    Readds the underCaution laps that were not counted for lap age
    % 2 is used to correct for rounding down in calcAge
    */
    if (underCaution % 2 == 0) {
        stints[0] += underCaution / 2;
    } else {
        stints[0] += (underCaution / 2) + 1;
    }

    // Moves lap to last stop before printing
    lap -= sincePit;
    printStints(lap, stints);
    return stints;
}

int calcTireAge(int sincePit, int underCaution) {
    return sincePit - (underCaution / 2);
}

int* findStints(int laps, int tireAge) {
    // Allocate mem for stints
    int* stints = calloc(6, sizeof(int));

    // Sets up known values for 
    stints[0] = tireAge;
    if (laps + tireAge < 40) { // Edge case for no stops remaining
        stints[0] += laps;
        return stints;
    }
    addLapsToStint(&laps, &stints[5], 30);

    // Adds as many target stints as possible
    int stint = 0;
    while (laps >= TARGET) {
        addLapsToStint(&laps, &stints[stint], TARGET - stints[stint]);
        stint++;
    }

    // Adds another stint if it is optimal
    if (laps >= 20) {
        addLapsToStint(&laps, &stints[stint], laps);
        return orderStints(stints);
    }

    // Splits the stops up to prevent one overly long stint and maintain flexability
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
    /*
    Bubble sort is used here since the number of comparisons is only 15
    Readability and simplicity prioritized over minuscule runtime improvement
    */
    for (int i = 0; i < 5; i++) {
        for (int l = 0; l < 5 - i; l++) {
            /*
            Pushes off long stints for as long as possible in hopes of a caution
            Short stints are put at the very end to maximize effectiveness
            */
            if (stints[l] > 33 && stints [l + 1] > 32 && stints[l] > stints[l + 1]) {
                swap(&stints[l], &stints[l + 1]);
            }
        }
    }

    // Moves the isolated 30 lap stint to the end of the other stints
    for (int i = 0; i < 5; i++) {
        if (stints[i] == 0) {
            swap (&stints[i], &stints[5]);
            break;
        }
    }
    return stints;
}

void swap(int* n1, int* n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void printStints(int lap, int* stints) {

    // Last stop : ###
    printf("Last stop: %d\n", lap);

    // Stops remaining: ###   ###...
    printf("Stops remaining: ");
    for (int i = 0; i < 6; i++) {
        if (stints[i] == 0) {
            break;
        }

        lap += stints[i];

        printf("%d     ", lap);
    }

    // Stint lengths: ##   ##...
    printf("\nStint lengths: ");
    for (int i = 0; i < 6; i++) {
        if (stints[i] == 0) {
            break;
        }
        printf("%d     ", stints[i]);
    }
    printf("\n");
}

int main() {
    // 3 values easily available through IndyCar live race data
    int lap = 0;
    int sincePit = 0;
    int underCaution = 0;

    // Asks user for 3 values used in calculation
    printf("INDY 500 STRATEGY CALCULATOR\n\n");
    printf("Current lap: ");
    scanf("%d", &lap);
    printf("Laps since last pit: ");
    scanf("%d", &sincePit);
    printf("Laps under caution: ");
    scanf("%d", &underCaution);
    printf("\n\n");

    // Gets data of stints
    int* stints = calcStrat(lap, sincePit, underCaution);

    // Frees malloc
    free(stints);
    return 0;
}