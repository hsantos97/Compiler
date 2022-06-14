tab_simb:  tab_simb.tab.o  lex.yy.o 
	gcc lex.yy.o tab_simb.tab.o  -o tab_simb
	
	
lex.yy.o:   lex.yy.c
	gcc -c lex.yy.c
	
tab_simb.tab.o:  tab_simb.tab.c
	gcc -c tab_simb.tab.c

lex.yy.c:  tab_simb.l
	flex tab_simb.l

	
tab_simb.tab.c:   tab_simb.y
	bison -d tab_simb.y -o tab_simb.tab.c
	
