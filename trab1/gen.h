#ifndef _GEN_H_
#define _GEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_compiler.h"

// Prototipos
void genAdd();
void genSub();
void genMult(); // ADICIONEI ISSO AQUI 
void genDiv();
void genNum(char num_string[MAX_TOKEN]);

#endif //_GEN_H_