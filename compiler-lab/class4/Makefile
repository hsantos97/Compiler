gram:  gram.tab.o  lex.yy.o 
	gcc lex.yy.o gram.tab.o  -o gram
	
	
lex.yy.o:   lex.yy.c
	gcc -c lex.yy.c
	
gram.tab.o:  gram.tab.c
	gcc -c gram.tab.c

lex.yy.c:  gram.l
	flex gram.l

	
gram.tab.c:   gram.y
	bison -d gram.y -o gram.tab.c
	
