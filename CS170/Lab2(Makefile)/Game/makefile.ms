#MACROS   =============================

CC=cl
CFLAGS=/c /W4 /EHa /D_CRT_SECURE_NO_WARNINGS /nologo /Za /WX

OUTDIR=ms/
OBJECTS=$(OUTDIR)Main.obj $(OUTDIR)Command.obj $(OUTDIR)Inventory.obj $(OUTDIR)Map.obj $(OUTDIR)Parser.obj
EXE=Game.exe

#TARGETS  =============================

$(OUTDIR)$(EXE) : $(OBJECTS)
	$(CC) $(OBJECTS) -Fe$(OUTDIR)$(EXE)
	
$(OUTDIR)Main.obj : Main.cpp Command.h Parser.h Inventory.h Map.h
	$(CC) $(CFLAGS) Main.cpp -Fo$(OUTDIR)Main.obj
	
$(OUTDIR)Command.obj : Command.cpp Command.h
	$(CC) $(CFLAGS) Command.cpp -Fo$(OUTDIR)Command.obj

$(OUTDIR)Inventory.obj : Inventory.cpp Inventory.h
	$(CC) $(CFLAGS) Inventory.cpp -Fo$(OUTDIR)Inventory.obj
	
$(OUTDIR)Map.obj : Map.cpp Map.h Inventory.h
	$(CC) $(CFLAGS) Map.cpp -Fo$(OUTDIR)Map.obj

$(OUTDIR)Parser.obj : Command.cpp Parser.h
	$(CC) $(CFLAGS) Parser.cpp -Fo$(OUTDIR)Parser.obj

clean : 
	rm $(OUTDIR)$(EXE) $(OBJECTS)

