compiler: lex.o synt.o gen.o symbols.o
	gcc -o compiler lex.o synt.o gen.o symbols.o -I. -g

compiler_win: lex.o synt.o gen_win.o symbols.o
	gcc -o compiler4win lex.o synt.o gen_win.o symbols.o -I. -g

lex.o: lex.c
	gcc -c -g lex.c

synt.o: synt.c
	gcc -c -g synt.c

gen.o: gen.c
	gcc -c -g gen.c

gen_win.o: gen_win.c
	gcc -c -g gen_win.c

symbols.o: symbols.c
	gcc -c -g symbols.c

tstLex: lex.o tst_lex.o
	gcc -o tstLexCompiler lex.o tst_lex.o -I. -g

tst_lex.o: tst_lex.c
	gcc -c -g tst_lex.c

clean:
	rm *.o compiler