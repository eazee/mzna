outdir=bin/
indir=src/
objdir=$(outdir)obj/

cc=gcc
ld=gcc

ldopts=
ccopts=

$(outdir)mzna: $(objdir)mzna.o $(objdir)lex.o $(objdir)token.o $(objdir)ast.o $(objdir)parse.o
	$(ld) -o $(outdir)mzna $(objdir)mzna.o $(objdir)lex.o $(objdir)token.o $(objdir)ast.o $(objdir)parse.o $(ldopts)

$(objdir)mzna.o: $(indir)mzna.c
	$(cc) -o $(objdir)mzna.o -c $(indir)mzna.c $(ccopts)

$(objdir)lex.o: $(indir)lex.c
	$(cc) -o $(objdir)lex.o -c $(indir)lex.c $(ccopts)

$(objdir)token.o: $(indir)token.c
	$(cc) -o $(objdir)token.o -c $(indir)token.c $(ccopts)

$(objdir)ast.o: $(indir)ast.c
	$(cc) -o $(objdir)ast.o -c $(indir)ast.c $(ccopts)

$(objdir)parse.o: $(indir)parse.c
	$(cc) -o $(objdir)parse.o -c $(indir)parse.c $(ccopts)

prepare:
	mkdir -p bin/obj

clean:
	rm -f $(objdir)*.o
	rm -f $(outdir)mzna