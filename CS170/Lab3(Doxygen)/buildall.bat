cls
make -f makefile.gnu clean
make -f makefile.ms clean
dir gnu ms
pause
make -f makefile.gnu
make -f makefile.ms
dir gnu ms
dir gnu ms