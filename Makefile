CC = g++
PROG = simpleGA
OBJ = main.o
DEP = individual.h

all: $(PROG)

$(PROG): $(OBJ) $(DEP)
	$(CC) -o $@ $^
	
clean:
	rm -rf *.o $(PROG)
