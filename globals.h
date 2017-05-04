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
#define VARIABLE_LENGHT 2
#define EXP_VARIABLE_LENGHT 1
#define LABEL_SIZE 10

/* Yacc/Bison generates its own integer values
 * for tokens
 */
typedef int TokenType;


// extern FILE* source; /* source code text file */
// extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int linenumber; /* source line number*/

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

// typedef enum {StmtK, ExpK} NodeKind;
// typedef enum {IfK, WhileK, AssignK, ReturnK, VarK, VecK, FuncK, FuncVarK, FuncVecK} StmtKind;
// typedef enum {TypeK, RelOpK, ArithOpK, ConstK, IdK, VecIndexK, CallK} ExpKind;

typedef enum {DecK, StmtK, ExpK, TypeK} NodeKind;
typedef enum {IfK, WhileK, AssignK, ReturnK, CallK} StmtKind;
typedef enum {ConstK, IdK, OpK} ExpKind;
typedef enum {FuncDecK, VarK, CompK, ParamK} DecKind;

/* ExpType is used for type checking */
typedef enum {Void, Integer, Boolean} ExpType;

#define MAXCHILDREN 3

union treeKind{
    StmtKind stmt;
    ExpKind exp;
    DecKind dec;
    ExpType typ;
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
    int call_stmt;
    char * scope;
    NodeKind nodekind;
    union treeKind kind;
    struct treeAttr attr;
    ExpType type; /* for type checking of exps */
} TreeNode;

static char * OP_ADD = "ADD";
static char * OP_ADDI = "ADDI";
static char * OP_SUB = "SUB";
static char * OP_SUBI = "SUBI";
static char * OP_AND = "AND";
static char * OP_ANDI = "ANDI";
static char * OP_OR = "OR";
static char * OP_ORI = "ORI";
static char * OP_NOT = "NOT";
static char * OP_SR = "SR";
static char * OP_SL = "SL";
static char * OP_LOAD = "LOAD";
static char * OP_LOADI = "LOADI";
static char * OP_STORE = "STORE";
static char * OP_JUMP = "JUMP";
static char * OP_JUMPI = "JUMPI";
static char * OP_JZI = "JZI";
static char * OP_JN = "JN";
static char * OP_JNI = "JNI";
static char * OP_MOVE = "MOVE";
static char * OP_NOP = "NOP";
static char * OP_HLT = "HLT";
static char * OP_IN = "IN";
static char * OP_OUT = "OUT";


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
