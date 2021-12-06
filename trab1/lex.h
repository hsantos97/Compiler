#ifndef _LEX_H_
#define _LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_compiler.h"

//Variaveis globais
int pos;
char string[MAX_CHAR];

// Prototipos
void initLex();
type_token *getToken();

#endif //_LEX_H_