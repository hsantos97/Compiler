#include "synt.h"

/**
 * @brief Verifica se o proximo caracter (a frente) na cadeia eh o esperado
 *
 * @param token_tag (int) codigo do token a ser verificado
 * @return int true/false
 */
int match(int token_tag)
{
    if (lookahead->tag == token_tag)
    {
        lookahead = getToken(); // Pega o proximo token por meio do lexico
        return true;
    }
    return false;
}

/**
 * @brief Atribui as operações consecutivas de TR
 *
 * @return int true/false
 */
void handleTR(int *lastOperation, type_code *trCode, type_code *tr1Code, type_code *fCode)
{
    switch (*lastOperation)
    {
    case '*':
        strcat(trCode->code, trCode->temp);
        strcat(trCode->code, "=");
        strcat(trCode->code, fCode->temp);
        strcat(trCode->code, "*");
        strcat(trCode->code, tr1Code->temp);
        strcat(trCode->code, "\n");
        break;
    case '/':
        strcat(trCode->code, trCode->temp);
        strcat(trCode->code, "=");
        strcat(trCode->code, fCode->temp);
        strcat(trCode->code, "/");
        strcat(trCode->code, tr1Code->temp);
        strcat(trCode->code, "\n");
        break;
    case '\0':
        strcat(trCode->code, trCode->temp);
        strcat(trCode->code, "=");
        strcat(trCode->code, fCode->temp);
        strcat(trCode->code, "\n");
        break;
    }
}

/**
 * @brief Atribui as operações consecutivas de ER
 *
 * @return int true/false
 */
void handleER(int *lastOperation, type_code *erCode, type_code *er1Code, type_code *tCode)
{
    switch (*lastOperation)
    {
    case '+':
        strcat(erCode->code, erCode->temp);
        strcat(erCode->code, "=");
        strcat(erCode->code, tCode->temp);
        strcat(erCode->code, "+");
        strcat(erCode->code, er1Code->temp);
        strcat(erCode->code, "\n");
        break;
    case '-':
        strcat(erCode->code, erCode->temp);
        strcat(erCode->code, "=");
        strcat(erCode->code, tCode->temp);
        strcat(erCode->code, "-");
        strcat(erCode->code, er1Code->temp);
        strcat(erCode->code, "\n");
        break;
    case '\0':
        strcat(erCode->code, erCode->temp);
        strcat(erCode->code, "=");
        strcat(erCode->code, tCode->temp);
        strcat(erCode->code, "\n");
        break;
    }
}
/**
 * @brief Regra de derivacao da gramatica: DIGIT
 *
 * @return int true/false
 */
// int digit()
// {
//   char aux_lexema[MAX_TOKEN];
//   strcpy(aux_lexema, lookahead->lexema); // armazena temporariamente o lexema

//   if (match(NUM))
//   {
//     genNum(aux_lexema); // Geracao de codigo por meio de funcao do GERADOR
//     return true;
//   }
//   return false;
// }

/**
 * @brief Regra de derivacao da gramatica: E->TE'
 *
 * @return int true/false
 */
int E(type_code *eCode)
{
    int test1, test2;
    type_code *t_code;
    type_code *er_code;
    int *last_operation;

    last_operation = (int *)malloc(sizeof(int));
    t_code = (type_code *)malloc(sizeof(type_code));
    er_code = (type_code *)malloc(sizeof(type_code));

    newTemp(eCode->temp);

    test1 = T(t_code);

    if (test1)
    {
        test2 = ER(last_operation, er_code);
    }

    // strcpy(eCode->code, t_code->code);
    // test2 = ER(last_operation, er_code);

    strcpy(eCode->code, t_code->code);
    strcat(eCode->code, er_code->code);

    switch (*last_operation)
    {
    case '+':
        strcat(eCode->code, eCode->temp);
        strcat(eCode->code, "=");
        strcat(eCode->code, t_code->temp);
        strcat(eCode->code, "+");
        strcat(eCode->code, er_code->temp);
        strcat(eCode->code, "\n");
        break;
    case '-':
        strcat(eCode->code, eCode->temp);
        strcat(eCode->code, "=");
        strcat(eCode->code, t_code->temp);
        strcat(eCode->code, "-");
        strcat(eCode->code, er_code->temp);
        strcat(eCode->code, "\n");
        break;
    case '\0':
        strcat(eCode->code, eCode->temp);
        strcat(eCode->code, "=");
        strcat(eCode->code, t_code->temp);
        strcat(eCode->code, "\n");
        break;
    }

    return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: E'->+TE'
 *
 * @return int true/false
 */
int ER(int *lastOperation, type_code *erCode)
{
    type_code *tCode;
    type_code *er1Code;
    int *lOperation;

    lOperation = (int *)malloc(sizeof(int));
    tCode = (type_code *)malloc(sizeof(type_code));
    er1Code = (type_code *)malloc(sizeof(type_code));

    if (lookahead->tag == '+')
    {
        int b1, b2;
        match('+');
        *lastOperation = (int)'+';
        newTemp(erCode->temp);

        b1 = T(tCode);
        // strcpy(erCode->temp, tCode->temp);
        if (b1)
            b2 = ER(lOperation, er1Code);

        strcpy(erCode->code, tCode->code);
        strcat(erCode->code, er1Code->code);
        handleER(lOperation, erCode, er1Code, tCode);

        return b1 && b2;
    }
    else if (lookahead->tag == '-')
    {
        int b1, b2;
        match('-');
        *lastOperation = (int)'-';
        newTemp(erCode->temp);

        b1 = T(tCode);
        // strcpy(erCode->temp, tCode->temp);
        if (b1)
            b2 = ER(lOperation, er1Code);

        strcpy(erCode->code, tCode->code);
        strcat(erCode->code, er1Code->code);
        handleER(lOperation, erCode, er1Code, tCode);

        return b1 && b2;
    }
    else if (lookahead->tag == ENDTOKEN || lookahead->tag == '*' || lookahead->tag == '/' || lookahead->tag == OPEN_PAR || lookahead->tag == CLOSE_PAR)
    {
        strcpy(erCode->temp, "");
        (*lastOperation) = '\0';
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Regra de derivacao da gramatica: T->FT'
 *
 * @return int true/false
 */
int T(type_code *tCode)
{
    type_code *fCode;
    type_code *trCode;
    int b1, b2, *lastOperation;
    newTemp(tCode->temp);

    lastOperation = (int *)malloc(sizeof(int));
    fCode = (type_code *)malloc(sizeof(type_code));
    trCode = (type_code *)malloc(sizeof(type_code));

    b1 = F(fCode);
    if (b1)
        b2 = TR(lastOperation, trCode);

    strcpy(tCode->code, fCode->code);
    strcat(tCode->code, trCode->code);

    switch (*lastOperation)
    {
    case '*':
        strcat(tCode->code, tCode->temp);
        strcat(tCode->code, "=");
        strcat(tCode->code, fCode->temp);
        strcat(tCode->code, "*");
        strcat(tCode->code, trCode->temp);
        strcat(tCode->code, "\n");
        break;
    case '/':
        strcat(tCode->code, tCode->temp);
        strcat(tCode->code, "=");
        strcat(tCode->code, fCode->temp);
        strcat(tCode->code, "/");
        strcat(tCode->code, trCode->temp);
        strcat(tCode->code, "\n");
        break;
    case '\0':
        strcat(tCode->code, tCode->temp);
        strcat(tCode->code, "=");
        strcat(tCode->code, fCode->temp);
        strcat(tCode->code, "\n");
        break;
    }
    return b1 && b2;
}

/**
 * @brief Regra de derivacao da gramatica: T'->*FT'
 *
 * @return int true/false
 */
int TR(int *lastOperation, type_code *trCode)
{
    type_code *fCode;
    type_code *tr1Code;
    int *lOperation;

    lOperation = (int *)malloc(sizeof(int));
    fCode = (type_code *)malloc(sizeof(type_code));
    tr1Code = (type_code *)malloc(sizeof(type_code));

    if (lookahead->tag == '*')
    {
        int b1, b2;
        match('*');
        *lastOperation = (int)'*';
        newTemp(trCode->temp);

        b1 = F(fCode);

        if (b1)
        {
            b2 = TR(lOperation, tr1Code);
        }

        strcat(trCode->code, fCode->code);
        strcat(trCode->code, tr1Code->code);
        handleTR(lOperation, trCode, tr1Code, fCode);

        return b1 && b2;
    }
    else if (lookahead->tag == '/')
    {
        int b1, b2;
        match('/');
        *lastOperation = (int)'/';
        newTemp(trCode->temp);

        b1 = F(fCode);
        // strcpy(trCode->temp, fCode->temp);

        if (b1)
        {
            b2 = TR(lOperation, tr1Code);
        }

        strcat(trCode->code, fCode->code);
        strcat(trCode->code, tr1Code->code);
        handleTR(lOperation, trCode, tr1Code, fCode);

        return b1 && b2;
    }
    else if (lookahead->tag == ENDTOKEN || lookahead->tag == '+' || lookahead->tag == '-' || lookahead->tag == OPEN_PAR || lookahead->tag == CLOSE_PAR)
    {
        strcpy(trCode->temp, "");
        (*lastOperation) = '\0';
        return true;
    }
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: F->(E)
 *
 * @return int true/false
 */
int F(type_code *fCode)
{
    if (lookahead->tag == OPEN_PAR)
    {
        int test1, test2;
        type_code *eCode;
        eCode = (type_code *)malloc(sizeof(type_code));

        match(OPEN_PAR);
        test1 = E(eCode);
        if (test1)
            test2 = match(CLOSE_PAR);

        strcpy(fCode->temp, eCode->temp);
        strcpy(fCode->code, eCode->code);
        return test1 && test2;
    }
    else if (lookahead->tag == NUM)
    {
        int token;
        char lexema[MAX_TOKEN];

        strcpy(lexema, lookahead->lexema);
        token = match(NUM);

        newTemp(fCode->temp);
        strcpy(fCode->code, fCode->temp);
        strcat(fCode->code, "=");
        strcat(fCode->code, lexema);
        strcat(fCode->code, "\n");

        return token;
    }
    return false;
}

//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 *
 * @return int
 */
int main()
{

    type_code *e_code;
    int accept;

    e_code = (type_code *)malloc(sizeof(type_code));
    accept = false;

    initLex();              // Carrega codigo
    lookahead = getToken(); // Inicializacao do lookahead

    accept = E(e_code); // Chamada da derivacao/funcao inicial da gramatica

    // Imprime na tela o codigo intermediario gerado
    printf("%s\n", e_code->code);

    // Verifica aceitacao da cadeia/codigo
    if (accept)
    {
        printf("\tCadeia PERTENCENTE a linguagem\n");
    }
    else
    {
        printf("\tCadeia NAO pertencente a linguagem\n");
    }

    return 1;
}