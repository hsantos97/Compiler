/**
 * @file gen.c
 * @author Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo gerador de codigo
 * @version 0.3
 * @date 2022-04-25
 * 
 */

// Inclusao do cabecalho
#include "gen.h"

/**
 * @brief Funcao que cria novo 'temporario' para a geracao de codigo intermediario
 * 
 * @param label 
 */
void newTemp(char label[32]) {
    static int label_count = 0;
    sprintf(label, "t%d", label_count++);
}