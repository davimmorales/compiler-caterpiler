/****************************************************/
/* File: parse.h                                    */
/* The parser interface for the C- compiler         */
/****************************************************/

#include "globals.h"
#include "util.h"

#ifndef _INTERMEDIATE_H
#define _INTERMEDIATE_H_


/* Function parse returns the newly
 * constructed syntax tree
 */
typedef enum {
  // arithmetic [0~3]
  AddK, SubK, TimK, OvrK,
  // relational [4~9]
  EqlK, NeqK, GtrK, GeqK, LsrK, LeqK,
  // data transfer [10~14]
  AsvK, AsaK, CstK, VstK, AstK,
  // i|o [15,16]
  InnK, OutK,
  // function/procedure [17~19]
  PrmK, CalK, RetK,
  // flow [20~23]
  IffK, GtoK, HltK, LblK,
  //control
  PrmArrK, PrmVarK
 } OpKind;

typedef enum {Empty, IntConst, String, Temp, LabAddr} AddrKind;

typedef struct{
    AddrKind kind;
    int value;
    char name[20];
} Address;

typedef struct quadruple{
  int index;
  char scope[50];
  OpKind op;
  Address address_1, address_2, address_3;
  struct quadruple *next;
}quadruple;

typedef struct{
    quadruple *start;
}list_quadruple;

void insert_quadruple(list_quadruple *quad_list, quadruple *quad);

int string2int(const char *num);

void insert_quadruples(list_quadruple *quad_list);

void printWTable(TipoLista *lista, int index);

void generate_icode_launcher(list_quadruple *quad_list, TreeNode *tree, TipoLista *vetor);

static void generate_statement(list_quadruple *quad_list, TreeNode *tree);

void generate_intermediate_code(list_quadruple *quad_list, TreeNode *tree);

void add_parameters_to_table(TipoLista *table, list_quadruple *quad_list);

void print_quadruple_list(list_quadruple *quad_list);

void store_quadruple(OpKind o, AddrKind k1, AddrKind k2, AddrKind k3,
                     int v1, int v2, int v3,
                     char n1[], char n2[], char n3[]);

void add_indexes_to_table(TipoLista *table, list_quadruple *quad_list);


#endif
