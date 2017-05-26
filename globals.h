/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for C- compiler            */
/* must come before other include files             */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header")
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself
 */

#ifndef YYPARSER

/* the name of the following file may change */
#include "cminus.tab.h"

/* ENDFILE is implicitly defined by Yacc/Bison,
 * and not included in the tab.h file
 */
#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 6

/* Yacc/Bison generates its own integer values
 * for tokens
 */
typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int linenumber; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK, ExpK} NodeKind;
typedef enum {IfK, WhileK, AssignK, ReturnK, VarK, VecK, FuncK, FuncVarK, FuncVecK} StmtKind;
typedef enum {TypeK, RelOpK, ArithOpK, ConstK, IdK, VecIndexK, CallK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void, Integer, Boolean} ExpType;

#define MAXCHILDREN 3

union treeKind{
    StmtKind stmt;
    ExpKind exp;
};

struct treeAttr{
    TokenType oprtr;
    int value;
    char * name;
};

typedef struct treeNode{
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    int linenumber;
    char * scope;
    NodeKind nodekind;
    union treeKind kind;
    struct treeAttr attr;
    ExpType type; /* for type checking of exps */
} TreeNode;

typedef struct TipoID{
    char nomeID[20];
    char tipoID[20];
    char tipoData[10];
    char escopo[30];
    int linhas[50];
    int intermediate_index;
    int declaration_flag;
    int array_size;
    int top;
    struct TipoID *prox;
}TipoID;

typedef struct{
    TipoID *start;
}TipoLista;

// extern TipoLista hash_table[211];


/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error;
#endif
