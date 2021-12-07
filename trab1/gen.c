// Inclusao do cabecalho
#include "gen.h"

/**
 * @brief Funcao que gera codigo de montagem para SOMA
 * 
 */
void genAdd() {
    printf("pop rax\n");
    printf("pop rbx\n");
    printf("add rax,rbx\n");
    printf("push rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para SUBTRACAO
 * 
 */
void genSub() {
    printf("pop rbx\n");
    printf("pop rax\n");
    printf("sub rax,rbx\n");
    printf("push rax\n");
}
//ADICIONEI ISSO AQUI 
void genMult(){
    printf("pop rax\n");
    printf("pop rbx\n");
    printf("mult rax,rbx\n");
    printf("push rax\n");
}
void genDiv(){
    printf("pop rax\n");
    printf("pop rbx\n");
    printf("div rax,rbx\n");
    printf("push rax\n");
}
/**
 * @brief Funcao que gera codigo de montagem para armazenamento de NUMERAL
 * 
 * @param num_string 
 */
void genNum(char num_string[MAX_TOKEN]) {
    printf("mov rax,%s\n", num_string);
    printf("push rax\n");
}