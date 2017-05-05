/****************************************************/
/* File: cminus.l                                   */
/* Lex specification for C-, Table Generator        */
/* Lexical and Semantic Analysis                    */
/* Practical Compilers Work                         */
/* Davi Morales and Mateus Franco                   */
/****************************************************/
%{

  #include "globals.h"
  #include "util.h"
  #include "scan.h"
  #include "parse.h"
  /*#include "intermediate.h"*/


char tokenString[MAXTOKENLEN+1];


void abrirArq();

/*void printTree();*/

int lineno = 1;
int linenumber = 0;
int memcounter = 0;
static void code_generator_parsing(TreeNode *tree, TipoLista *hash);


%}

digit       [0-9]
number     {digit}+
letter      [a-zA-Z]
identifier  {letter}+{letter}*
newline     \n
whitespace  [ \t\r]+
other	[^0-9a-zA-Z;/=\-"+""*""("")""\n"\[\]\,\{\}\<\>|!=\==\<=\>=]
%option yylineno
%%

"int"		     {/*printf("INT ");*/ return INT;}
"float"		   {/*printf("FLOAT ");*/ return FLOAT;}
"if"         {/*printf("IF ");*/ return IF;}
"else"		   {/*printf("ELSE ");*/ return ELSE;}
"return"	   {/*printf("RETURN ");*/ return RETURN;}
"void"		   {/*printf("VOID ");*/return VOID;}
"while"		   {/*printf("WHILE ");*/ return WHILE;}
"+"			     {/*printf("PLUS ");*/ return PLUS;}
"-"			     {/*printf("MINUS ");*/ return MINUS;}
"*"			     {/*printf("TIMES ");*/ return TIMES;}
"<"			     {/*printf("LT ");*/ return LT;}
"/"			     {/*printf("OVER ");*/ return OVER;}
"<="         {/*printf("LET ");*/ return LET;}
">"			     {/*printf("HT ");*/ return HT;}
">="         {/*printf("HET ");*/ return HET;}
"=="         {/*printf("EQ ");*/ return EQ;}
"!="         {/*printf("NEQ ");*/ return NEQ;}
"="			     {/*printf("ASSIGN ");*/ return ASSIGN;}
";"			     {/*printf("SEMI ");*/ return SEMI;}
","			     {/*printf("COMMA ");*/ return COMMA;}
")"          {/*printf("RPAREN ");*/ return RPAREN;}
"("			     {/*printf("LPAREN ");*/ return LPAREN;}
"]"			     {/*printf("RBRACK ");*/ return RBRACK;}
"["			     {/*printf("LBRACK ");*/ return LBRACK;}
"{"			     {/*printf("LCAPSULE ");*/ return LCAPSULE;}
"}"			     {/*printf("RCAPSULE ");*/ return RCAPSULE;}
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
              {newline}       { lineno++; /*printf("\t%d\n", lineno);*/}
              {whitespace}    ;
              {number}       { /*printf("NUM ");* strcpy(id,yytext);*/ return NUM;}
              {identifier}    {/*printf("ID "); strcpy(id,yytext);*/ return ID;}
<<EOF>>         return(0);
{other}		{ printf("Lexical Error at line %d\n", lineno);}

%%

int label_counter = 0;
int temp_counter = 0;

int yywrap() {
  return 1;
}

list_quadruple *quadruple;

TokenType getToken(void){
  static int firstTime = TRUE;
  TokenType current;
  if(firstTime){
    firstTime = FALSE;
    linenumber++;
    FILE * file;
    yyin = fopen("entrada.txt", "r");
  }
  current = yylex();
  strncpy(tokenString, yytext, MAXTOKENLEN);

  /*printf("\t%d", linenumber);*/
  /*printf("%d %s %d\n", current, tokenString, linenumber);*/

  /*the one I really print*/
  /*printToken(current, tokenString);*/
  return current;
}

/*may be useful someday*/
/*static void traverse(TreeNode * t, void (* preProc) (TreeNode *), void (* postProc) (TreeNode *)){
    if(t != NULL){
        preProc(t);
        {
            int i;
            for(i = 0; i < MAXCHILDREN; ++i)
                traverse(t->child[i], preProc, postProc);
        }
        postProc(t);
        traverse(t->sibling, preProc, postProc);
    }
}*/

char L_side[20];
char R_side[20];
int verState = 0;
int voidFlag = 0;

/*registers*/
int reg_zero = 0;
int reg_result = 1;
int reg_operation_loader = 2;
int reg_operation_left = 3;
int reg_operation_right = 4;
int reg_operation_offset = 6;
int reg_context_offset = 5;



/*typedef struct TipoID{
    char nomeID[20];
    char tipoID[20];
    char tipoData[10];
    char escopo[30];
    int linhas[50];
    int top;
    struct TipoID *prox;
}TipoID;*/

typedef struct TypeSync{
  char name[45];
  char scope[45];
  int type;//where 1 stands for var, 2 for array and 3 for function
  int value;
  int top;
  struct TypeSync *next;
}TypeSync;

/*typedef struct{
    TipoID *start;
}TipoLista;*/

typedef struct{
  TypeSync *start;
}SyncList;

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

void insert(SyncList *list, char scope[], char nameID[], char typeID[]){
  TypeSync *new_node = malloc(sizeof(TypeSync));
  if(!strcmp(typeID,"func")){
    new_node->type = 3;
    strcpy(new_node->scope, "none");
  }
  else if(!strcmp(typeID,"var")){
    new_node->type = 1;
    strcpy(new_node->scope, scope);
  }
  else{
    new_node->type = 2;
    strcpy(new_node->scope, scope);

  }
  strcpy(new_node->name,nameID);
  TypeSync *p = list->start;
  if(p==NULL)
    list->start = new_node;
  else{
    while(p->next!=NULL)
      p = p->next;
    p->next = new_node;
    /*printf("%s\n", ->name);*/
  }
}

void insert_quadruple(list_quadruple *list, char arg_a[], char arg_b[], char op[], char res[]){
  type_quadruple *new_quadruple = malloc(sizeof(type_quadruple));

  strcpy(new_quadruple->argument_a, arg_a);
  strcpy(new_quadruple->argument_b, arg_b);
  strcpy(new_quadruple->operation, op);
  strcpy(new_quadruple->result, res);

  type_quadruple *p = list->start;
  if(p == NULL) {
      list->start = new_quadruple;
  } else {
      while(p->next!=NULL){
          p = p->next;
    }
      p->next = new_quadruple;
}
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

int checkExistance(TipoLista *Lista, char s[], int noline, int index, char scope[], int flag){
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

void printIDList(SyncList *list) {
  TypeSync *p = list->start;
  while(p!=NULL){
      printf("%s %s %d\n", p->name, p->scope, p->type);
      p = p->next;
  }
}

void abrirArq()
{
  yyin = fopen("entrada.txt", "r");

}

/*Semantic Analysis functions*/

/*Checks existance of a given variable*/
int buscaVariavel(TipoLista *list, char nomeID[], char escopo[]) {
    int hash = string2int(nomeID)%211;
    TipoID *c = list[hash].start;
    while(c != NULL) {
      if((!strcmp(nomeID, c->nomeID)) && (!strcmp(escopo, c->escopo)) || (!strcmp("global", c->escopo))) {
        return 1;
      }
      c = c->prox;
    }
    if(c == NULL) {
      /*printf("\nVariável %s não encontrada no escopo %s\n", nomeID, escopo);*/
      return 0;
    }
}

int functionType(TipoLista *list, char nomeID[]){
  int hash = string2int(nomeID)%211;
  TipoID *c = list[hash].start;
  while(c != NULL){
    if(!strcmp(nomeID, c->nomeID)&&!strcmp(c->tipoData, "void"))
      return 0;
    else
      return 1;
  }
}

/*Checks existance of a given function*/
int functionLookup(TipoLista *list, char nomeID[]) {
    int hash = string2int(nomeID)%211;
    TipoID *c = list[hash].start;
    char function[] = "func";
    while(c != NULL) {
      if((!strcmp(nomeID, c->nomeID)) && (!strcmp(function, c->tipoID))) {
        return 1;
      }
      c = c->prox;
    }
    /*if(c == NULL) {*/
      return 0;
    /*}*/
}

/*Role: Checks Existance of void variables*/
int checkVoid(TipoLista *list, int index){
TipoID *p = list[index].start;
while(p!=NULL){
    if(p->linhas[0] != 0) {
      //p->nomeID, p->tipoID, p->tipoData, p->escopo);
      if (!strcmp(p->tipoID, "var")&&!strcmp(p->tipoData,"void")) {
        return p->linhas[0];
      }
    }
      p = p->prox;
    }
    return 0;
}


/*Role: Checks Existance of Main function*/
int checkMain(TipoLista *list, int index){
TipoID *p = list[index].start;
while(p!=NULL){
    if(p->linhas[0] != 0) {
      //p->nomeID, p->tipoID, p->tipoData, p->escopo);
      if (!strcmp(p->tipoID, "func")&&
          !strcmp(p->tipoData,"void")&&
          !strcmp(p->nomeID, "main")&&
          p->linhas[1]==0)
        return 0;
    }
      p = p->prox;
    }
    return 1;
}

/*Role: Checks Existance of equal declarations in a same scope*/
int checkDecScope(TipoLista *list, int index){
  TipoID *p = list[index].start;
  TipoID *w;

  while(p!=NULL&&(!strcmp(p->tipoID,"var")||!strcmp(p->tipoID,"vet"))){
    if(p->linhas[0] != 0) {
      w = p->prox;
      while (w!=NULL&&(!strcmp(p->tipoID,"var")||!strcmp(p->tipoID,"vet"))){
        if(!strcmp(w->nomeID,p->nomeID)&&!strcmp(p->escopo,w->escopo)){
          return w->linhas[0];
        }
        w = w->prox;
      }
    }
      p = p->prox;
    }
    return 0;
  }

/*Role: Checks Existance of variables and functions with similar names*/
int checkSameVarFunc(TipoLista *list, int index){
  TipoID *p = list[index].start;
  TipoID *w;
  while (p!=NULL) {
    if (p->linhas[0] != 0) {
      w = p->prox;
      while (w!=NULL) {
        if (!strcmp(w->nomeID,p->nomeID)&&(((!strcmp(w->tipoID,"var")||!strcmp(w->tipoID,"vet"))
            &&!strcmp(p->tipoID,"func"))||((!strcmp(p->tipoID,"var")||!strcmp(w->tipoID,"vet"))
            &&!strcmp(w->tipoID,"func"))
          )){
            if (w->linhas[0])
              w->linhas[0];
            else
              return p->linhas[0];
        }

            w = w->prox;
      }
    }
    p = p->prox;
  }
  return 0;
}

int semanticAnalysis(TipoLista *hashList){
  int i;
  int j;
  int checkMainFlag = 1;
  int checkDecScopeFlag;
  int checkSameVarFuncFlag;

  for(i = 0;i<211;i++){
      if(&hashList[i]!=NULL){
        // Check Existance of void variables
        int checkVoidFlag;
        checkVoidFlag = checkVoid(hashList, i);
        if (checkVoidFlag)
          printf("Semantic error at line %d: Variable declared as void\n ", checkVoidFlag);
	//Check Existance of main function
       if (!checkMain(hashList, i))
         checkMainFlag = 0;
	//Check doubl  e var/vet declarations in a same scope
       checkDecScopeFlag = checkDecScope(hashList,i);
       if(checkDecScopeFlag)
            printf("Semantic error at line %d: double declaration at a same scope\n ", checkDecScopeFlag);
  //Check variables and functions with similar names
       checkSameVarFuncFlag = checkSameVarFunc(hashList,i);
       if(checkSameVarFuncFlag)
            printf("Semantic error at line %d: variable and function with same name\n ", checkSameVarFuncFlag);
      }
    }
    if (checkMainFlag)
      printf("Semantic error: main function not present or different from 'void main(void)'\n ");
  return 0;
}

/*AUXILIARY ANALYSIS FUNCTIONS*/
void allocate_variable_mem_loc(TreeNode *node, TipoLista *hash){
  int hash_line = string2int(node->attr.name)%211;
  TipoID *aux;
  for(aux = hash[hash_line].start;aux!=NULL;aux = aux->prox){
    if((!strcmp(aux->tipoID,"var")||!strcmp(aux->tipoID,"vet"))&&!strcmp(aux->nomeID,node->attr.name)
    && !strcmp(aux->escopo, node->scope)){
      if(aux->memloc==0)
        aux->memloc = ++memcounter;
      return;
    }
  }
}

/*void allocate_array_mem_loc(TreeNode *node, TipoLista *hash){
  int hash_line = string2int(node->attr.name)%211;
  TipoID *aux;
  for(aux = hash[hash_line].start;aux!=NULL;aux = aux->prox){
    if(!strcmp(aux->tipoID,"vet")&&!strcmp(aux->nomeID,node->attr.name)
    && !strcmp(aux->escopo, node->scope)){
      if(aux->memloc==0)
        aux->memloc = ++memcounter;
      return;
    }
  }
}*/

int get_variable_mem_loc(TreeNode *node, TipoLista *hash){
int hash_line = string2int(node->attr.name)%211;
TipoID *aux;
for(aux = hash[hash_line].start;aux!=NULL;aux = aux->prox){
  if((!strcmp(aux->tipoID,"var")||!strcmp(aux->tipoID,"vet"))&&!strcmp(aux->nomeID,node->attr.name)
  && !strcmp(aux->escopo, node->scope)){
    return aux->memloc;
  }
}
}



/*int get_variable_mem_loc(TreeNode *node, TipoLista *hash){
  int hashline;
  hashline = string2int(node->attr.name);


}*/


/*INTERMEDIATE CODE GENERATION*/
int freeze_line_loc(TreeNode *node){
  int future_line_loc;
  /*if(get_skip_print()){
    set_skip_print(1);
    int backup_line_loc = get_line_counter();
    code_generator_parsing(node);
    future_line_loc = get_line_counter()+1;
    set_line_counter(backup_line_loc);
  } else{
    set_skip_print(1);
    int backup_line_loc = get_line_counter();
    code_generator_parsing(node);
    future_line_loc = get_line_counter()+1;
    set_line_counter(backup_line_loc);
    set_skip_print(0);
  }*/
  return future_line_loc;
}

static void generate_statememt(TreeNode *tree, TipoLista *hash){
  TreeNode *p1, *p2, *p3, *aux;
  switch(tree->kind.stmt){
    case IfK:{
      p1 = tree->child[0];
      p2 = tree->child[1];
      p3 = tree->child[2];

      char *temp;
      char *t = "T";
      char *arg_a;
      char *label;
      char *result;
      char *possible_else;

      code_generator_parsing(p1, hash);
      sprintf(temp, "%d", temp_counter-1);
      arg_a = malloc(strlen(t)+strlen(temp)+1);
      strcpy(arg_a, t);
      strcat(arg_a, temp);

      sprintf(label, "%d", label_counter);
      result = label;
      label_counter++;
      insert_quadruple(quadruple, "none", "none", "if", result);
      code_generator_parsing(p2, hash);
      if(p3){
        sprintf(label, "%d", label_counter);
        possible_else = label;
        label_counter++;
      insert_quadruple(quadruple, "none", "none", "goto", possible_else);
      }
      insert_quadruple(quadruple, "none", "none", "label", result);
      code_generator_parsing(p3, hash);
      break;
    }
    case WhileK:{
      p1 = tree->child[0];
      p2 = tree->child[1];

      char *comparison_label;
      char *label;
      char *result;
      char *arg_a;
      char *temp;
      char *t = "T";

      sprintf(label, "%d", label_counter);
      comparison_label = label;
      label_counter++;

      insert_quadruple(quadruple, "none", "none", "label", comparison_label);
      code_generator_parsing(p1, hash);

      sprintf(temp, "%d", temp_counter-1);
      arg_a = malloc(strlen(t)+strlen(temp)+1);
      strcpy(arg_a, t);
      strcat(arg_a, temp);

      sprintf(label, "%d", label_counter);
      result = label;
      label_counter++;
      insert_quadruple(quadruple, "none", "none", "if", result);

      code_generator_parsing(p2, hash);
      insert_quadruple(quadruple, "none", "none", "goto", comparison_label);

      break;
    }
    case AssignK:
      p1 = tree->child[0];
      char *arg_a;
      char *result;
      char *label;
      char *temp;
      char *t = "T";

      if(p1->attr.name)
        strcpy(arg_a, p1->attr.name);
      else{
        sprintf(temp, "%d", temp_counter);
        arg_a = malloc(strlen(t)+strlen(temp)+1);
        strcpy(arg_a, t);
        strcat(arg_a, temp);
        temp_counter++;
      }

      if(tree->attr.name)
        strcpy(result, tree->attr.name);
      else{
        sprintf(temp, "%d", temp_counter);
        result = malloc(strlen(t)+strlen(temp)+1);
        strcpy(result, t);
        strcat(result, temp);
        temp_counter++;
      }
      /*if(p1->child[0]){ //it's an array
        code_generator_parsing(tree->child[1], hash);
        code_generator_parsing(p1->child[0], hash);
      }*/

      code_generator_parsing(tree->child[1], hash);

      insert_quadruple(quadruple, arg_a, "none", "assign", result);
      /*insert_quadruple(quadruple, )*/
      break;
      case CallK:
        if(!strcmp("input", tree->attr.name))
          insert_quadruple(quadruple, "none", "none", "call", "input");
        else if(!strcmp("output", tree->attr.name)){
          insert_quadruple(quadruple, "none", "none", "call", "output");
          code_generator_parsing(tree->child[0], hash);
        }
        else{
          insert_quadruple(quadruple, "none", "none", "call", tree->attr.name);

          /*if(get_skip_print())
              break;*/
            /*TreeNode *recovered_tree = get_tree_from_table(tree->attr.name);*/
            /*code_generator_parsing(recovered_tree->child[0]);*/

            /*TreeNode *assign_tree_parameters = build_parameter_tree(tree, recovered_tree);*/
            /*code_generator_parsing(assign_tree_parameters);*/

            /*int function_start_line = keep_line_loc(tree);*/
          }
          break;
          case ReturnK:
            aux = tree->child[0];

            char *ret;
            char *rtmp;
            char *w = "T";

            if(aux){
              code_generator_parsing(aux, hash);

              sprintf(rtmp, "%d", temp_counter);
              ret = malloc(strlen(t)+strlen(rtmp)+1);
              strcpy(ret, w);
              strcat(ret, rtmp);
              temp_counter++;

              insert_quadruple(quadruple, "none", "none", "return", ret);
            }
            insert_quadruple(quadruple, "none", "none", "return", " ");
            break;
          default:
            break;
        }
  }



static void generate_expression(TreeNode *tree, TipoLista *hash){
  int loc;
  TreeNode *p1, *p2;
  switch(tree->kind.exp){
    case ConstK:
      /*format_four(reg_result, tree->attr.value, OP_ADDI);*/
      /*printf("Constk\n");*/
    break;
    case IdK:
      loc = get_variable_mem_loc(tree, hash);
      p1 = tree->child[0];
      if(p1){//array
        code_generator_parsing(p1, hash);
        /*format_two();*/
        int i;
        int size = 5;//DELETE
        /*int size = get_array_size(tree);*/
        /*int end_jump = get_line_counter()+(size*5);*/
        for(i = loc; i< size+loc; i++){
          /*format_two();
          format_two();
          format_three();*/
          /*format_four(reg_result, i, OP_LD);*/
          /*format_three();*/
        }
        break;
      }
      /*format_four(reg_result, loc, OP_LD);*/
      break;

      case OpK:
        p1 = tree->child[0];
        p2 = tree->child[1];
        char *arg_a;
        char *arg_b;
        char *result;
        char *label;
        char *temp;
        char *t = "T";

        if(p1->attr.name)
          strcpy(arg_a, p1->attr.name);
        else{
          sprintf(temp, "%d", temp_counter);
          arg_a = malloc(strlen(t)+strlen(temp)+1);
          strcpy(arg_a, t);
          strcat(arg_a, temp);
          temp_counter++;
        }

        if(p2->attr.name)
          strcpy(arg_b, p2->attr.name);
        else{
          sprintf(temp, "%d", temp_counter);
          arg_b = malloc(strlen(t)+strlen(temp)+1);
          strcpy(arg_b, t);
          strcat(arg_b, temp);
          temp_counter++;
        }

        if(tree->attr.name)
          strcpy(result, tree->attr.name);
        else{
          sprintf(temp, "%d", temp_counter);
          result = malloc(strlen(t)+strlen(temp)+1);
          strcpy(result, t);
          strcat(result, temp);
          temp_counter++;
        }

        code_generator_parsing(p1, hash);
        code_generator_parsing(p2, hash);

        switch(tree->attr.oprtr){
          case PLUS:
          insert_quadruple(quadruple, arg_a, arg_b, "plus", result);
          break;
          case MINUS:
          insert_quadruple(quadruple, arg_a, arg_b, "minus", result);
          break;
          case TIMES:
          insert_quadruple(quadruple, arg_a, arg_b, "times", result);
            break;
          case OVER:
          insert_quadruple(quadruple, arg_a, arg_b, "over", result);
            break;
          case LT:
            sprintf(label, "%d", label_counter);
            insert_quadruple(quadruple, "none", "none", "label", label);
            insert_quadruple(quadruple, arg_a, arg_b, "lt", result);
            label_counter++;

            break;
          case HT:
          sprintf(label, "%d", label_counter);
          insert_quadruple(quadruple, "none", "none", "label", label);
          insert_quadruple(quadruple, arg_a, arg_b, "ht", result);
          label_counter++;

            break;
          case LET:
          sprintf(label, "%d", label_counter);
          insert_quadruple(quadruple, "none", "none", "label", label);
          insert_quadruple(quadruple, arg_a, arg_b, "let", result);
          label_counter++;

          break;
          case HET:
          sprintf(label, "%d", label_counter);
          insert_quadruple(quadruple, "none", "none", "label", label);
          insert_quadruple(quadruple, arg_a, arg_b, "het", result);
          label_counter++;

          break;
          case NEQ:
          sprintf(label, "%d", label_counter);
          insert_quadruple(quadruple, "none", "none", "label", label);
          insert_quadruple(quadruple, arg_a, arg_b, "neq", result);
          label_counter++;

          break;
          case EQ:
          sprintf(label, "%d", label_counter);
          insert_quadruple(quadruple, "none", "none", "label", label);
          insert_quadruple(quadruple, arg_a, arg_b, "eq", result);
          label_counter++;
          break;
          default:break;
        }default:break;
}
}


static void generate_declaration(TreeNode *tree, TipoLista *hash){
  TreeNode *aux;
  switch(tree->kind.dec){
    case FuncDecK:
      if(!strcmp(tree->attr.name,"main"))
        /*jump_to_main();*/insert_quadruple(quadruple, "none", "none", "label", "main");
      aux = tree->child[0];
      if(aux)
        code_generator_parsing(aux, hash);
      code_generator_parsing(tree->child[1], hash);
      /*if(tree->type = Void){
        ignore
      }*/
      if(strcmp(tree->attr.name,"main")&&tree->attr.name)
        /*format_tree_assembly();*/insert_quadruple(quadruple, "none", "none", "label", tree->attr.name);
    break;
    case VarK:
    aux = tree->child[0];
    if(aux->child[0] == NULL)
      allocate_variable_mem_loc(tree, hash);
    else{
      aux = tree->child[0]->child[0];
      allocate_variable_mem_loc(tree, hash);
      /*should be allocate_array_mem_loc();*/

    }
    break;
    case CompK:
      aux = tree->child[0];
      if(aux)//declaration
        code_generator_parsing(aux, hash);
      aux = tree->child[1];
      if(aux)//statement
        code_generator_parsing(aux, hash);
      break;
    case ParamK:
      allocate_variable_mem_loc(tree, hash);
    break;
    default:
    break;
  }
}

static void code_generator_parsing(TreeNode *tree, TipoLista *hash){
  if(tree!=NULL){
    switch(tree->nodekind){
      case StmtK:
      printf("stmt sbt\n");
      generate_statememt(tree, hash);
      break;
      case ExpK:
      printf("expk sbt\n");
      generate_expression(tree, hash);
      break;
      case DecK:
      printf("deck sbt\n");
      generate_declaration(tree, hash);
      break;
      case TypeK:
        break;
      default:
        break;
    }
    code_generator_parsing(tree->sibling, hash);
  }
}


void code_generator(TreeNode *syntaxTree, TipoLista *hash){
  code_generator_parsing(syntaxTree, hash);
}

int main() {
/*
extern int yydebug;
yydebug = 1;
*/
TreeNode * syntaxTree;
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
SyncList id_list;

for(i = 0; i < 211; i++) {
  vetor[i].start = NULL;
}

id_list.start = NULL;

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
  /*printf("%d\t", token);*/
  /*printf("%s\n", yytext);*/
  w++;
    switch(token) {

      case VOID:
        strcpy(tipoData, "void");
        flag = 2;
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
        flag = 0;
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
        /*printf("%d\t", token);*/
        w++;
        // IDS.linhas[0] = noline;
        if(token == LPAREN) {
          strcpy(tipoID, "func");
          if(strcmp(escopo,"global") == 0) {
            strcpy(escopo, nomeID);
          }
          if(flag==0&&!(functionLookup(vetor, nomeID)))
            printf("\nSemantic Error: Non declared function called, '%s()'. Line %d\n", nomeID, lineno);
        } else {
          if(token == LBRACK) {
            // vetor
            // printf("Vetor\n");
            strcpy(tipoID, "vet");
            if(flag == 0 && !(buscaVariavel(vetor, nomeID, escopo)))
              printf("\nSemantic error: bad declaration for Variable '%s'. Line %d\n", nomeID, lineno);


          } else {
            // variavel
            strcpy(tipoID, "var");
            if(flag == 0 && !(buscaVariavel(vetor, nomeID, escopo)))
              printf("\nSemantic error: bad declaration for Variable '%s'. Line %d\n", nomeID, lineno);

          }
        }

        hash = string2int(nomeID)%211;
        int newID = checkExistance(vetor, nomeID, lineno, hash, escopo, flag);
        if(!newID){
          insere(vetor, escopo, nomeID, tipoID, tipoData, lineno, hash);
        }
        insert(&id_list, escopo, nomeID,tipoID);
        if(token==SEMI) flag = 0;
      break;

      case SEMI:
        flag = 0;
        break;
    }
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
    case NUM:	fprintf(f_out, "NUM\n"); break;
    case ID:	fprintf(f_out, "ID\n"); break;
    }
  i++;
  }

  // Verificação de atribuições
  abrirArq();
  lineno = 1;
  strcpy(escopo, "global"); //  inicia laço com escopo global
  while ((token=yylex()) != '\0') {

      switch(token) {

        case ASSIGN:
            if(verState == 0) {
              verState = 1; // passa a procurar lado direito
            }
        break;

        case SEMI:
            if(verState == 1) {
              verState = 0; // volta a procurar lado esquerdo
            }

        break;

        case ID:
            if(verState == 0) {
              strcpy(L_side,yytext);
              if(functionLookup(vetor, L_side)) {
                strcpy(escopo, yytext);
              }
            } else {
              if(verState == 1) {
                while(token != SEMI && token != LPAREN) {
                  strcpy(R_side,yytext);
                  if(functionLookup(vetor, R_side)){
                    if(!functionType(vetor, R_side))
                      voidFlag = 1;
                  }

                  token = yylex();
                  if((token == MINUS) || (token == PLUS) || (token == TIMES) || (token == OVER)) token == yylex();
                }
                verState = 0;
              }
            }
        break;
      }
  }

  printf("\nParser running...\n");
  abrirArq();
  /*if (yyparse()==0) printf("\nSyntax Analysis OK\n");
  else printf("\nERROR in Syntax Analysis\n");*/

  /*printTree();*/

  if(voidFlag)
    printf("Semantic error: Void attribution to variable\n");

  printf("Running Semantic Analysis...\n");
  semanticAnalysis(vetor);
  printf("Semantic Analysis Finished\n");


  printf("Finished.\n");



  /*printIDList(&id_list);*/

  /*while(getToken() != ENDFILE);*/
  syntaxTree = parse();
  code_generator(syntaxTree, vetor);

  /*printTree(syntaxTree);*/

  /*printf("Name(ID)  Type(ID)  Type(Data)   Scope    Appears in lines\n");
  for(i = 0;i<211;i++){
      if(&vetor[i]!=NULL)
      printWTable(vetor, i);
  }*/

  return 0;
}
