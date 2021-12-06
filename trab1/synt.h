#ifndef _SYNT_H_
#define _SYNT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_compiler.h"
#include "lex.h"
#include "gen.h"

// Variaveis globais
type_token *lookahead;

// Prototipos
int list();
int listR();
int digit();
int match(int token_tag);

//ADCICIONEI ISSO AQUI
int E();
int ER();
int T();
int TR();
int F();

int main();

#endif //_SYNT_H_