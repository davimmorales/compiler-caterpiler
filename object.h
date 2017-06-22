


#ifndef _object_H_
#define _object_H_

#include "intermediate.h"
#include <stdbool.h>

#define STACK_SIZE 500

// globals
int line_return[STACK_SIZE];
int temporary_return[STACK_SIZE];
int top;


typedef enum{
    /*0 Adição  000000 &*/ G_ADD, // R[DR] <- R[SA] + R[SB]
  /*1 Adição Imediato  000001 &*/ G_ADDI, // R[DR] <- R[SA] + IM
  /*2 Subtração  000010 &*/ G_SUB, // R[DR] <- R[SA] + \overline{R[SB]} + 1
  /*3 Subtração Imediato  000011 &*/ G_SUBI, // R[DR] <- R[SA] + \overline{IM} + 1
  /*4 Multiplicação  000100 &*/ G_MUL, // R[DR] <- R[SA] * R[SB]
  /*5 Divisão  000101 &*/ G_DIV, // R[DR] <- R[SA] / R[SB]
  /*6 Incrementa  000110 &*/ G_INC, // R[DR] <- R[SA] + 1
  /*7 Decrementa  000111 &*/ G_DEC, // R[DR] <- R[SA] - 1
  /*8 And  001000 &*/ G_AND, // R[DR] <- R[SA] \wedge R[SB]
  /*9 Or  001001 &*/ G_OR, // R[DR] <- R[SA] \vee R[SB]
  /*10 Resto  001010 &*/ G_MOD, // R[DR] <- R[SA] \% R[SB]
  /*11 Xor  001100 &*/ G_XOR, // R[DR] <- R[SA] \bigoplus R[SB]
  /*12 Not  001101 &*/ G_NOT, // R[DR] <- \overline{R[SA]}
  /*13 Desloca Esquerda  010000 &*/ G_SHL, // R[DR] <- sl (shamt)R[SA]
  /*14 Desloca Direita  010001 &*/ G_SHR, // R[DR] <- sr (shamt)R[SA]
  /*15 Pré-branch  011111 &*/ G_PBC, // se R[SA] = 0, FZ = 1;  se R[SA] < 0, FN = 1;
  /*16 Branch em Zero  010011 &*/ G_BOZ, // se FZ = 1, então PC <- PC + 1 + IM e FZ = 0, então PC <- PC + 1
  /*17 Branch em Negativo  010100 &*/ G_BON, // se FN = 1, então PC <- PC + IM e FN = 0, então PC <- PC + 1
  /*18 Jump  010101 &*/ G_JMP, // PC <- IM
  /*19 Set on Less Than  010111 &*/ G_SLT, // se R[SA] < R[SB], então R[DR] <- 1
  /*20 Load  011000 &*/ G_LD, // R[DR] <- M[IM]
  /*21 Store  011001 &*/ G_ST, // M[IM] <- R[SA]
  /*22 Load Imediato  011010 &*/ G_LDI, // R[DR] <- IM
  /*23 Nop  011011 &*/ G_NOP, // Sem Operação
  /*24 Entrada  011101 &*/ G_IN, // R[DR] <- alavancas
  /*25 HLT  011100 &*/ G_HLT, // Parar Operação
  /*26 Pré Saída  011110 &*/ G_POUT, // Displays <- R[SA]
  /*27 Saída  100000 &*/ G_OUT, // Displays <- R[SA]
  /*28 Load Registrador 1000001*/ G_LDR, // R[DR] <- M[R[SA]]
  /*29 Store Registrador 100010*/ G_STR // M[R[SA]] -> R[DR]
}galetype;

typedef enum{
  label_kind,
  call_kind
}kind_jump;

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

typedef struct type_instruction{
  int line;
  int register_a;
  int register_b;
  int register_c;
  int immediate;
  int target_label;
  kind_jump jump;
  char label_name[50];
  galetype type;
  struct type_instruction *next;
}type_instruction;

typedef struct type_parameter{
  AddrKind kind;
  int value;
  char name[50];
  char scope[50];
  struct type_parameter *next;
}type_parameter;

typedef struct type_label{
  AddrKind type;
  char name[50];
  int index;
  int line;
  struct type_label *next;
}type_label;

typedef struct{
  type_parameter *start;
}list_parameters;

typedef struct{
    type_instruction *start;
}list_instructions;

typedef struct{
    type_variable *start;
}list_variables;

typedef struct{
    type_label *start;
}list_labels;

//reserves spaces in memory for variables of a given function
void declaration_variables(list_variables *variables_list, TipoLista *table, char scope[]);

//numbers relate to amount of registers in the operation
void insert_variable(list_variables *variables_list, int index, int index_array, kind_variable kind, char id[], char scope[]);

void insert_label(list_labels *labels_list, AddrKind type, char name[], int index, int line);


//searches the position in memory of a variable given its name, scope and array index
int search_variable(list_variables *variables_list, char name[], int array_position, char scope[]);

void format_zero(list_instructions *instructions_list, galetype type, int immediate, AddrKind kind, char label_string[], kind_jump jump);

void format_one(list_instructions *instructions_list, galetype type, int register_a, int immediate);

void format_two(list_instructions *instructions_list, galetype type, int register_source, int register_target, int immediate);

void format_three(list_instructions *instructions_list, galetype type, int register_source_a, int register_source_b, int register_target);

void generate_code(list_instructions *instructions_list, list_quadruple *quad_list, TipoLista *table, list_variables *variables_list, list_parameters *parameters_list, list_labels *labels_list);

void generate_code_launcher(list_quadruple *quad_list, TipoLista *table);

void consume_parameters(TipoLista *table, list_instructions *instructions_list, list_parameters *parameters_list,list_variables *variables_list, char function[]);

void treat_jumps_n_branches(list_instructions *instructions_list, list_labels *labels_list);










#endif
