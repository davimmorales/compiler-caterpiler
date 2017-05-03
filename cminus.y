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
            $$ = allocateNode("programa");
            addChild($$,$1);
            tree = $$;
          }
					;

declaration-list	: declaration-list declaration
                  {$$ = allocateNode("declaration-list");
                   addChild($$,$1);
                   addChild($$,$2);}
									| declaration
                  {$$ = allocateNode("declaration-list");
                   addChild($$,$1);}
									;

declaration		: var-declaration
              {$$ = allocateNode("declaration");
               addChild($$,$1);}
              | fun-declaration
              {$$ = allocateNode("declaration");
               addChild($$,$1);}
							;

var-declaration	: type-specifier var-list SEMI
                {$$ = allocateNode("var-declaration");
                 addChild($$,$1);
                 addChild($$,$2);
                 $3 = allocateNode("SEMI");
                 addChild($$,$3);}
								;


var-list: var-list COMMA variable
           {$$ = allocateNode("var-list");
            addChild($$,$1);
            $2 = allocateNode("COMMA");
            addChild($$,$2);
            addChild($$,$3);}
           | variable
           {$$ = allocateNode("var-list");
            addChild($$,$1);}
           ;

variable: ID
          {$$ = allocateNode("variable");
           $1 = allocateToken("ID");
           addChild($$,$1);}
          | ID LBRACK NUMI RBRACK
          {$$ = allocateNode("variable");
           $1 = allocateToken("ID");
           $2 = allocateNode("LBRACK");
           $3 = allocateToken("NUMI");
           $4 = allocateNode("RBRACK");
           addChild($$,$1);
           addChild($$,$2);
           addChild($$,$3);
           addChild($$,$4);}
          ;


type-specifier	: INT
                {$$ = allocateNode("type-specifier");
                 $1 = allocateNode("INT");
                 addChild($$,$1);}
								| FLOAT
                {$$ = allocateNode("type-specifier");
                 $1 = allocateNode("FLOAT");
                 addChild($$,$1);}
								| VOID
                {$$ = allocateNode("type-specifier");
                 $1 = allocateNode("VOID");
                 addChild($$,$1);}
								;

fun-declaration : type-specifier ID LPAREN params RPAREN compound-stmt
                {$$ = allocateNode("fun-declaration");
                 addChild($$,$1);
                 $2 = allocateToken("ID");
                 $3 = allocateNode("LPAREN");
                 addChild($$,$2);
                 addChild($$,$3);
                 addChild($$,$4);
                 $5 = allocateNode("RPAREN");
                 addChild($$,$5);
                 addChild($$,$6);}
                | type-specifier ID LPAREN RPAREN compound-stmt
                {$$ = allocateNode("fun-declaration");
                 addChild($$,$1);
                 $2 = allocateToken("ID");
                 $3 = allocateNode("LPAREN");
                 $4 = allocateNode("RPAREN");
                 addChild($$,$2);
                 addChild($$,$3);
                 addChild($$,$4);
                 addChild($$,$5);}
                ;

params  : param-list
        {$$ = allocateNode("params");
         addChild($$,$1);}
        | VOID
        {$$ = allocateNode("params");
         $1 = allocateNode("VOID");
         addChild($$,$1);}
        ;

param-list  : param-list COMMA param
            {$$ = allocateNode("param-list");
             addChild($$,$1);
             $2 = allocateNode("COMMA");
             addChild($$,$2);
             addChild($$,$3);}
            | param
            {$$ = allocateNode("param-list");
             addChild($$,$1);}
            ;

param       : type-specifier ID
            {$$ = allocateNode("param");
             addChild($$,$1);
             $2 = allocateToken("ID");
             addChild($$,$2);}
            | type-specifier ID LBRACK RBRACK
            {$$ = allocateNode("param");
             addChild($$,$1);
             $2 = allocateToken("ID");
             $3 = allocateNode("LBRACK");
             $4 = allocateNode("RBRACK");
             addChild($$,$2);
             addChild($$,$3);
             addChild($$,$4);}
            ;

compound-stmt : LCAPSULE local-declarations statement-list RCAPSULE
              {$$ = allocateNode("compound-stmt");
               $1 = allocateNode("LCAPSULE");
               addChild($$,$1);
               addChild($$,$2);
               addChild($$,$3);
               $4 = allocateNode("RCAPSULE");
               addChild($$,$4);}
              ;

local-declarations  : local-declarations var-declaration
                      {
                        $$ = allocateNode("local-declarations");
                        addChild($$,$1);
                        addChild($$,$2);
                      }
                    | /* empty */
                    {$$ = allocateNode("local-declarations");}
                    ;

statement-list      : statement-list statement
                      {
                        $$ = allocateNode("statement-list");
                        addChild($$,$1);
                        addChild($$,$2);
                      }
                    | /* empty */
                    {$$ = allocateNode("statement-list");}
                    ;

statement           : expression-stmt
                      {
                        $$ = allocateNode("statement");
                        addChild($$,$1);
                      }
                    | compound-stmt
                      {
                        $$ = allocateNode("statement");
                        addChild($$,$1);
                      }
                    | selection-stmt
                      {
                        $$ = allocateNode("statement");
                        addChild($$,$1);
                      }
                    | iteration-stmt
                      {
                        $$ = allocateNode("statement");
                        addChild($$,$1);
                      }
                    | return-stmt
                      {
                        $$ = allocateNode("statement");
                        addChild($$,$1);
                      }
                    ;

expression-stmt     : expression SEMI
                      {
                        $$ = allocateNode("expression-stmt");
                        addChild($$,$1);
                        $2 = allocateNode("SEMI");
                        addChild($$,$2);
                      }
                    | SEMI
                      {
                        $$ = allocateNode("expression-stmt");
                        $1 = allocateNode("SEMI");
                        addChild($$,$1);
                      }
                    ;

selection-stmt      : IF LPAREN comparative-expression RPAREN statement
                      {
                        $$ = allocateNode("selection-stmt");
                        $1 = allocateNode("IF");
                        addChild($$,$1);
                        $2 = allocateNode("LPAREN");
                        addChild($$,$2);
                        addChild($$,$3);
                        $4 = allocateNode("RPAREN");
                        addChild($$,$4);
                        addChild($$,$5);
                      }
                    | IF LPAREN comparative-expression RPAREN statement ELSE statement
                      {
                        $$ = allocateNode("selection-stmt");
                        $1 = allocateNode("IF");
                        addChild($$,$1);
                        $2 = allocateNode("LPAREN");
                        addChild($$,$2);
                        addChild($$,$3);
                        $4 = allocateNode("RPAREN");
                        addChild($$,$4);
                        addChild($$,$5);
                        $6 = allocateNode("ELSE");
                        addChild($$,$6);
                        addChild($$,$7);
                      }
                    ;

iteration-stmt      : WHILE LPAREN comparative-expression RPAREN statement
                      {
                        $$ = allocateNode("iteration-stmt");
                        $1 = allocateNode("WHILE");
                        addChild($$,$1);
                        $2 = allocateNode("LPAREN");
                        addChild($$,$2);
                        addChild($$,$3);
                        $4 = allocateNode("RPAREN");
                        addChild($$,$4);
                        addChild($$,$5);
                      }
                    ;

return-stmt         : RETURN SEMI
                      {
                        $$ = allocateNode("return-stmt");
                        $1 = allocateNode("RETURN");
                        addChild($$,$1);
                        $2 = allocateNode("SEMI");
                        addChild($$,$2);
                      }

                    | RETURN expression SEMI
                      {
                        $$ = allocateNode("return-stmt");
                        $1 = allocateNode("RETURN");
                        addChild($$,$1);
                        addChild($$,$2);
                        $3 = allocateNode("SEMI");
                        addChild($$,$3);
                      }
                    ;

expression          : var ASSIGN expression
                      {
                        $$ = allocateNode("expression");
                        addChild($$,$1);
                        $1 = allocateNode("ASSIGN");
                        addChild($$,$2);
                        addChild($$,$3);
                      }
                    | simple-expression
                      {
                        $$ = allocateNode("expression");
                        addChild($$,$1);
                      }
                    ;

var                 : ID
                      {
                        $$ = allocateNode("var");
                        $1 = allocateToken("ID");
                        addChild($$,$1);
                      }
                    | ID LBRACK expression RBRACK
                      {
                        $$ = allocateNode("var");
                        $1 = allocateToken("ID");
                        addChild($$,$1);
                        $2 = allocateNode("LBRACK");
                        addChild($$,$2);
                        addChild($$,$3);
                        $4 = allocateNode("RBRACK");
                        addChild($$,$4);
                      }
                    ;

simple-expression   : comparative-expression
                      {
                        $$ = allocateNode("simple-expression");
                        addChild($$,$1);
                      }
                    | additive-expression
                      {
                        $$ = allocateNode("simple-expression");
                        addChild($$,$1);
                      }
                    ;

comparative-expression: additive-expression relop additive-expression
                        {
                          $$ = allocateNode("comparative-expression");
                          addChild($$,$1);
                          addChild($$,$2);
                          addChild($$,$3);
                        }
                    ;

relop               : LET
                      {
                        $$ = allocateNode("relop");
                        $1 = allocateNode("LET");
                        addChild($$,$1);
                      }
                    | LT
                      {
                        $$ = allocateNode("relop");
                        $1 = allocateNode("LT");
                        addChild($$,$1);
                      }
                    | HT
                      {
                        $$ = allocateNode("relop");
                        $1 = allocateNode("HT");
                        addChild($$,$1);
                      }
                    | HET
                      {
                        $$ = allocateNode("relop");
                        $1 = allocateNode("HET");
                        addChild($$,$1);
                      }
                    | EQ
                      {
                        $$ = allocateNode("relop");
                        $1 = allocateNode("EQ");
                        addChild($$,$1);
                      }
                    | NEQ
                      {
                        $$ = allocateNode("relop");
                        $1 = allocateNode("NEQ");
                        addChild($$,$1);
                      }
                    ;

additive-expression : additive-expression addop term
                      {
                        $$ = allocateNode("additive-expression");
                        addChild($$,$1);
                        addChild($$,$2);
                        addChild($$,$3);
                      }
                    | addop term
                      {
                        $$ = allocateNode("additive-expression");
                        addChild($$,$1);
                        addChild($$,$2);
                      }
		                | term
                      {
                        $$ = allocateNode("additive-expression");
                        addChild($$,$1);
                      }
                    ;

addop               : PLUS
                      {
                        $$ = allocateNode("addop");
                        $1 = allocateNode("PLUS");
                        addChild($$,$1);
                      }
                    | MINUS
                      {
                        $$ = allocateNode("addop");
                        $1 = allocateNode("MINUS");
                        addChild($$,$1);
                      }
                    ;

term                : term mulop factor
                      {
                        $$ = allocateNode("term");
                        addChild($$,$1);
                        addChild($$,$2);
                        addChild($$,$3);
                      }
                    | factor
                      {
                        $$ = allocateNode("term");
                        addChild($$,$1);
                      }
                    ;

mulop               : TIMES
                      {
                        $$ = allocateNode("mulop");
                        $1 = allocateNode("TIMES");
                        addChild($$,$1);
                      }
                    | OVER
                      {
                        $$ = allocateNode("mulop");
                        $1 = allocateNode("OVER");
                        addChild($$,$1);
                      }
                    ;

factor              : LPAREN expression RPAREN
                      {
                        $$ = allocateNode("factor");
                        $1 = allocateNode("LPAREN");
                        addChild($$,$1);
                        addChild($$,$2);
                        $3 = allocateNode("RPAREN");
                        addChild($$,$3);
                      }
                    | var
                      {
                        $$ = allocateNode("factor");
                        $1 = allocateNode("var");
                        addChild($$,$1);
                      }
                    | call
                      {
                        $$ = allocateNode("factor");
                        $1 = allocateNode("call");
                        addChild($$,$1);
                      }
                    | NUMI
                      {
                        $$ = allocateNode("factor");
                        $1 = allocateToken("NUMI");
                        addChild($$,$1);
                      }
                    | NUMF
                      {
                        $$ = allocateNode("factor");
                        $1 = allocateToken("NUMF");
                        addChild($$,$1);
                      }
                    ;

call                : ID LPAREN args RPAREN
                      {
                        $$ = allocateNode("call");
                        $1 = allocateToken("ID");
                        addChild($$,$1);
                        $2 = allocateNode("LPAREN");
                        addChild($$,$2);
                        addChild($$,$3);
                        $4 = allocateNode("RPAREN");
                        addChild($$,$4);
                      }
                    ;

args                : arg-list
                      {
                        $$ = allocateNode("args");
                        addChild($$,$1);
                      }
                    | /* empty */
                    {
                  		$$ = allocateNode("args");
                  	}
                    ;

arg-list            : arg-list COMMA expression
                      {
                        $$ = allocateNode("arg-list");
                        addChild($$,$1);
                        $2 = allocateNode("COMMA");
                        addChild($$,$2);
                        addChild($$,$3);
                      }
                    | expression
                      {
                        $$ = allocateNode("arg-list");
                        addChild($$,$1);
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
