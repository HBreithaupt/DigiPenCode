# Macros ========================================

CC=gcc
CFLAGS= -D_XOPEN_SOURCE -Wall -Wextra -ansi -pedantic -O -Wno-unused-result -g
ERASE=rm
EXE = parent-matrix child-matrix

# TARGETS ========================================

parent : parent-matrix.c
	$(CC) $(CFLAGS) parent-matrix.c -o parent-matrix
	
child : child-matrix.c
	$(CC) $(CFLAGS) child-matrix.c -o child-matrix

ipc : 
	ipcrm -M 123
	
clean : 
	$(ERASE) $(EXE)
