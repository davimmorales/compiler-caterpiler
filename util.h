/****************************************************/
/* File: util.h                                     */
/* Utility functions for the C- compiler            */
/* Rodrigo de Farias Ramires                        */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/* Auxiliary defines used inside customPrint procedure
 * to print formatted text
 */
#define BOLD "\033[1m"
#define RESET "\033[0m"

/* Procedure customPrint customizes print
 * of text in bold to the listing file
 */
void customPrint(const char* string, int bold);

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken(TokenType, const char*);

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);

/* Function countParamArg counts how many parameters/arguments
 * exist in the function declaration/call
 */
int countParamArg(TreeNode * t);

/* Function getParamArgName gets parameter's/argument's name
 * of a function declaration/call
 */
char * getParamArgName(TreeNode * t, int index);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char *);

/* Function joinNameScope joins name and scope to
 * produce new scope for all children nodes of a function
 */
char * joinNameScope(char * name, char * sep, char * scope);

/* Function setScope defines scope for all children
 * nodes of a function
 */
void setScope(TreeNode * t, char * scope);

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree(TreeNode *);

#endif
