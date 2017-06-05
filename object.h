


#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "intermediate.h"


typedef enum{
    /* Adição  000000 &*/ G_ADD, // R[DR] <- R[SA] + R[SB]
  /* Adição Imediato  000001 &*/ G_ADDI, // R[DR] <- R[SA] + IM
  /* Subtração  000010 &*/ G_SUB, // R[DR] <- R[SA] + \overline{R[SB]} + 1
  /* Subtração Imediato  000011 &*/ G_SUBI, // R[DR] <- R[SA] + \overline{IM} + 1
  /* Multiplicação  000100 &*/ G_MUL, // R[DR] <- R[SA] * R[SB]
  /* Divisão  000101 &*/ G_DIV, // R[DR] <- R[SA] / R[SB]
  /* Incrementa  000110 &*/ G_INC, // R[DR] <- R[SA] + 1
  /* Decrementa  000111 &*/ G_DEC, // R[DR] <- R[SA] - 1
  /* And  001000 &*/ G_AND, // R[DR] <- R[SA] \wedge R[SB]
  /* Or  001001 &*/ G_OR, // R[DR] <- R[SA] \vee R[SB]
  /* Resto  001010 &*/ G_MOD, // R[DR] <- R[SA] \% R[SB]
  /* Xor  001100 &*/ G_XOR, // R[DR] <- R[SA] \bigoplus R[SB]
  /* Not  001101 &*/ G_NOT, // R[DR] <- \overline{R[SA]}
  /* Desloca Esquerda  010000 &*/ G_SHL, // R[DR] <- sl (shamt)R[SA]
  /* Desloca Direita  010001 &*/ G_SHR, // R[DR] <- sr (shamt)R[SA]
  /* Pré-branch  011111 &*/ G_PBC, // se R[SA] = 0, FZ = 1;  se R[SA] < 0, FN = 1;
  /* Branch em Zero  010011 &*/ G_BOZ, // se FZ = 1, então PC <- PC + 1 + IM e FZ = 0, então PC <- PC + 1
  /* Branch em Negativo  010100 &*/ G_BON, // se FN = 1, então PC <- PC + IM e FN = 0, então PC <- PC + 1
  /* Jump  010101 &*/ G_JMP, // PC <- IM
  /* Set on Less Than  010111 &*/ G_SLT, // se R[SA] < R[SB], então R[DR] <- 1
  /* Load  011000 &*/ G_LD, // R[DR] <- M[IM]
  /* Store  011001 &*/ G_ST, // M[IM] <- R[SA]
  /* Load Imediato  011010 &*/ G_LDI, // R[DR] <- IM
  /* Nop  011011 &*/ G_NOP, // Sem Operação
  /* Entrada  011101 &*/ G_IN, // R[DR] <- alavancas
  /* HLT  011100 &*/ G_HLT, // Parar Operação
  /* Saída  011110 &*/ G_OUT // Displays <- R[SA]
}galetype;

typedef enum{
  array_kind,
  variable_kind
}kind_variable;

FILE *file_target_code;



typedef struct type_variable{
    int index;
    int index_array;
    char id[50];
    char scope[50];
    kind_variable kind;
    struct type_variable *next;
}type_variable;

typedef struct{
    type_variable *start;
}list_variables;

typedef struct type_galeto{
    int index;
    int index_array;
    char id[50];
    char scope[50];
    kind_variable kind;
    struct type_galeto *next;
}type_galeto;

typedef struct{
    type_galeto *start;
}list_galetos;

//reserves spaces in memory for variables of a given function
void declaration_variables(list_variables *variables_list, TipoLista *table, char scope[]);

//numbers relate to amount of registers in the operation
void insert_variable(list_variables *variables_list, int index, int index_array, kind_variable kind, char id[], char scope[]);

//searches the position in memory of a variable given its name, scope and array index
int search_variable(list_variables *variables_list, char name[], int array_position, char scope[]);

void format_zero(galetype type, int immediate);

void format_one(galetype type, int register_a, int immediate);

void format_two(galetype type, int register_source, int register_target, int immediate);

void format_three(galetype type, int register_source_a, int register_source_b, int register_target);

void generate_code(list_quadruple *quad_list, TipoLista *table, list_variables *variables_list);

void generate_code_launcher(list_quadruple *quad_list, TipoLista *table);
















#endif
