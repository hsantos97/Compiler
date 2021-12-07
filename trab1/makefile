compiler: lex.o synt.o gen.o
	gcc -o compiler lex.o synt.o gen.o -I. -g -fcommon

lex.o: lex.c
	gcc -c -g lex.c -fcommon

synt.o: synt.c
	gcc -c -g synt.c -fcommon

gen.o: gen.c
	gcc -c -g gen.c -fcommon

tstLex: lex.o tst_lex.o
	gcc -o tstLexCompiler lex.o tst_lex.o -I. -g 

tst_lex.o: tst_lex.c
	gcc -c -g tst_lex.c

clean:
	rm *.o compiler