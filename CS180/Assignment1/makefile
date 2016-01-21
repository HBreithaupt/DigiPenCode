c

all : $(EXE)
	
$(EXE) : $(OBJS)
	$(CC) $(OBJS) -o $(EXE) $(LFLAGS) 

driver.o : sample-driver.c slist.h PRNG.h
	$(CC) $(CFLAGS) -c sample-driver.c -o driver.o

slist.o : slist.c slist.h
	$(CC) $(CFLAGS) -c slist.c -o slist.o

PRNG.o : PRNG.c PRNG.h
	$(CC) $(CFLAGS) -c PRNG.c -o PRNG.o

clean :
	$(ERASE) $(OBJS) $(EXE)
