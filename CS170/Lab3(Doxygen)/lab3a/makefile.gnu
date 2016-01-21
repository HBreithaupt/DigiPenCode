#MACROS   =============================

CC=g++
CFLAGS=-c -Wall -Wextra -Werror -ansi -pedantic -O -Wconversion 

OUTDIR=gnu/
OBJECTS=$(OUTDIR)main.o $(OUTDIR)fibonacci.o
EXE=fib

#TARGETS  =============================


$(OUTDIR)$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTDIR)$(EXE)
	
$(OUTDIR)fibonacci.o: fibonacci.cpp
	$(CC) $(CFLAGS) fibonacci.cpp -o $(OUTDIR)fibonacci.o
	
$(OUTDIR)main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(OUTDIR)main.o
	
clean: 
	rm $(OUTDIR)$(EXE) $(OBJECTS)