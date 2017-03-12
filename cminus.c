/****************************************************/
/* File: cminus.l                                   */
/* Lex specification for C- and Table Generator     */
/* Trabalho Prático de Compiladores                 */
/* Davi Morales and Mateus Franco                   */
/****************************************************/
/*there was, formerly, an optional minus on numberi and numberf*/
%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cminus.tab.h"
extern YYSTYPE yylval;


void abrirArq();

void printTree();

int lineno = 1;

%}

digit       [0-9]
numberi     {digit}+
numberf	    {digit}+?\.{digit}+|-?{digit}+\.{digit}+?
letter      [a-zA-Z]
identifier  {letter}+{letter}*
newline     \n
whitespace  [ \t\r]+
other	[^0-9a-zA-Z;/=\-"+""*""("")""\n"\[\]\,\{\}\<\>|!=\==\<=\>=]
%option yylineno
%%

"int"		     {printf("INT "); return INT;}
"float"		   {printf("FLOAT "); return FLOAT;}
"if"         {printf("IF "); return IF;}
"else"		   {printf("ELSE "); return ELSE;}
"return"	   {printf("RETURN "); return RETURN;}
"void"		   {printf("VOID ");return VOID;}
"while"		   {printf("WHILE "); return WHILE;}
"+"			     {printf("PLUS "); return PLUS;}
"-"			     {printf("MINUS "); return MINUS;}
"*"			     {printf("TIMES "); return TIMES;}
"/"			     {printf("OVER "); return OVER;}
"<"			     {printf("LT "); return LT;}
"<="         {printf("LET "); return LET;}
">"			     {printf("HT "); return HT;}
">="         {printf("HET "); return HET;}
"=="         {printf("EQ "); return EQ;}
"!="         {printf("NEQ "); return NEQ;}
"="			     {printf("ASSIGN "); return ASSIGN;}
";"			     {printf("SEMI "); return SEMI;}
","			     {printf("COMMA "); return COMMA;}
"("			     {printf("LPAREN "); return LPAREN;}
")"          {printf("RPAREN "); return RPAREN;}
"["			     {printf("LBRACK "); return LBRACK;}
"]"			     {printf("RBRACK "); return RBRACK;}
"{"			     {printf("LCAPSULE "); return LCAPSULE;}
"}"			     {printf("RCAPSULE "); return RCAPSULE;}
"/*"            { 	char c, d;
                        c = input();
                        do
                        { 	if (c == EOF) break;
                                d = input();
                                if (c == '\n')
                                	 lineno++;
                                if (c == '*' && d == '/') break;
                                c = d;
                  } while (1);
                }
{newline}       { lineno++; printf("\t%d\n", lineno);}
{whitespace}    ;
{numberi}       {printf("NUMI "); return NUMI;}
{numberf}		    {printf("NUMF "); return NUMF;}
{identifier}    {printf("ID ");return ID;}
<<EOF>>         return(0);
{other}		{ printf("Lexical Error at line %d\n", lineno);}

%%

typedef struct TipoID{
    char nomeID[20];
    char tipoID[20];
    char tipoData[10];
    char escopo[30];
    int linhas[50];
    int top;
    struct TipoID *prox;
}TipoID;

typedef struct{
    TipoID *start;
}TipoLista;

void inicializaLista(TipoLista *lista){
    lista->start = NULL;
}

int contaChar(const char *str)
{
    int i = 0;
    for(;str[i] != 0; ++i);
    return i;
}

int string2int(const char *num)
{
  int  i, len, a;
  int result=0;
  len = contaChar(num);
  for(i=0; i<len; i++){
    result = result * 10 + ( num[i] - '0' );
  }
  return result;
}

void insere(TipoLista *lista, char scope[], char nameID[], char typeID[], char typeData[], int nline, int index)
{


    // Alocação do nó que será indexado
    TipoID *novoNo = malloc(sizeof(TipoID));
    // Inicialização do vetor de linhas
    int i;
    for(i=0;i<50;i++) {
      novoNo->linhas[i] = 0;
    }
    // Atribuição da linha na posição inicial

    if(strcmp(nameID,"input") == 0 || strcmp(nameID,"output") == 0) {
      novoNo->linhas[0] = 0;
      novoNo->top = 0;
    } else {
      novoNo->linhas[0] = nline;
      novoNo->top = 1; // proxima posição de inserir numero da linha
    }

    // Inicialização dos demais campos do nó com os parâmetros de entrada
    if(!strcmp(typeID,"func")) {
      strcpy(novoNo->escopo, "none");
      /*strcpy(novoNo->tipoData, "none");*/
    } else {
      strcpy(novoNo->escopo, scope);
      /*strcpy(novoNo->tipoData, typeData);*/
    }
    strcpy(novoNo->tipoData, typeData);
    strcpy(novoNo->nomeID, nameID);
    strcpy(novoNo->tipoID, typeID);
    /*printf("%s\n", novoNo->escopo);*/
    TipoID *p = lista[index].start;

    if(p == NULL) { // Lista vazia
        lista[index].start = novoNo;
    } else {  // Lista não vazia. Insere no final
        while(p->prox!=NULL){
            p = p->prox;
        }
        p->prox = novoNo;
    }
}

int checkExistence(TipoLista *Lista, char s[], int noline, int index, char scope[], int flag){
    int i;
    TipoID *c = Lista[index].start;
    if(flag)
      return 0;
    while(c!=NULL){
        if(!strcmp(s,c->nomeID)){
          if(!strcmp(scope,c->escopo)||!strcmp(c->tipoID, "func")||!strcmp(c->escopo, "global")){
          for(i=0;i<c->top;i++){
            if(c->linhas[i]==noline)
              return 1;
          }
          c->linhas[c->top] = noline;
          c->top++;
          return 1;
        }
      }
        c = c->prox;
    }
    return 0;
}

void printWTable(TipoLista *lista, int index) {
  int i;
  TipoID *p = lista[index].start;
  while(p!=NULL){
      i = 0;
      if(p->linhas[0] != 0) {
        printf("%6s    %6s    %6s    %6s        ", p->nomeID, p->tipoID, p->tipoData, p->escopo);
        while(p->linhas[i]!=0){
          printf("%d", p->linhas[i]);
          if(i<p->top-1)
            printf(",");
          i++;
        }
        printf("\n");
      }
        p = p->prox;
  }
}

void abrirArq()
{
  yyin = fopen("entrada.txt", "r");
}

/*Name: Semantic Analysis functions*/
/*Role: Checks Existance of void variables*/
int checkVoid(TipoLista *list, int index){
TipoID *p = list[index].start;
while(p!=NULL){
    if(p->linhas[0] != 0) {
      //p->nomeID, p->tipoID, p->tipoData, p->escopo);
      if (!strcmp(p->tipoID, "var")&&!strcmp(p->tipoData,"void")) {
        return p->linhas[0];
      }
      printf("\n");
    }
      p = p->prox;
    }
    return 0;
}

int semanticAnalysis(TipoLista *hashList){
  int i;
  for(i = 0;i<211;i++){
      if(&hashList[i]!=NULL){
        // Check Existance of void variables
        int checkVoidFlag;
        checkVoidFlag = checkVoid(hashList, i);
        if (checkVoidFlag) {
          printf("Semantic error at line %d: Variable declared as void\n ", checkVoidFlag);
      }
    }
  }
  return 0;
}

int main() {
/*
extern int yydebug;
yydebug = 1;
*/
FILE *f_in;
FILE *f_out;
int i;
int w;
int flag;
int buf[100000];
char escopo[30];  //  escopo da função
char nomeID[20];  //  nome do ID
char tipoID[3];   //  tipo nenhum <var, fun, vet>
char tipoData[10]; //  tipo de dados <int, float, void>
char nomeIDAnt[20];
int line = 1;
int hash = 0;
// Alocando o vetor estático e inicializando ponteiros com NULL
TipoLista vetor[211]; //lista de listas

for(i = 0; i < 211; i++) {
  vetor[i].start = NULL;
}

for (i=0;i<=100000;i++) buf[i] = 0;

abrirArq();

int token;
int cont = 0;             //  contador de chaves inicia com zero no IDS.escopo global
strcpy(nomeID, "nome");
strcpy(escopo, "global"); //  inicia laço com escopo global
strcpy(tipoData, "void"); //  tipo void por default
strcpy(tipoID, "non");    //  tipo nenhum <var, fun, vet>
flag = 0;
w = 0;


// Inserindo funções predefinidas int input() e void output()
insere(vetor, escopo, "input", "func", "int", -1, 39);
insere(vetor, escopo, "output", "func", "void", -1, 34);

while ((token=yylex()) != '\0') {
  buf[w] = token;
  printf("%d\t", token);
  w++;
    switch(token) {

      case VOID:
        strcpy(tipoData, "void");
    //    puts(tipoData);
      break;

      case FLOAT:
        strcpy(tipoData, "float");
        flag = 1;
  //      puts(tipoData);
      break;

      case INT:
        strcpy(tipoData, "int");
        flag = 1;
  //      puts(tipoData);
      break;

      case LCAPSULE:
        cont++;
      break;

      case RCAPSULE:
        cont--;
        if(cont == 0) strcpy(escopo,"global");
      break;

      case ID:
       hash = string2int(nomeID);
        strcpy(nomeID, yytext);
        token = yylex();
        buf[w] = token;
        printf("%d\t", token);
        w++;
        // IDS.linhas[0] = noline;
        if(token == LPAREN) {
          strcpy(tipoID, "func");

          if(strcmp(escopo,"global") == 0) {
            strcpy(escopo, nomeID);


          }
        } else {
          if(token == LBRACK) {
            // vetor
            // printf("Vetor\n");
            strcpy(tipoID, "vet");


          } else {
            // variavel
            strcpy(tipoID, "var");

          }
        }

        hash = string2int(nomeID)%211;
        if(!checkExistence(vetor, nomeID, lineno, hash, escopo, flag))
          insere(vetor, escopo, nomeID, tipoID, tipoData, lineno, hash);
          flag = 0;
      break;
    }
}
printf("Nome(ID)  Tipo(ID)  Tipo(Dado)   Escopo    Linhas em que aparece\n");
for(i = 0;i<211;i++){
    if(&vetor[i]!=NULL)
    printWTable(vetor, i);
}

f_out = fopen("out.txt", "w");
i = 0;
  while (buf[i] != 0) {
    switch(buf[i]) {
    case INT: fprintf(f_out, "INT\n"); break;
    case FLOAT: fprintf(f_out, "FLOAT\n"); break;
    case IF:	fprintf(f_out, "IF\n"); break;
    case ELSE:	fprintf(f_out, "ELSE\n"); break;
    case RETURN:fprintf(f_out, "RETURN\n"); break;
    case VOID:	fprintf(f_out, "VOID\n"); break;
    case WHILE: fprintf(f_out, "WHILE\n"); break;
    case PLUS: 	fprintf(f_out, "PLUS\n"); break;
    case MINUS:	fprintf(f_out, "MINUS\n"); break;
    case TIMES:	fprintf(f_out, "TIMES\n"); break;
    case OVER:	fprintf(f_out, "OVER\n"); break;
    case LT:	fprintf(f_out, "LT\n"); break;
    case LET:	fprintf(f_out, "LET\n"); break;
    case HT:	fprintf(f_out, "HT\n"); break;
    case HET:	fprintf(f_out, "HET\n"); break;
    case EQ:	fprintf(f_out, "EQ\n"); break;
    case NEQ:	fprintf(f_out, "NEQ\n"); break;
    case ASSIGN:fprintf(f_out, "ASSIGN\n"); break;
    case SEMI:	fprintf(f_out, "SEMI\n"); break;
    case COMMA:	fprintf(f_out, "COMMA\n"); break;
    case LPAREN:fprintf(f_out, "LPAREN\n"); break;
    case RPAREN:fprintf(f_out, "RPAREN\n"); break;
    case LBRACK:fprintf(f_out, "LBRACK\n"); break;
    case RBRACK:fprintf(f_out, "RBRACK\n"); break;
    case LCAPSULE:	fprintf(f_out, "LCAPSULE\n"); break;
    case RCAPSULE:	fprintf(f_out, "RCAPSULE\n"); break;
    case NUMI:	fprintf(f_out, "NUMI\n"); break;
    case NUMF:	fprintf(f_out, "NUMF\n"); break;
    case ID:	fprintf(f_out, "ID\n"); break;
    }
  i++;
  }

  printf("\nParser em execução...\n");
  abrirArq();
  if (yyparse()==0) printf("\nAnálise sintática OK\n");
  else printf("\nAnálise sintática apresenta ERRO\n");

  printTree();

  printf("Running Semantic Analysis...\n");
  if(semanticAnalysis(vetor) ==0)
    printf("Semantic Analysis OK\n");
  else
    printf("Errors found in Semantic Analysis\n");

  printf("Finished.\n");

  return 0;
}
