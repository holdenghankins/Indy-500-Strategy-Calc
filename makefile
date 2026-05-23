CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = strat_calc

$(TARGET): strat_calc.o
	$(CC) $(CFLAGS) -o $(TARGET) strat_calc.o

strat_calc.o: strat_calc.c strat_calc.h
	$(CC) $(CFLAGS) -c strat_calc.c

clean:
	rm -f *.o $(TARGET)
