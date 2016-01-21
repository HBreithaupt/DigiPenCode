#MACROS   =============================

CC=g++
CFLAGS=-c -g -Wall -ansi -pedantic -Wextra -Werror

OUTDIR=gnu/
OBJECTS=$(OUTDIR)Main.o $(OUTDIR)Command.o $(OUTDIR)Inventory.o $(OUTDIR)Map.o $(OUTDIR)Parser.o
EXE=Game

#TARGETS  =============================

$(OUTDIR)$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTDIR)$(EXE)
	
$(OUTDIR)Main.o : Main.cpp Command.h Parser.h Inventory.h Map.h
	$(CC) $(CFLAGS) Main.cpp -o $(OUTDIR)Main.o
	
$(OUTDIR)Command.o : Command.cpp Command.h
	$(CC) $(CFLAGS) Command.cpp -o $(OUTDIR)Command.o

$(OUTDIR)Inventory.o : Inventory.cpp Inventory.h
	$(CC) $(CFLAGS) Inventory.cpp -o $(OUTDIR)Inventory.o
	
$(OUTDIR)Map.o : Map.cpp Map.h Inventory.h
	$(CC) $(CFLAGS) Map.cpp -o $(OUTDIR)Map.o

$(OUTDIR)Parser.o : Command.cpp Parser.h
	$(CC) $(CFLAGS) Parser.cpp -o $(OUTDIR)Parser.o

clean : 
	rm $(OUTDIR)$(EXE) $(OBJECTS)

