%{
//GLC para gerar parser para C-

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


#define YYDEBUG 0

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {statementK, expK} node_kind;
typedef enum {ifK, whileK, assignK, returnK, varK, vecK, funcK, funcvarK, funcvecK} statement_kind;
typedef enum {TypeK, RelOpK, ArithOpK, ConstK, IdK, VecIndexK, CallK} expression_kind;

union treeKind{
    statement_kind stmt;
    expression_kind exp;
};

typedef struct treeNode{
  char *str;
  char *name;
  int type;
  int value;
  int lineno;
  node_kind nodekind;
  char * scope;
  union treeKind kind;
  struct treeNode *child;
  struct treeNode *sibling;
}TreeNode;

int line_flag = 0;
int reference_line = 0;

TreeNode * tree;// Declaração da árvore
TreeNode * allocateToken(char const* token);
TreeNode * allocateNode(char const* node);
TreeNode * addChild(TreeNode* node, TreeNode* newChild);
TreeNode * addSibling(TreeNode* first, TreeNode* newSibling);

static int indentNo = 0;

#define YYSTYPE TreeNode *
#define INDENT indentNo+=2
#define UNINDENT indentNo-=2

static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
// char * strExp;
std::string strExp;



using namespace std;

extern "C"
{

  ofstream writeTree;
  int yylex();
  int yyparse();
	void abrirArq();
  void effPrintTree(TreeNode * tree);
  /*void printTree();*/
  int yywrap() {
    return 1;
  }
}


extern char* yytext;
extern int yylineno;
FILE *arq;

void yyerror(char*);
%}

%start programa
%token INT      300
%token FLOAT    301
%token IF       302
%nonassoc ELSE     303
%token RETURN   304
%token VOID     305
%token WHILE    306
%token PLUS     307
%token MINUS    308
%token TIMES    309
%token OVER     310
%token LT 		  311
%token LET 	    312
%token HT 		  313
%token HET 	    314
%token EQ 		  315
%token NEQ		  316
%token ASSIGN   317
%token SEMI 	  318
%token COMMA	  319
%token LPAREN   320
%nonassoc RPAREN	  321
%token LBRACK   322
%token RBRACK   323
%token LCAPSULE 324
%token RCAPSULE 325
%token NUMI	    326
%token NUMF	    327
%token ID		    328
%token NEWLINE  329
%token ERROR    331

%%

programa	:	/* Entrada Vazia */
					| declaration-list
          {
            /*$$ = allocateNode("programa");
            addChild($$,$1);*/
            tree = $1;
          }
					;

declaration-list	: declaration-list declaration
                  { YYSTYPE t = $1;
                    if(t != NULL){
                      while(t->sibling != NULL)
                        t = t->sibling;
                      t->sibling = $2;
                      $$ = $1;
                    }
                    else
                      $$ = $2;
                    }
                    /*$$ = allocateNode("declaration-list");
                   addChild($$,$1);
                   addChild($$,$2);}*/
									| declaration
                  {
                    $$ = $1;
                    /*$$ = allocateNode("declaration-list");*/
                   /*addChild($$,$1);*/
                 }
									;
declaration             :   variable_declaration
                                {
                                    $$ = $1;
                                }
                        |   function_declaration
                                {
                                    $$ = $1;
                                }
                        ;
variable_declaration    :   INT id SEMI
                                {
                                    $$ = newExpNode(TypeK);
                                    $$->type = Integer;
                                    $$->child[0] = $2;
                                    $2->nodekind = StmtK;
                                    $2->kind.stmt = VarK;
                                    $2->type = Integer;
                                }
                        |   INT id LBRACK num RBRACK SEMI
                                {
                                    $$ = newExpNode(TypeK);
                                    $$->type = Integer;
                                    $$->child[0] = $2;
                                    $2->nodekind = StmtK;
                                    $2->kind.stmt = VecK;
                                    $2->attr.value = $4->attr.value;
                                    $2->type = Integer;
                                }
                        ;
function_declaration    :   INT id LPAREN parameters RPAREN compound_declaration
                                {
                                    $$ = newExpNode(TypeK);
                                    $$->type = Integer;
                                    $$->child[0] = $2;
                                    $2->nodekind = StmtK;
                                    $2->kind.stmt = FuncK;
                                    $2->child[0] = $4;
                                    $2->child[1] = $6;
                                    $2->type = Integer;
                                    setScope($2->child[0], $2->attr.name);
                                    setScope($2->child[1], $2->attr.name);
                                }
                        |   VOID id LPAREN parameters RPAREN compound_declaration
                                {
                                    $$ = newExpNode(TypeK);
                                    $$->type = Void;
                                    $$->child[0] = $2;
                                    $2->nodekind = StmtK;
                                    $2->kind.stmt = FuncK;
                                    $2->child[0] = $4;
                                    $2->child[1] = $6;
                                    $2->type = Void;
                                    setScope($2->child[0], $2->attr.name);
                                    setScope($2->child[1], $2->attr.name);
                                }
                        ;
parameters              :   list_parameters
                                {
                                    $$ = $1;
                                }
                        |   VOID
                                {
                                    $$ = NULL;
                                }
                        ;
list_parameters         :   list_parameters COMMA parameter
                                {
                                    YYSTYPE t = $1;
                                    if(t != NULL){
                                        while(t->sibling != NULL)
                                            t = t->sibling;
                                        t->sibling = $3;
                                        $$ = $1;
                                    }
                                    else
                                        $$ = $3;
                                }
                        |   parameter
                                {
                                    $$ = $1;
                                }
                        ;
parameter               :   INT id
                                {
                                    $$ = newExpNode(TypeK);
                                    $$->type = Integer;
                                    $$->child[0] = $2;
                                    $2->nodekind = StmtK;
                                    $2->kind.stmt = FuncVarK;
                                    $2->type = Integer;
                                }
                        |   INT id LBRACK RBRACK
                                {
                                    $$ = newExpNode(TypeK);
                                    $$->type = Integer;
                                    $$->child[0] = $2;
                                    $2->nodekind = StmtK;
                                    $2->kind.stmt = FuncVecK;
                                    $2->type = Integer;
                                }
                        ;
compound_declaration    :   LCAPSULE local_declarations list_statement RCAPSULE
                                {
                                    YYSTYPE t = $2;
                                    if(t != NULL){
                                        while(t->sibling != NULL)
                                            t = t->sibling;
                                        t->sibling = $3;
                                        $$ = $2;
                                    }
                                    else
                                        $$ = $3;
                                }
                        |   LCAPSULE local_declarations RCAPSULE
                                {
                                    $$ = $2;
                                }
                        |   LCAPSULE list_statement RCAPSULE
                                {
                                    $$ = $2;
                                }
                        |   LCAPSULE RCAPSULE
                                {}
                        ;
local_declarations      :   local_declarations variable_declaration
                                {
                                    YYSTYPE t = $1;
                                    if(t != NULL){
                                        while(t->sibling != NULL)
                                            t = t->sibling;
                                        t->sibling = $2;
                                        $$ = $1;
                                    }
                                    else
                                        $$ = $2;
                                }
                        |   variable_declaration
                                {
                                    $$ = $1;
                                }
                        ;
list_statement          :   list_statement statement
                                {
                                    YYSTYPE t = $1;
                                    if(t != NULL){
                                        while(t->sibling != NULL)
                                            t = t->sibling;
                                        t->sibling = $2;
                                        $$ = $1;
                                    }
                                    else
                                        $$ = $2;
                                }
                        |   statement
                                {
                                    $$ = $1;
                                }
                        ;
statement               :   expression_declaration
                                {
                                    $$ = $1;
                                }
                        |   compound_declaration
                                {
                                    $$ = $1;
                                }
                        |   selection_declaration
                                {
                                    $$ = $1;
                                }
                        |   iteration_declaration
                                {
                                    $$ = $1;
                                }
                        |   return_declaration
                                {
                                    $$ = $1;
                                }
                        ;
expression_declaration  :   expression SEMI
                                {
                                    $$ = $1;
                                }
                        |   SEMI
                                {}
                        ;
selection_declaration   :   IF LPAREN expression RPAREN statement
                                {
                                    $$ = newStmtNode(IfK);
                                    $$->child[0] = $3;
                                    $$->child[1] = $5;
                                }
                        |   IF LPAREN expression RPAREN statement ELSE statement
                                {
                                    $$ = newStmtNode(IfK);
                                    $$->child[0] = $3;
                                    $$->child[1] = $5;
                                    $$->child[2] = $7;
                                }
                        ;
iteration_declaration   :   WHILE LPAREN expression RPAREN statement
                                {
                                    $$ = newStmtNode(WhileK);
                                    $$->child[0] = $3;
                                    $$->child[1] = $5;
                                }
                        ;
return_declaration      :   RETURN SEMI
                                {
                                    $$ = newStmtNode(ReturnK);
                                    $$->type = Void;
                                }
                        |   RETURN expression SEMI
                                {
                                    $$ = newStmtNode(ReturnK);
                                    $$->child[0] = $2;
                                    $$->type = $2->type;
                                }
                        ;
expression              :   variable ASSIGN expression
                                {
                                    $$ = newStmtNode(AssignK);
                                    $$->child[0] = $1;
                                    $$->child[1] = $3;
                                }
                        |   simple_expression
                                {
                                    $$ = $1;
                                }
                        ;
variable                :   id
                                {
                                    $$ = $1;
                                    $$->type = Integer;
                                }
                        |   id LBRACK expression RBRACK
                                {
                                    $$ = $1;
                                    $$->kind.exp = VecIndexK;
                                    $$->child[0] = $3;
                                    $$->type = Integer;
                                }
                        ;
simple_expression       :   plus_minus_expression relational_operator plus_minus_expression
                                {
                                    $$ = $2;
                                    $$->child[0] = $1;
                                    $$->child[1] = $3;
                                }
                        |   plus_minus_expression
                                {
                                    $$ = $1;
                                }
                        ;
relational_operator     :   EQ
                                {
                                    $$ = newExpNode(RelOpK);
                                    $$->attr.operator = EQ;
                                    $$->attr.name = "==";
                                    $$->type = Boolean;
                                }
                        |   NEQ
                                {
                                    $$ = newExpNode(RelOpK);
                                    $$->attr.operator = NEQ;
                                    $$->attr.name = "!=";
                                    $$->type = Boolean;
                                }
                        |   LT
                                {
                                    $$ = newExpNode(RelOpK);
                                    $$->attr.operator = LT;
                                    $$->attr.name = "<";
                                    $$->type = Boolean;
                                }
                        |   LET
                                {
                                    $$ = newExpNode(RelOpK);
                                    $$->attr.operator = LET;
                                    $$->attr.name = "<=";
                                    $$->type = Boolean;
                                }
                        |   HT
                                {
                                    $$ = newExpNode(RelOpK);
                                    $$->attr.operator = HT;
                                    $$->attr.name = ">";
                                    $$->type = Boolean;
                                }
                        |   HET
                                {
                                    $$ = newExpNode(RelOpK);
                                    $$->attr.operator = HET;
                                    $$->attr.name = ">=";
                                    $$->type = Boolean;
                                }
                        ;
plus_minus_expression   :   plus_minus_expression plus_minus term
                                {
                                    $$ = $2;
                                    $$->child[0] = $1;
                                    $$->child[1] = $3;
                                }
                        |   term
                                {
                                    $$ = $1;
                                }
                        ;
plus_minus              :   PLUS
                                {
                                    $$ = newExpNode(ArithOpK);
                                    $$->attr.operator = PLUS;
                                    $$->attr.name = "+";
                                    $$->type = Integer;
                                }
                        |   MINUS
                                {
                                    $$ = newExpNode(ArithOpK);
                                    $$->attr.operator = MINUS;
                                    $$->attr.name = "-";
                                    $$->type = Integer;
                                }
                        ;
term                    :   term times_over factor
                                {
                                    $$ = $2;
                                    $$->child[0] = $1;
                                    $$->child[1] = $3;
                                }
                        |   factor
                                {
                                    $$ = $1;
                                }
                        ;
times_over              :   TIMES
                                {
                                    $$ = newExpNode(ArithOpK);
                                    $$->attr.operator = TIMES;
                                    $$->attr.name = "*";
                                    $$->type = Integer;
                                }
                        |   OVER
                                {
                                    $$ = newExpNode(ArithOpK);
                                    $$->attr.operator = OVER;
                                    $$->attr.name = "/";
                                    $$->type = Integer;
                                }
                        ;
factor                  :   LPAREN expression RPAREN
                                {
                                    $$ = $2;
                                }
                        |   variable
                                {
                                    $$ = $1;
                                }
                        |   function_call
                                {
                                    $$ = $1;
                                }
                        |   num
                                {
                                    $$ = $1;
                                }
                        ;
function_call           :   id LPAREN list_arguments RPAREN
                                {
                                    $$ = $1;
                                    $$->child[0] = $3;
                                    $$->kind.exp = CallK;
                                }
                        |   id LPAREN RPAREN
                                {
                                    $$ = $1;
                                    $$->kind.exp = CallK;
                                }
                        ;
list_arguments          :   list_arguments COMMA expression
                                {
                                    YYSTYPE t = $1;
                                    if(t != NULL){
                                        while(t->sibling != NULL)
                                            t = t->sibling;
                                        t->sibling = $3;
                                        $$ = $1;
                                    }
                                    else
                                        $$ = $3;
                                }
                        |   expression
                                {
                                    $$ = $1;
                                }
                        ;
id                      :   ID
                                {
                                    $$ = newExpNode(IdK);
                                    $$->attr.name = copyString(tokenString);
                                }
                        ;
num                     :   NUM
                                {
                                    $$ = newExpNode(ConstK);
                                    $$->attr.value = atoi(tokenString);
                                    $$->type = Integer;
                                }
                        ;

%%


// void reset(char arg[]) //100%
// {
// 	int i, max = strlen(arg);
//
// 	for(i = 0; i < max; i++)
// 		arg[i] = '\0';
// }


TreeNode * allocateToken(char const *token)
{
	//reset(strExp);
	//strncpy(strExp, yytext, sizeof(strExp));
  strExp.erase();
  strExp = yytext;
	TreeNode *branch = allocateNode(token);
	//puts( yytext );
//	sprintf(strExp, "%s", yytext);
	TreeNode *leaf = allocateNode(strExp.c_str());//because it must be a char const*
  // TreeNode *leaf = allocateNode("galeto");
//	addChild(branch, leaf);
	return branch;
}

TreeNode * allocateNode(char const *node)
{

  if(line_flag==0){
    reference_line = yylineno;
    line_flag = 1;
  }

	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->lineno = yylineno - reference_line;
  /*newNode->name = strcpy(newNode->name, yylex());*/

	newNode->str = (char*) calloc(sizeof(char),20);
	strcpy(newNode->str, node);

	newNode->child = NULL;
	newNode->sibling = NULL;
  /*printf("alocou no str->%s\n", newNode->str);*/
	return newNode;
}

TreeNode* addSibling(TreeNode* first, TreeNode* newSibling){
	if(first->sibling == NULL){first->sibling = newSibling;}
	else{first->sibling = addSibling(first->sibling, newSibling);}
	return first;
}

TreeNode* addChild(TreeNode* node, TreeNode* childNode){
	if(node->child!=NULL){node->child = addSibling(node->child, childNode);}
	else{node->child = childNode;}
	return node;
}

TreeNode* freeTree(TreeNode * tree){
	if(tree != NULL)
	{
		if(tree->sibling != NULL){tree->sibling = freeTree(tree->sibling);}

		if(tree->child != NULL){tree->child = freeTree(tree->child);}

		if(tree->child == NULL && tree->sibling == NULL)
		{
			free(tree);
			return NULL;
		}
	}
}

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
	int i;
  	for (i=0;i<indentNo;i++)
	{
		//fprintf(arq, "	");
		printf("_");
	}
}


/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
void effPrintTree(TreeNode * tree)
{
	INDENT;
	while (tree != NULL)
	{
		printSpaces();
		//fprintf(arq, "%s\n",tree->str);
    printf("%s %d\n",tree->str, tree->lineno);

		tree = tree->child;

		while(tree != NULL)
		{
			effPrintTree(tree);
			tree = tree->sibling;
		}
	  	UNINDENT;
	}
}

/*void printTree()
{
  printf("Imprimindo árvore sintática...\n");
	arq = fopen("syntaticTree.xls", "w");
	effPrintTree(tree);
	fclose(arq);
}*/

void yyerror (char* s)  /* Called by yyparse on error */
{
	extern char* yytext;
	cout << s << ": " << yytext << endl << "At line: " << yylineno <<  endl;
  strExp = (char*) calloc(sizeof(char),40);
}

TreeNode * parse(void){
    yyparse();
    return savedTree;
}
