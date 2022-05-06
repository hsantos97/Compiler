/**
 * @file synt.h
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo do analisado sintatico
 * @version 0.3
 * @date 2022-04-25
 * 
 */

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
int E(type_code *);
int ER(int *, type_code *);
int T(type_code *);
int TR(int *, type_code *);
int F(type_code *);
int digit();
int match(int token_tag);

int main();

#endif //_SYNT_H_