/**
 * @file gen.c
 * @author Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo gerador de codigo
 * @version 0.2
 * @date 2022-02-23
 * 
 */

// Inclusao do cabecalho
#include "gen.h"

// Inclusao explicita de variaveis globais de outro contexto (symbols.h)
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
char output_file_name[MAX_CHAR];
FILE *output_file;

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

/**
 * @brief Funcao que gera codigo de montagem para MULTIPLICACAO
 * 
 */
void genMult() {
    printf("pop rax\n");
    printf("pop rbx\n");
    printf("imult rax,rbx\n");
    printf("push rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para DIVISAO
 * 
 */
void genDiv() {
    printf("pop rbx\n");
    printf("pop rax\n");
    printf("idiv rax,rbx\n");
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

/**
 * @brief Funcao que gera um preambulo que permite o uso das funcoes do C (scanf e printf)
 * 
 */
void gen_preambule(void) {
    fprintf(output_file, ";UFMT-Compiladores\n");
    fprintf(output_file, ";Prof. Ivairton\n");
    fprintf(output_file, ";Procedimento para geracao do executavel apos compilacao (em Linux):\n");
    fprintf(output_file, ";(1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>\n");
    fprintf(output_file, ";(2) likedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>\n\n");
    fprintf(output_file, "extern printf\n");
    fprintf(output_file, "extern scanf\n");
}

/**
 * @brief Funcao que gera codigo da secao de dados (declaracao de variaveis).
 */
void gen_data_section(void) {
    int i, n;
    
    fprintf(output_file, "\n\tsection .data\n");

    // emite strings de formato fixo
    //fprintf(output_file, "str0: db \"%%d\",13,10,0\n");
    //fprintf(output_file, "str1: db \"%%s\",13,10,0\n");
    //fprintf(output_file, "str2: db \"%%c\",13,10,0\n");
    //fprintf(output_file, "str3: db \"%%lf\",13,10,0\n");
    //fprintf(output_file, "\n");

    // processa cada simbolo da tabela de strings
    //n = symbol_table_string.n_strings;
    //for (i = 0; i < n; i++) {
    //    fprintf(output_file, "%s: db %s, 0\n", 
    //        symbol_table_string.string[i].name,
    //        symbol_table_string.string[i].value);
    //}
    //fprintf(output_file,"\n");
    
    // processa cada simbolo da tabela e gera um ponteiro para cada variavel na memoria
    n = global_symbol_table_variables.n_variables;
    for (i = 0; i < n; i++) {
       fprintf(output_file, "%s: ", global_symbol_table_variables.variable[i].name); 
       
       switch(global_symbol_table_variables.variable[i].type) { //Por enquanto gera endereco zero
            case INT:
                fprintf(output_file, "dd \"%%d\", 4\n");
                break;
            case STRING:
                fprintf(output_file, "db \"                \" \n");
                break;
            case FLOAT:
                fprintf(output_file, "dd \"%%lf\", 16\n");
                break;
            case CHAR:
                fprintf(output_file, "dd \"%%c\", 1\n");
                break;
            default:
                fprintf(output_file, "[ERRO] Tipo desconhecido.\n");       
                break;           
       }
    }

    n = symbol_table_string.n_strings;
    for (i = 0; i < n; i++) {
        fprintf(output_file, "%s: db %s\n",
            symbol_table_string.string[i].name, 
            symbol_table_string.string[i].value);
    }
}

/**
 * @brief Funcao que gera a marcacao do inicio da secao de codigo
 * 
 */
void gen_preambule_code(void) {
    fprintf(output_file, "\n\tsection .text\n");
    fprintf(output_file, "\tglobal main,_start\n");
    fprintf(output_file, "main:\n");
    fprintf(output_file, "_start:\n");
}

/**
 * @brief Funcao que encerra o codigo inserindo comandos de fechamento
 * 
 */
void gen_epilog_code(void) {
    //fprintf(output_file, "\nret\n");
    fprintf(output_file, "\n;encerra programa\n");
    fprintf(output_file, "mov ebx,0\n");
    fprintf(output_file, "mov eax,1\n");
    fprintf(output_file, "int 0x80\n");
}


/**
 * @brief Gera codigo para o comando READ
 * 
 * @param lexeme_of_id nome do identificador
 */
void gen_read(char *lexeme_of_id, int type) {
    /*
    //Codigo antigo, demanda estudo para ser usado com o liker GCC no Linux
    fprintf(output_file, "mov rdi, fmtstr0\n");
    fprintf(output_file, "mov rsi, %s\n", lexeme_of_id);
    fprintf(output_file, "mov rax, 0\n");
    fprintf(output_file, "call scanf\n");
    */
    switch (type) {
        case INT:
            fprintf(output_file, "\n;le valor inteiro\n");
            fprintf(output_file, "mov edx,4\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,3\n");
            fprintf(output_file, "int 0x80\n");
            break;
        case FLOAT:
            fprintf(output_file, "\n;le valor float\n");
            fprintf(output_file, "mov edx,16\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,3\n");
            fprintf(output_file, "int 0x80\n");
            break;
        case CHAR:
            fprintf(output_file, "\n;le valor char\n");
            fprintf(output_file, "mov edx,1\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,3\n");
            fprintf(output_file, "int 0x80\n");
            break;
        case STRING:
            fprintf(output_file, "\n;le valor string\n");
            fprintf(output_file, "mov edx,16\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,3\n");
            fprintf(output_file, "int 0x80\n");
            break;
    }
}

/**
 * @brief Gera codigo para o comando WRITE
 * 
 * @param lexeme_of_id nome do identificador
 */
void gen_write(char *lexeme_of_id, int type) {
    /*
    //Codigo antigo, demanda estudo para ser usado com o liker GCC no Linux
    fprintf(output_file, "mov rdi, fmtstr0\n");
    fprintf(output_file, "mov rsi, [rel %s]\n", lexeme_of_id);
    fprintf(output_file, "mov rax, 0\n");
    fprintf(output_file, "call printf\n");
    */
    switch (type) {
        case INT:
            fprintf(output_file, "\n;escreve valor inteiro\n");
            fprintf(output_file, "mov edx,4\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,4\n");
            fprintf(output_file, "int 0x80\n");
            break;
        case FLOAT:
            fprintf(output_file, "\n;escreve valor float\n");
            fprintf(output_file, "mov edx,16\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,4\n");
            fprintf(output_file, "int 0x80\n");
            break;
        case CHAR:
            fprintf(output_file, "\n;escreve valor char\n");
            fprintf(output_file, "mov edx,1\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,4\n");
            fprintf(output_file, "int 0x80\n");
            break;
        case STRING:
            fprintf(output_file, "\n;escreve valor string\n");
            fprintf(output_file, "mov edx,16\n");
            fprintf(output_file, "mov ecx,%s\n", lexeme_of_id);
            fprintf(output_file, "mov ebx,1\n");
            fprintf(output_file, "mov eax,4\n");
            fprintf(output_file, "int 0x80\n");
            break;
    }
}