#ifndef _STRUCT_COMPILER_
#define _STRUCT_COMPILER_

// Definicao de constantes para todo o compilador
#define MAX_CHAR 32
#define MAX_TOKEN 32

#define true 1  //por conveniencia, para facilitar leitura de codigo
#define false 0 //por conveniencia, para facilitar leitura de codigo

// Definicao dos codigos
#define ENDTOKEN '\0'
#define ERROR -1
#define NUM 1
#define PLUS '+'
#define MINUS '-'
#define MULT '*' //ADICIONEI ISSO AQUI
#define DIV '/' //ADICIONEI ISSO AQUI
#define OPENPAREN '(' //ADICIONEI ISSO AQUI
#define CLOSEPAREN ')' //ADICIONEI ISSO AQUI

// Definicao da estrutura de dados 'token'
struct st_token {
    int tag;
    char lexema[MAX_CHAR];
};
typedef struct st_token type_token;

#endif //_STRUCT_COMPILER_