/**
 * @file symbols.h
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo do gerador da tabela de simbolos
 * @version 0.1
 * @date 2022-02-04
 */

#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <stdio.h>
#include <string.h>

#include "struct_compiler.h"

#define MAX_SYMBOLS 4096
#define MAX_CHAR 32
#define MAX_PARAMS 8
#define MAX_FUNCS 64
#define MAX_STRINGSZ 512
#define MAX_STRINGS 64
#define MAX_TOKSZ 256 

// Entrada da tabela de simbolos de variaveis
struct st_symbol_table_entry {
    int type;
    char name[MAX_TOKSZ];
    int addr;
};
typedef struct st_symbol_table_entry type_symbol_table_entry;

// Tabela de simbolos de variaveis
struct st_symbol_table_variables {
    type_symbol_table_entry variable[MAX_SYMBOLS];
    int n_variables;
    struct st_symbol_table_variables *next;
};
typedef struct st_symbol_table_variables type_symbol_table_variables;

// Entrada da tabela de simbolos de strings
struct st_sym_string_entry {
    char name[MAX_TOKSZ];
    char value[MAX_STRINGSZ];
};
typedef struct st_sym_string_entry type_symbol_table_string_entry;

// tabela de simbolos de strings
struct st_symbol_table_strings {
    type_symbol_table_string_entry string[MAX_SYMBOLS];
    int n_strings;
};
typedef struct st_symbol_table_strings type_symbol_table_string;

/* Preparo para tratamento de funcoes
// Estrutura da tabela de simbolos para funcoes
struct st_sym_func {
    char type;
    char name[MAX_TOKSZ];
    type_symbol params[MAX_PARAMS];
    int nparams;
};
typedef struct st_sym_func type_symbol_function_entry;
*/


// Prototipos
type_symbol_table_entry *sym_find(char *s, type_symbol_table_variables *stv);
type_symbol_table_entry *sym_declare(char *name, int type, int addr, type_symbol_table_variables *stv);
type_symbol_table_string_entry *sym_string_find(char *s);
type_symbol_table_string_entry *sym_string_declare(char *s);
void initSymbolTableVariables(type_symbol_table_variables *stv);
void initSymbolTableString();
//Funcoes destinadas a DEBUG
void printSTVariables(type_symbol_table_variables *stv);
void printSTString();

/* Preparo para tratamento de funcoes
type_symbol_function *sym_func_find(char *s);
type_symbol_function *sym_func_declare(char *name,char type, type_symbol_table_entry params[MAX_PARAMS], int nparams);
*/
#endif //_SYMBOLS_H_