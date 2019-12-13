output=bin/
source=src/

include=$(source)include
temp=$(output)temp

headers=$(source)$(inc)mzna.h

ldopts=
ccopts=

$(output)mzna: $(temp)mzna.o $(temp)parse.o
	gcc -o $(output)mzna $(temp)mzna.o $(temp)parse.o $(ldopts)

$(temp)mzna.o: $(source)mzna.c
	gcc -o $(temp)mzna.o -c $(source)mzna.c $(ccopts)

$(temp)parse.o: $(source)parse.c
	gcc -o $(temp)parse.o -c $(source)parse.c $(ccopts)