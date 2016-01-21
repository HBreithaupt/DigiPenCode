GCC=gcc
MSC=cl

GCCFLAGS=-ansi -Wall -Wextra -pedantic -Wstrict-prototypes -Wmissing-prototypes -Wdeclaration-after-statement -O2
MSCFLAGS=/EHa /W4 /Za /Zc:forScope /nologo /D_CRT_SECURE_NO_DEPRECATE /D"_SECURE_SCL 0" /O2i /GL

VALGRIND_OPTIONS=-q --leak-check=full
DIFF_OPTIONS=-y --strip-trailing-cr --suppress-common-lines

OSTYPE := $(shell uname)
ifeq ($(OSTYPE),Linux)
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

OBJECTS0=spvector.c
DRIVER0=driver.c

gcc0:
	$(GCC) -o $@.exe $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) 
msc0:
	$(MSC) -Fe$@.exe $(DRIVER0) $(OBJECTS0) $(MSCFLAGS) 
clean:
	rm -f *.exe *.tds *.o *.obj *manifest*
