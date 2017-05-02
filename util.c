/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the C- compiler                              */
/* Rodrigo de Farias Ramires                        */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure customPrint customizes print
 * of text in bold to the listing file
 */
void customPrint(const char* string, int bold){
    if(bold == TRUE)
        fprintf(listing, BOLD "%s" RESET, string);
    else
        fprintf(listing, "%s", string);
}

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken(TokenType token, const char* tokenString){
    switch(token){
        case IF:
            fprintf(listing, "Keyword: if\n");
            break;
        case ELSE:
            fprintf(listing, "Keyword: else\n");
            break;
        case WHILE:
            fprintf(listing, "Keyword: while\n");
            break;
        case INT: 
            fprintf(listing, "Keyword: int\n");
            break;   
        case VOID:
            fprintf(listing, "Keyword: void\n");
            break;
        case RETURN:
            fprintf(listing, "Keyword: return\n");
            break;
        case ASSIGN:
            fprintf(listing, "Special symbol: =\n");
            break;
        case LT:
            fprintf(listing, "Special symbol: <\n");
            break;
        case LTE:
            fprintf(listing, "Special symbol: <=\n");
            break;
        case GT:
            fprintf(listing, "Special symbol: >\n");
            break;
        case GTE:
            fprintf(listing, "Special symbol: >=\n");
            break;
        case EQ:
            fprintf(listing, "Special symbol: ==\n");
            break;
        case NEQ:
            fprintf(listing, "Special symbol: !=\n");
            break;
        case LPAREN:
            fprintf(listing, "Special symbol: (\n");
            break;
        case RPAREN:
            fprintf(listing, "Special symbol: )\n");
            break;
        case LBRACKET:
            fprintf(listing, "Special symbol: [\n");
            break;
        case RBRACKET:
            fprintf(listing, "Special symbol: ]\n");
            break;
        case LKEY:
            fprintf(listing, "Special symbol: {\n");
            break;
        case RKEY:
            fprintf(listing, "Special symbol: }\n");
            break;
        case SEMI:
            fprintf(listing, "Special symbol: ;\n");
            break;
        case COMMA:
            fprintf(listing, "Special symbol: ,\n");
            break;
        case PLUS:
            fprintf(listing, "Special symbol: +\n");
            break;
        case MINUS:
            fprintf(listing, "Special symbol: -\n");
            break;
        case TIMES:
            fprintf(listing, "Special symbol: *\n");
            break;
        case OVER:
            fprintf(listing, "Special symbol: /\n");
            break;
        case ENDFILE:
            fprintf(listing,"End of file (EOF)\n");
            break;
        case NUM:
            fprintf(listing, "Number: %s\n", tokenString);
            break;
        case ID:
            fprintf(listing, "Identifier: %s\n", tokenString);
            break;
        case ERROR:
            fprintf(listing, "Error: %s\n", tokenString);
            break;
        default: /* should never happen */
            fprintf(listing,"Unknown token: %d\n", token);
    }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind){
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else{
        for(i = 0; i < MAXCHILDREN; ++i)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
        t->scope = "global";
    }
    return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind){
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else{
        for(i = 0; i < MAXCHILDREN; ++i)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
        t->type = Void;
        t->scope = "global";
    }
    return t;
}

/* Function countParamArg counts how many parameters/arguments
 * exist in the function declaration/call
 */
int countParamArg(TreeNode * t){
    int count = 0;
    while(t != NULL)
        t = t->sibling, ++count;
    return count;
}

/* Function getParamArgName gets parameter's/argument's name
 * of a function declaration/call
 */
char * getParamArgName(TreeNode * t, int index){
    int i = 0;
    while(t != NULL && i < index)
        t = t->sibling, ++i;
    return copyString(t->child[0]->attr.name);
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s){
    int n;
    char * t;
    if(s == NULL)
        return NULL;
    n = strlen(s)+1;
    t = (char *) malloc(n*sizeof(char));
    if(t == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else
        strcpy(t, s);
    return t;
}

/* Function joinNameScope joins name and scope to
 * produce new scope for all children nodes of a function
 */
char * joinNameScope(char * name, char * sep, char * scope){
    char * newScope;
    int length = strlen(name)+strlen(sep)+strlen(scope)+1;
    newScope = (char *) malloc(length*sizeof(char));
    if(newScope == NULL)
        fprintf(listing, "Out of memory error at line %d\n", lineno);
    else{
        strcpy(newScope, name);
        strcat(newScope, sep);
        strcat(newScope, scope);
    }
    return newScope;
}

/* Function setScope defines scope for all children
 * nodes of a function
 */
void setScope(TreeNode * t, char * scope){
    while(t != NULL){
        t->scope = copyString(scope);
        int i;
        if(t->nodekind == StmtK && t->kind.stmt == FuncK){
            char * newScope = joinNameScope(t->attr.name, "/", scope);
            for(i = 0; i < MAXCHILDREN; ++i)
                setScope(t->child[i], newScope);
        }
        else{
            for(i = 0; i < MAXCHILDREN; ++i)
                setScope(t->child[i], scope);
        }
        t = t->sibling;
    }
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=4
#define UNINDENT indentno-=4

/* printSpaces indents by printing spaces */
static void printSpaces(){
    int i;
    for(i = 0; i < indentno; ++i)
        fprintf(listing, " ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree(TreeNode * tree){
    int i;
    INDENT;
    while(tree != NULL){
        printSpaces();
        if(tree->nodekind == StmtK){
            switch(tree->kind.stmt){
                case IfK:
                    if(tree->child[2] != NULL)
                        fprintf(listing, "If-Else:\n");
                    else
                        fprintf(listing, "If:\n");
                    break;
                case WhileK:
                    fprintf(listing, "While:\n");
                    break;
                case AssignK:
                    fprintf(listing, "Assign to:\n");
                    break;
                case ReturnK:
                    if(tree->child[0] != NULL)
                        fprintf(listing, "Return:\n");
                    else
                        fprintf(listing, "Return\n");
                    break;
                case VarK:
                    fprintf(listing, "Variable declaration: %s\n", tree->attr.name);
                    break;
                case VecK:
                    fprintf(listing, "Vector declaration: %s[%d]\n", tree->attr.name, tree->attr.value);
                    break;
                case FuncK:
                    if(tree->child[0] != NULL){
                        int k = countParamArg(tree->child[0]);
                        fprintf(listing, "Function declaration: %s(%d parameter%s)\n",
                                tree->attr.name, k, ((k>1) ? "s" : ""));
                    }
                    else
                        fprintf(listing, "Function declaration: %s(void)\n", tree->attr.name);
                    break;
                case FuncVarK:
                    fprintf(listing, "Variable: %s\n", tree->attr.name);
                    break;
                case FuncVecK:
                    fprintf(listing, "Vector: %s[]\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown StmtNode kind\n");
                    break;
            }
        }
        else if(tree->nodekind == ExpK){
            switch(tree->kind.exp){
                case TypeK:
                    if(tree->type == Integer)
                        fprintf(listing, "Type: Integer\n");
                    else if(tree->type == Void)
                        fprintf(listing, "Type: Void\n");
                    break;
                case RelOpK:
                    fprintf(listing, "Relational operator: %s\n", tree->attr.name);
                    break;
                case ArithOpK:
                    fprintf(listing, "Arithmetic operator: %s\n", tree->attr.name);
                    break;
                case ConstK:
                    fprintf(listing, "Constant: %d\n", tree->attr.value);
                    break;
                case IdK:
                    fprintf(listing, "Identifier: %s\n", tree->attr.name);
                    break;
                case VecIndexK:
                    fprintf(listing, "Vector index: %s[]\n", tree->attr.name);
                    break;
                case CallK:
                    if(tree->child[0] != NULL){
                        int k = countParamArg(tree->child[0]);
                        fprintf(listing, "Function call: %s(%d argument%s)\n",
                                tree->attr.name, k, ((k>1) ? "s" : ""));
                    }
                    else
                        fprintf(listing, "Function call: %s()\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing, "Unknown ExpNode kind\n");
                    break;
            }
        }
        else
            fprintf(listing, "Unknown node kind\n");
        for(i = 0; i < MAXCHILDREN; ++i)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}
