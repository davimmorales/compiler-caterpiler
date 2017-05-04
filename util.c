/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the C- compiler                              */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure customPrint customizes print
 * of text in bold to the listing file
 */
void customPrint(const char* string, int bold){
    if(bold == TRUE)
        printf( BOLD "%s" RESET, string);
    else
        printf( "%s", string);
}

/* Procedure printToken prints a token
 * and its lexeme to the listing file
 */
void printToken(TokenType token, const char* tokenString){
    switch(token){
        case IF:
            printf( "Keyword: if\n");
            break;
        case ELSE:
            printf( "Keyword: else\n");
            break;
        case WHILE:
            printf( "Keyword: while\n");
            break;
        case INT:
            printf( "Keyword: int\n");
            break;
        case VOID:
            printf( "Keyword: void\n");
            break;
        case RETURN:
            printf( "Keyword: return\n");
            break;
        case ASSIGN:
            printf( "Special symbol: =\n");
            break;
        case LT:
            printf( "Special symbol: <\n");
            break;
        case LET:
            printf( "Special symbol: <=\n");
            break;
        case HT:
            printf( "Special symbol: >\n");
            break;
        case HET:
            printf( "Special symbol: >=\n");
            break;
        case EQ:
            printf( "Special symbol: ==\n");
            break;
        case NEQ:
            printf( "Special symbol: !=\n");
            break;
        case LPAREN:
            printf( "Special symbol: (\n");
            break;
        case RPAREN:
            printf( "Special symbol: )\n");
            break;
        case LBRACK:
            printf( "Special symbol: [\n");
            break;
        case RBRACK:
            printf( "Special symbol: ]\n");
            break;
        case LCAPSULE:
            printf( "Special symbol: {\n");
            break;
        case RCAPSULE:
            printf( "Special symbol: }\n");
            break;
        case SEMI:
            printf( "Special symbol: ;\n");
            break;
        case COMMA:
            printf( "Special symbol: ,\n");
            break;
        case PLUS:
            printf( "Special symbol: +\n");
            break;
        case MINUS:
            printf( "Special symbol: -\n");
            break;
        case TIMES:
            printf( "Special symbol: *\n");
            break;
        case OVER:
            printf( "Special symbol: /\n");
            break;
        case ENDFILE:
            printf("End of file (EOF)\n");
            break;
        case NUM:
            printf( "Number: %s\n", tokenString);
            break;
        case ID:
            printf( "Identifier: %s\n", tokenString);
            break;
        case ERROR:
            printf( "Error: %s\n", tokenString);
            break;
        default: /* should never happen */
            printf("Unknown token: %d\n", token);
    }
}

// TreeNode * newTypeNode(TypeKind kind){
//   TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
//   int i;
//   if(t==NULL)
//     printf("ERROR: out of memory");
//   else{
//     for (i = 0; i < MAXCHILDREN; i++) {
//       t->child[i] = NULL;
//     }
//     t->sibling = NULL;
//     t->nodekind = Type;
//     t->linenumber = linenumber;
//     t->call_stmt = 0;
//     t->kind->typ = kind;
//   }
//   return t;
// }

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind){
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL)
        printf( "Out of memory error at line %d\n", linenumber);
    else{
        for(i = 0; i < MAXCHILDREN; ++i)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->linenumber = linenumber;
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
        printf( "Out of memory error at line %d\n", linenumber);
    else{
        for(i = 0; i < MAXCHILDREN; ++i)
            t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->linenumber = linenumber;
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
        printf( "Out of memory error at line %d\n", linenumber);
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
        printf( "Out of memory error at line %d\n", linenumber);
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
        printf( " ");
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
                        printf( "If-Else:\n");
                    else
                        printf( "If:\n");
                    break;
                case WhileK:
                    printf( "While:\n");
                    break;
                case AssignK:
                    printf( "Assign to:\n");
                    break;
                case ReturnK:
                    if(tree->child[0] != NULL)
                        printf( "Return:\n");
                    else
                        printf( "Return\n");
                    break;
                case VarK:
                    printf( "Variable declaration: %s\n", tree->attr.name);
                    break;
                case VecK:
                    printf( "Vector declaration: %s[%d]\n", tree->attr.name, tree->attr.value);
                    break;
                case FuncK:
                    if(tree->child[0] != NULL){
                        int k = countParamArg(tree->child[0]);
                        printf( "Function declaration: %s(%d parameter%s)\n",
                                tree->attr.name, k, ((k>1) ? "s" : ""));
                    }
                    else
                        printf( "Function declaration: %s(void)\n", tree->attr.name);
                    break;
                case FuncVarK:
                    printf( "Variable: %s\n", tree->attr.name);
                    break;
                case FuncVecK:
                    printf( "Vector: %s[]\n", tree->attr.name);
                    break;
                default:
                    printf( "Unknown StmtNode kind\n");
                    break;
            }
        }
        else if(tree->nodekind == ExpK){
            switch(tree->kind.exp){
                case TypeK:
                    if(tree->type == Integer)
                        printf( "Type: Integer\n");
                    else if(tree->type == Void)
                        printf( "Type: Void\n");
                    break;
                case RelOpK:
                    printf( "Relational operator: %s\n", tree->attr.name);
                    break;
                case ArithOpK:
                    printf( "Arithmetic operator: %s\n", tree->attr.name);
                    break;
                case ConstK:
                    printf( "Constant: %d\n", tree->attr.value);
                    break;
                case IdK:
                    printf( "Identifier: %s\n", tree->attr.name);
                    break;
                case VecIndexK:
                    printf( "Vector index: %s[]\n", tree->attr.name);
                    break;
                case CallK:
                    if(tree->child[0] != NULL){
                        int k = countParamArg(tree->child[0]);
                        printf( "Function call: %s(%d argument%s)\n",
                                tree->attr.name, k, ((k>1) ? "s" : ""));
                    }
                    else
                        printf( "Function call: %s()\n", tree->attr.name);
                    break;
                default:
                    printf( "Unknown ExpNode kind\n");
                    break;
            }
        }
        else
            printf( "Unknown node kind\n");
        for(i = 0; i < MAXCHILDREN; ++i)
            printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}
