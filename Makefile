outdir=bin/
indir=src/

cc=gcc
ld=gcc

ldopts=
ccopts=

$(outdir)mzna: $(outdir)mzna.o $(outdir)lex.o $(outdir)token.o
	$(ld) -o $(outdir)mzna $(outdir)mzna.o $(outdir)lex.o $(outdir)token.o $(ldopts)
	rm -f $(outdir)*.o

$(outdir)mzna.o: $(indir)mzna.c
	$(cc) -o $(outdir)mzna.o -c $(indir)mzna.c $(ccopts)

$(outdir)lex.o: $(indir)lex.c
	$(cc) -o $(outdir)lex.o -c $(indir)lex.c $(ccopts)

$(outdir)token.o: $(indir)token.c
	$(cc) -o $(outdir)token.o -c $(indir)token.c $(ccopts)