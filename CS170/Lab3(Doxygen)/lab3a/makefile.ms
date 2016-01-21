#MACROS   =============================

CC=cl
CFLAGS=/c /nologo /W4 /EHsc /Za /WX

OUTDIR=ms/
OBJECTS=$(OUTDIR)main.obj $(OUTDIR)fibonacci.obj
EXE=fib

#TARGETS  =============================


$(OUTDIR)$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) -Fe$(OUTDIR)$(EXE)
	
$(OUTDIR)fibonacci.obj: fibonacci.cpp
	$(CC) $(CFLAGS) fibonacci.cpp -Fo$(OUTDIR)fibonacci.obj
	
$(OUTDIR)main.obj: main.cpp
	$(CC) $(CFLAGS) main.cpp -Fo$(OUTDIR)main.obj
	
clean:
	rm $(OUTDIR)$(EXE) $(OBJECTS)