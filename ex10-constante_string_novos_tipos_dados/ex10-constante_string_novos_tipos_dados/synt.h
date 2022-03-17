/**
 * @file synt.h
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo do analisado sintatico
 * @version 0.4
 * @date 2022-02-04
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
#include "symbols.h"

/*
 * Gramatica: 
 *      program -> declarations  statements
 *      declarations -> declaration declarations | [vazio]
 *      declaration -> int id;
 *      statements -> statement statements | [vazio]
 *      statement -> read id; | write id;
 */

// Prototipos
void program (void);
void declarations(void);
void statements (void);
int declaration(void);
int statement(void);

int main();

#endif //_SYNT_H_