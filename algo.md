LAP TARGET = 33, TOTAL LAPS = 200

arr calc_strat(laps left l, tire age t)
    arr stints[6] {0, 0, 0, 0, 0, 0}
    addLapsToStint(l, [5], 30)
    stints[0] = t
    

    int stint = 0
    while (laps < TARGET)
        addLapsToStint(l*, [stint]*, TARGET - [stint])
        stint++

    if (laps > 20)
        addLapsToStint(l, [stint], *l)
        return orderLaps(stints, stint)
    




void addLapsToStint(int* lapsLeft, int* stint, int lapsToAdd)
    lapsLeft -= lapsToAdd
    stint += lapsToAdd

basic algo
    create arr of [6] 0s
    add 30 to [5]
    add current stint to [0]
    push current stint to 33
    add 33 to each stint until less than 33 laps remaining
    if remaining laps > 20, make new stint, return ordered

    if laps < 4, add all to 1 stint
    