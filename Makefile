outdir=bin/
indir=src/

cc=gcc
ld=gcc

ldopts=
ccopts=

$(outdir)mzna: $(outdir)mzna.o $(outdir)lex.o $(outdir)token.o $(outdir)ast.o $(outdir)parse.o
	$(ld) -o $(outdir)mzna $(outdir)mzna.o $(outdir)lex.o $(outdir)token.o $(outdir)ast.o $(outdir)parse.o $(ldopts)
	rm -f $(outdir)*.o

$(outdir)mzna.o: $(indir)mzna.c
	$(cc) -o $(outdir)mzna.o -c $(indir)mzna.c $(ccopts)

$(outdir)lex.o: $(indir)lex.c
	$(cc) -o $(outdir)lex.o -c $(indir)lex.c $(ccopts)

$(outdir)token.o: $(indir)token.c
	$(cc) -o $(outdir)token.o -c $(indir)token.c $(ccopts)

$(outdir)ast.o: $(indir)ast.c
	$(cc) -o $(outdir)ast.o -c $(indir)ast.c $(ccopts)

$(outdir)parse.o: $(indir)parse.c
	$(cc) -o $(outdir)parse.o -c $(indir)parse.c $(ccopts)

clean:
	rm -f $(outdir)*.o
	rm -f $(outdir)mzna