outdir=bin/
indir=src/

cc=gcc
ld=gcc

ldopts=
ccopts=

$(outdir)mzna: $(outdir)mzna.o $(outdir)parse.o
	$(ld) -o $(outdir)mzna $(outdir)mzna.o $(outdir)parse.o $(ldopts)
	rm -f $(outdir)*.o

$(outdir)mzna.o: $(indir)mzna.c
	$(cc) -o $(outdir)mzna.o -c $(indir)mzna.c $(ccopts)

$(outdir)parse.o: $(indir)parse.c
	$(cc) -o $(outdir)parse.o -c $(indir)parse.c $(ccopts)