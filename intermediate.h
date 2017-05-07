/****************************************************/
/* File: parse.h                                    */
/* The parser interface for the C- compiler         */
/****************************************************/

#ifndef _INTERMEDIATE_H
#define _INTERMEDIATE_H_

/* Function parse returns the newly
 * constructed syntax tree
 */
typedef enum {
  // arithmetic
  AddK, SubK, MulK, DivK,
  // relational
  EqlK, NeqK, GtrK, GeqK, LsrK, LeqK,
  // data transfer
  AsvK, AsaK,
  // i|o
  InnK, OutK,
  // function/procedure
  PrmK, CalK, RetK,
  // flow
  IffK, GtoK, HltK
 } OpKind;

typedef enum {Empty, IntConst, String, Temp} AddrKind;

// typedef struct {
//   AddrKind kind;
//     union{
//       int val;
//       char *name;
//     }contents;
// } Address;

typedef struct{
    AddrKind kind;
    int value;
    char name[20];
} Address;

typedef struct{
  OpKind op;
  Address address_1, address_2, address_3;
  struct quadruple *next;
}quadruple;


static void generate_statement(TreeNode *tree);

void generate_intermediate_code(TreeNode *tree);

#endif
