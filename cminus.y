%{
  /****************************************************/
  /* File: cminus.y                                   */
  /* Syntax TreeNode                                  */
  /* Practical Compilers Work                         */
  /* Davi Morales and Mateus Franco                   */
  /****************************************************/

  #define YYPARSER    /* distinguishes Yacc output from other code files */

//GLC para gerar parser para C-

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
/*#include "cminus.tab.h"*/




/*#define YYDEBUG 0*/

#define YYSTYPE TreeNode *
static char * saved_id_name;
static char * saved_fun_name = "Global";
static int saved_line_number;
static TreeNode * savedTree;    /* stores syntax tree for later return */
static int yylex(void);

extern char* yytext;
extern int yylineno;
FILE *arq;

void yyerror(char*);
%}

%start programa
%token INT
%token FLOAT
%token IF
%token ELSE
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
%token NUM	    326
%token ID		    328
%token NEWLINE  329
%token ERROR    331

%%

programa	:	/* Entrada Vazia */
					| declaration-list
          {
            /*$$ = allocateNode("programa");
            addChild($$,$1);*/
            savedTree = $1;
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
                                    saved_fun_name = "Global";
                                }
                        ;
id                      :   ID
                                {
                                    $$ = newExpNode(IdK);
                                    $$->attr.name = copyString(tokenString);
                                    saved_id_name = $$->attr.name;
                                    $$->scope = saved_fun_name;
                                    $$->linenumber = linenumber;
                                }
                        ;

function_id             : {
                            saved_fun_name = saved_id_name;
                          }

variable_declaration    :   type_specifier variable SEMI
                                {
                                    $$ = newDecNode(VarK);
                                    $$->type = $1->type;
                                    $$->child[0] = $2;
                                    $$->attr.name = $2->attr.name;
                                    $$->linenumber = $2->linenumber;
                                    $$->scope = saved_fun_name;
                                }
                        ;

type_specifier          : INT
                        {
                          $$ = newTypeNode(TypeK);
                          $$->type = Integer;
                        }
                        | VOID
                        {
                          $$ = newTypeNode(TypeK);
                          $$->type = Void;
                        }
                        ;

function_declaration    :   type_specifier id  function_id LPAREN parameters RPAREN compound_declaration
                                {
                                    $$ = newDecNode(FuncDecK);
                                    $$->attr.name = saved_fun_name;
                                    $$->type = $1->type;
                                    $$->child[0] = $2;
                                    $2->child[0] = $5;
                                    $2->child[1] = $7;
                                    $$->linenumber = $2->linenumber;
                                    /*setScope($2->child[0], $2->attr.name);
                                    setScope($2->child[1], $2->attr.name);*/
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
parameter               :   type_specifier id
                                {
                                    $$ = newDecNode(ParamK);
                                    $$->type = $1->type;
                                    $$->attr.name = $2->attr.name;
                                    $$->child[0] = $2;
                                    $$->scope = $2->scope;
                                    $$->linenumber = $2->linenumber;
                                }
                        |   type_specifier id LBRACK RBRACK
                                {
                                    $$ = newDecNode(ParamK);
                                    $$->type = $1->type;
                                    $$->attr.name = $2->attr.name;
                                    $$->child[0] = $2;
                                    $$->call_stmt = 13;
                                    $$->scope = $2->scope;
                                    $$->linenumber = $2->linenumber;
                                }
                        ;
compound_declaration    :   LCAPSULE local_declarations list_statement RCAPSULE
                                {
                                  $$ = newDecNode(CompK);
                                  $$->child[0] = $2;
                                  $$->child[1] = $3;
                                }
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
                        |   {
                          $$ = NULL;
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
                                |   {
                                  $$ = NULL;
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
                                {$$ = NULL;}
                        ;
selection_declaration   :   IF LPAREN expression RPAREN statement
                                {
                                  /*ERRORS MAY COME FROM HERE*/
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
                                    $$->child[0] = NULL;
                                }
                        |   RETURN expression SEMI
                                {
                                    $$ = newStmtNode(ReturnK);
                                    $$->child[0] = $2;
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
                                }
                        |   id LBRACK expression RBRACK
                                {
                                    /*$$ = $1;
                                    $$->kind.exp = VecIndexK;*/
                                    $$->child[0] = $3;
                                    /*$$->type = Integer;*/
                                }
                        ;

variable_b              :id
                                {
                                    $$ = $1;
                                }

simple_expression       :   plus_minus_expression relational_operator plus_minus_expression
                                {
                                  $$ = newExpNode(OpK);
                                  $$->child[0] = $1;
                                  $$->child[1] = $3;
                                  $$->attr.oprtr = $2->attr.oprtr;
                                }
                        |   plus_minus_expression
                                {
                                    $$ = $1;
                                }
                        ;
relational_operator     :   EQ
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = EQ;
                                }
                        |   NEQ
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = NEQ;
                                }
                        |   LT
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = LT;
                                }
                        |   LET
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = LET;
                                }
                        |   HT
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = HT;
                                }
                        |   HET
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = HET;
                                }
                        ;
plus_minus_expression   :   plus_minus_expression plus_minus term
                                {
                                    $$ = newExpNode(OpK);
                                    $$->child[0] = $1;
                                    $$->child[1] = $3;
                                    $$->attr.oprtr = $2->attr.oprtr;
                                }
                        |   term
                                {
                                    $$ = $1;
                                }
                        ;
plus_minus              :   PLUS
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = PLUS;
                                }
                        |   MINUS
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = MINUS;
                                }
                        ;
term                    :   term times_over factor
                                {
                                    $$ = newExpNode(OpK);
                                    $$->child[0] = $1;
                                    $$->child[1] = $3;
                                    $$->attr.oprtr = $2->attr.oprtr;
                                }
                        |   factor
                                {
                                    $$ = $1;
                                }
                        ;

times_over              :   TIMES
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = TIMES;
                                }
                        |   OVER
                                {
                                    $$ = newTypeNode(TypeK);
                                    $$->attr.oprtr = OVER;
                                }
                        ;
factor                  :   LPAREN expression RPAREN
                                {
                                    $$ = $2;
                                }
                        |   variable
                                {
                                    $$ = $1;
                                    $1->call_stmt = 1;
                                }
                        |   function_call
                                {
                                    $$ = $1;
                                }
                        |   NUM
                                {
                                    $$ = newExpNode(ConstK);
                                    $$->type = Integer;
                                    $$->attr.value = atoi(tokenString);
                                }
                        ;
function_call           :   variable_b LPAREN arguments RPAREN
                                {
                                    $$ = newStmtNode(CallK);
                                    $$->attr.name = $1->attr.name;
                                    $$->child[0] = $3;
                                }
                        ;

arguments               : list_arguments
                        {
                          $$ = $1;
                        }
                        |
                        {
                          $$ = NULL;
                        }

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
%%

/*TreeNode * allocateToken(char const *token)
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
}*/

/*TreeNode * allocateNode(char const *node)
{

  if(line_flag==0){
    reference_line = yylineno;
    line_flag = 1;
  }

	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->lineno = yylineno - reference_line;
  /*newNode->name = strcpy(newNode->name, yylex());*/

/*	newNode->str = (char*) calloc(sizeof(char),20);
	strcpy(newNode->str, node);

	newNode->child = NULL;
	newNode->sibling = NULL;
  /*printf("alocou no str->%s\n", newNode->str);*/
	/*return newNode;
}*/

/*TreeNode* addSibling(TreeNode* first, TreeNode* newSibling){
	if(first->sibling == NULL){first->sibling = newSibling;}
	else{first->sibling = addSibling(first->sibling, newSibling);}
	return first;
}*/

/*TreeNode* addChild(TreeNode* node, TreeNode* childNode){
	if(node->child!=NULL){node->child = addSibling(node->child, childNode);}
	else{node->child = childNode;}
	return node;
}*/

/*TreeNode* freeTree(TreeNode * tree){
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
}*/

/* printSpaces indents by printing spaces */
/*static void printSpaces(void)
{
	int i;
  	for (i=0;i<indentNo;i++)
	{
		//fprintf(arq, "	");
		printf("_");
	}
}*/


/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
/*void effPrintTree(TreeNode * tree)
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
}*/

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
	/*cout << s << ": " << yytext << endl << "At line: " << yylineno <<  endl;*/
  printf("Syntax error at line %d\n", yylineno);
  printToken(yychar, tokenString);

  /*strExp = (char*) calloc(sizeof(char),40);*/
}

static int yylex(void){
    return getToken();
}

TreeNode * parse(void){
    yyparse();
    return savedTree;
}
