//#ifndef _GLOBALS_H_
//#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern char scope[50];
extern char name[50];



typedef enum {none_nK, statementK, expK} node_kind;
typedef enum {none_stK, ifK, whileK, assignK, returnK, varK, vecK, funcK, funcvarK, funcvecK} statement_kind;
typedef enum {none_expK, TypeK, RelOpK, ArithOpK, ConstK, IdK, VecIndexK, CallK} expression_kind;
typedef enum {none_typeK, intK, voidK, boolK} type_kind;
typedef int TokenType;

union treeKind{
    statement_kind stmt;
    expression_kind exp;
};

struct treeAttr{
    TokenType op;
    int value;
    char * name;
};

typedef struct treeNode{
  char *str;
  char *name;
  char * scope;
  type_kind type;//where 0=none, 1=int and 2 = void
  int value;
  int lineno;
  node_kind nodekind;
  union treeKind kind;
  struct treeAttr attr;
  struct treeNode *child;
  struct treeNode *sibling;
}TreeNode;

typedef struct TipoID{
    char nomeID[20];
    char tipoID[20];
    char tipoData[10];
    char escopo[30];
    int linhas[50];
    int top;
    struct TipoID *prox;
}TipoID;

typedef struct TypeSync{
  char name[45];
  char scope[45];
  int type;//where 1 stands for var, 2 for array and 3 for function
  int value;
  int top;
  struct TypeSync *next;
}TypeSync;

typedef struct{
  TypeSync *start;
}SyncList;

typedef struct{
    TipoID *start;
}TipoLista;


void inicializaLista(TipoLista *lista);

void insert(SyncList *list, char scope[], char nameID[], char typeID[]);

void printIDList(SyncList *list);
