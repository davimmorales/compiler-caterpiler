#include "globals.h"
#include "util.h"
#include "intermediate.h"

static int temporary = 0;
static int label = 0;
static int flag_param = 0;

void insert_quadruple(list_quadruple *quad_list, quadruple *quad){
  quadruple *p = quad_list->start;
  if(p==NULL)
    quad_list->start = quad;
  else{
    while(p->next!=NULL){
      p = p->next;
    }
    p->next = quad;
  }
}

void print_quadruple_list(list_quadruple *quad_list){
  quadruple *p = quad_list->start;
  while (p!=NULL) {
    printf("%d\n", p->op);
    p = p->next;
  }
}

static void generate_relop(list_quadruple *quad_list, TreeNode *tree) {
  TreeNode *c0, *c1, *c2;
  c0 = tree->child[0];
  c1 = tree->child[1];
  c2 = tree->child[2];
  int aux;

  quadruple *quad = malloc(sizeof(quadruple));

  switch (tree->attr.oprtr) {
    case EQ:
    if(c0){
      if(c0->kind.stmt == VarK){
        strcpy(quad->address_1.name, c0->attr.name);
        quad->address_1.kind = String;
        printf("%s\n", quad->address_1.name);
      }else if (c0->kind.exp == ConstK) {
        quad->address_1.value = c0->attr.value;
        quad->address_1.kind = IntConst;
        printf("%d\n", quad->address_1.value);
      }else{
        generate_intermediate_code(quad_list, c0);
        printf("%d\n", temporary);
        quad->address_1.value = temporary;
        quad->address_1.kind = Temp;
        temporary++;
      }
    }

    if(c1){
      if(c1->kind.stmt == VarK){
        strcpy(quad->address_2.name, c1->attr.name);
        quad->address_2.kind = String;
        printf("%s\n", quad->address_2.name);
      }else if (c1->kind.exp == ConstK) {
        quad->address_2.value = c1->attr.value;
        quad->address_2.kind = IntConst;
        printf("%d\n", quad->address_2.value);
      }else{
        generate_intermediate_code(quad_list, c1);
        printf("%d\n", temporary);
        quad->address_2.value = temporary;
        quad->address_2.kind = Temp;
        temporary++;
      }
    }
    quad->address_3.value = temporary;
    quad->address_3.kind = Temp;
    temporary++;

    quad->op = EqlK;
    insert_quadruple(quad_list, quad);
      break;
    case NEQ:
    if(c0){
      if(c0->kind.stmt == VarK){
        strcpy(quad->address_1.name, c0->attr.name);
        quad->address_1.kind = String;
        printf("%s\n", quad->address_1.name);
      }else if (c0->kind.exp == ConstK) {
        quad->address_1.value = c0->attr.value;
        quad->address_1.kind = IntConst;
        printf("%d\n", quad->address_1.value);
      }else{
        generate_intermediate_code(quad_list, c0);
        printf("%d\n", temporary);
        quad->address_1.value = temporary;
        quad->address_1.kind = Temp;
        temporary++;
      }
    }

    if(c1){
      if(c1->kind.stmt == VarK){
        strcpy(quad->address_2.name, c1->attr.name);
        quad->address_2.kind = String;
        printf("%s\n", quad->address_2.name);
      }else if (c1->kind.exp == ConstK) {
        quad->address_2.value = c1->attr.value;
        quad->address_2.kind = IntConst;
        printf("%d\n", quad->address_2.value);
      }else{
        generate_intermediate_code(quad_list, c1);
        printf("%d\n", temporary);
        quad->address_2.value = temporary;
        quad->address_2.kind = Temp;
        temporary++;
      }
    }
    quad->address_3.value = temporary;
    quad->address_3.kind = Temp;
    temporary++;

    quad->op = NeqK;
    insert_quadruple(quad_list, quad);

    break;
    case LT:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = LsrK;
      insert_quadruple(quad_list, quad);

      break;
    case LET:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = LeqK;
      insert_quadruple(quad_list, quad);

      break;
    case HT:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = GtrK;
      insert_quadruple(quad_list, quad);

      break;
    case HET:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = GeqK;
      insert_quadruple(quad_list, quad);

      break;
    default:
      break;
  }
}

static void generate_arithop(list_quadruple *quad_list, TreeNode *tree){
  TreeNode *c0, *c1, *c2;
  c0 = tree->child[0];
  c1 = tree->child[1];
  c2 = tree->child[2];

  quadruple *quad = malloc(sizeof(quadruple));

  switch (tree->attr.oprtr) {
    case PLUS:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = AddK;
      insert_quadruple(quad_list, quad);

      break;
    case MINUS:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("t%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("t%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = SubK;
      insert_quadruple(quad_list, quad);

      break;
    case TIMES:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("t%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("t%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = TimK;
      insert_quadruple(quad_list, quad);

      break;
    case OVER:
      if(c0){
        if(c0->kind.stmt == VarK){
          strcpy(quad->address_1.name, c0->attr.name);
          quad->address_1.kind = String;
          printf("%s\n", quad->address_1.name);
        }else if (c0->kind.exp == ConstK) {
          quad->address_1.value = c0->attr.value;
          quad->address_1.kind = IntConst;
          printf("%d\n", quad->address_1.value);
        }else{
          generate_intermediate_code(quad_list, c0);
          printf("t%d\n", temporary);
          quad->address_1.value = temporary;
          quad->address_1.kind = Temp;
          temporary++;
        }
      }

      if(c1){
        if(c1->kind.stmt == VarK){
          strcpy(quad->address_2.name, c1->attr.name);
          quad->address_2.kind = String;
          printf("%s\n", quad->address_2.name);
        }else if (c1->kind.exp == ConstK) {
          quad->address_2.value = c1->attr.value;
          quad->address_2.kind = IntConst;
          printf("%d\n", quad->address_2.value);
        }else{
          generate_intermediate_code(quad_list, c1);
          printf("t%d\n", temporary);
          quad->address_2.value = temporary;
          quad->address_2.kind = Temp;
          temporary++;
        }
      }
      quad->address_3.value = temporary;
      quad->address_3.kind = Temp;
      temporary++;

      quad->op = OvrK;
      insert_quadruple(quad_list, quad);

      break;
    default:
      break;
  }
}


static void generate_statement(list_quadruple *quad_list, TreeNode *tree) {
  TreeNode *c0, *c1, *c2;
  c0 = tree->child[0];
  c1 = tree->child[1];
  c2 = tree->child[2];
  int aux;
  int aux2;
  int aux3;

  quadruple *quad0 = malloc(sizeof(quadruple));
  quadruple *quad1 = malloc(sizeof(quadruple));
  quadruple *quad2 = malloc(sizeof(quadruple));
  quadruple *quad3 = malloc(sizeof(quadruple));

  quad0->address_1.kind = Empty;
  quad0->address_2.kind = Empty;
  quad0->address_3.kind = Empty;

  quad1->address_1.kind = Empty;
  quad1->address_2.kind = Empty;
  quad1->address_3.kind = Empty;

  quad2->address_1.kind = Empty;
  quad2->address_2.kind = Empty;
  quad2->address_3.kind = Empty;

  quad3->address_1.kind = Empty;
  quad3->address_2.kind = Empty;
  quad3->address_3.kind = Empty;

  switch (tree->kind.stmt) {
    case IfK:
      // if
      if(c0){
        generate_intermediate_code(quad_list, c0);
        aux = temporary - 1;
        aux2 = label;
        label++;
        printf("If_false t%d goto L%d\n", aux, aux2);
        quad0->address_1.kind = Temp;
        quad0->address_1.value = aux;
        quad0->address_2.kind = Empty;
        quad0->address_3.kind = LabAddr;
        quad0->address_3.value = aux2;
        quad0->op = IffK;
        insert_quadruple(quad_list, quad0);

        //add quad0
      }
      // then
      if(c1)
        generate_intermediate_code(quad_list, c1);
      if (c2) {
        aux3 = label;
        label++;
        printf("goto L%d\n", aux3);
        quad1->address_1.kind = Empty;
        quad1->address_2.kind = Empty;
        quad1->address_3.kind = LabAddr;
        quad1->address_3.value = aux3;
        quad1->op = GtoK;
        insert_quadruple(quad_list, quad1);

        //add quad1
      }
      printf("L%d:\n", aux2);
      quad2->address_1.kind = Empty;
      quad2->address_2.kind = Empty;
      quad2->address_3.kind = LabAddr;
      quad2->address_3.value = aux2;
      quad2->op = LblK;
      insert_quadruple(quad_list, quad2);
      // add quad2
      // else
      if(c2){
        generate_intermediate_code(quad_list, c2);
        quad3->address_1.kind = Empty;
        quad3->address_2.kind = Empty;
        quad3->address_3.kind = LabAddr;
        quad3->address_3.value = aux3;
        quad3->op = LblK;
        insert_quadruple(quad_list, quad3);
        // add quad3
        // printf("L%d: ", aux3);
      }
      break;
    case WhileK:
      if (c0) {
        aux2 = label;
        label++;
        aux3 = label;
        label++;
        printf("L%d: ", aux2);
        quad0->address_1.kind = Empty;
        quad0->address_2.kind = Empty;
        quad0->address_3.kind = LabAddr;
        quad0->address_3.value = aux2;
        quad0->op = LblK;
        insert_quadruple(quad_list, quad0);

        // add quad0
        generate_intermediate_code(quad_list, c0);
        aux = temporary - 1;
        printf("If_false t%d goto L%d\n", aux, aux3);
        quad1->address_1.kind = Temp;
        quad1->address_1.value = aux;
        quad1->address_2.kind = Empty;
        quad1->address_3.kind = LabAddr;
        quad1->address_3.value = aux3;
        quad1->op = IffK;
        insert_quadruple(quad_list, quad1);

        // add quad1
      }
        if(c1)
          generate_intermediate_code(quad_list, c1);
        printf("goto L%d\n", aux2);
        quad2->address_1.kind = Empty;
        quad2->address_2.kind = Empty;
        quad2->address_3.kind = LabAddr;
        quad2->address_3.value = aux2;
        quad2->op = GtoK;
        insert_quadruple(quad_list, quad2);
        // add quad2

        printf("L%d:\n", aux3);
        quad3->address_1.kind = Empty;
        quad3->address_2.kind = Empty;
        quad3->address_3.kind = LabAddr;
        quad3->address_3.value = aux3;
        quad3->op = LblK;
        insert_quadruple(quad_list, quad3);
        // add quad3
      break;
    case AssignK:
      // printf("AssignK\n");
      if (c0) {
        if (c0->child[0]) {
          TreeNode *g1 = c0->child[0];
          if (g1->child[0]){
            generate_intermediate_code(quad_list, g1);
            aux = temporary-1;
            printf("Array assigned: %s [t%d] =\n", c0->attr.name, aux);
            quad0->address_2.kind = Temp;
            quad0->address_2.value = aux;
          }else{
            printf("Array assigned: %s [%s] =\n", c0->attr.name, g1->attr.name);
            quad0->address_2.kind = String;
            strcpy(quad0->address_2.name, g1->attr.name);
          }
          quad0->op = AsaK;

        }else{
          printf("Variable assigned: %s = \n", c0->attr.name);
          quad0->address_2.kind = Empty;
          quad0->op = AsvK;
        }
        quad0->address_3.kind = String;
        strcpy(quad0->address_3.name, c0->attr.name);
        insert_quadruple(quad_list, quad0);
      }

      if (c1){
        TreeNode *g2 = c1->child[0];
        if (g2) {
          generate_intermediate_code(quad_list, c1);
          aux2 = temporary-1;
          quad1->address_1.kind = Temp;
          quad1->address_1.value = aux2;
        }else if(c1->attr.oprtr==ConstK){
          quad1->address_1.kind = IntConst;
          quad1->address_1.value = c1->attr.value;
        }else if(c1->attr.oprtr==VarK){
          quad1->address_1.kind = String;
          strcpy(quad1->address_1.name, c1->attr.name);
        }
        insert_quadruple(quad_list, quad1);
      }
      // add quad0
      break;
    case ReturnK:
      // printf("ReturnK\n");
      quad0->address_1.kind = Empty;
      quad0->address_2.kind = Empty;
      if (!c0) {
        printf("Return void\n");
        quad0->address_3.kind = Empty;
      }else{
        TreeNode *g1 = c0->child[0];
        if(g1){
          generate_intermediate_code(quad_list, c0);
          aux = temporary;
          printf("Return t%d\n", aux);
          quad0->address_3.kind = Temp;
          quad0->address_3.value = aux;
        }else{
          if (c0->kind.stmt == ConstK) {
            printf("Return %d\n", c0->attr.value);
            quad0->address_3.kind = IntConst;
            quad0->address_3.value = c0->attr.value;
          }else
            printf("Return %s\n", c0->attr.name);
            quad0->address_3.kind = String;
            strcpy(quad0->address_3.name, c0->attr.name);
        }
      }
      quad0->op = RetK;
      insert_quadruple(quad_list, quad0);
      // add quad0
      break;
    case VarK:
      // printf("Vark\n");
      // not used in intermediate code generation
      break;
    case VecK:
      // printf("Veck\n");
      // not used in intermediate code generation
      break;
    case FuncK:
      // printf("FuncK\n");
      printf("Label: %s \n", tree->attr.name);
      quad0->address_1.kind = Empty;
      quad0->address_2.kind = Empty;
      quad0->address_3.kind = String;
      strcpy(quad0->address_3.name, tree->attr.name);
      quad0->op = LblK;
      insert_quadruple(quad_list, quad0);

      // add quad0
      if (c1) {
        generate_intermediate_code(quad_list, c1);
      }
      break;
    case FuncVecK:
      // printf("FuncVecK\n");
      // printf("Array: %s\n", c0->attr.name);
      break;
    case FuncVarK:
      // printf("FuncVarK\n");
      // printf("Variable: %s\n", c0->attr.name);
      break;
    default:
    printf("Oops: uncomment something!\n");
      break;
  }
}

static void generate_expression(list_quadruple *quad_list, TreeNode *tree) {
  TreeNode *c0, *c1;
  c0 = tree->child[0];
  c1 = tree->child[1];

  quadruple *quad0 = malloc(sizeof(quadruple));
  quadruple *quad1 = malloc(sizeof(quadruple));
  quadruple *quad2 = malloc(sizeof(quadruple));


  quad0->address_1.kind = Empty;
  quad0->address_2.kind = Empty;
  quad0->address_3.kind = Empty;

  quad1->address_1.kind = Empty;
  quad1->address_2.kind = Empty;
  quad1->address_3.kind = Empty;

  quad2->address_1.kind = Empty;
  quad2->address_2.kind = Empty;
  quad2->address_3.kind = Empty;

  switch (tree->kind.exp) {
    case TypeK:
      generate_intermediate_code(quad_list, c0);
      break;
    case RelOpK:
      generate_relop(quad_list, tree);//print nothing
      break;
    case ArithOpK:
      generate_arithop(quad_list, tree);
      break;
    case ConstK:
      printf("ConstK\n");
      break;
    case IdK:
      // if (!c0&&!c1) {
      //   printf("Variable %s\n", tree->attr.name);
      // }
      break;
    case VecIndexK:
      printf("VecIndexK\n");
      break;
    case CallK:
    {
      int count;
      count = 0;
      if (!c0) {
        printf("call %s, 0\n", tree->attr.name);
        quad0->op = CalK;
        insert_quadruple(quad_list, quad0);
        break;
      }else{
        do{
          if (c0->child[0]) {
            int aux;
            TreeNode *g0 = c0->child[0];
            generate_intermediate_code(quad_list, c0);
            aux = temporary-1;
            printf("param t%d\n", aux);
            quad0->address_1.kind = Empty;
            quad0->address_2.kind = Empty;
            quad0->address_3.kind = Temp;
            quad0->address_3.value = aux;
            quad0->op = PrmK;
          }else if(!c0->child[0]){
            flag_param = 1;
            printf("param %s\n", c0->attr.name);
            quad0->address_1.kind = Empty;
            quad0->address_2.kind = Empty;
            quad0->address_3.kind = String;
            strcpy(quad0->address_3.name, c0->attr.name);
            quad0->op = PrmK;
          }
          count++;
            c0 = c0->sibling;

            if(!c0)
              break;
            insert_quadruple(quad_list, quad0);
          // add quad0
        }while(1);
        printf("call %s, %d\n", tree->attr.name, count);
      }

      quad1->address_1.kind = IntConst;
      quad1->address_1.value = count;
      quad1->address_2.kind = Empty;
      quad1->address_3.kind = String;
      strcpy(quad1->address_3.name, tree->attr.name);
      quad1->op = CalK;

      insert_quadruple(quad_list, quad1);

      // add quad1
      break;
    }
    default:
      break;
  }
}

void generate_intermediate_code(list_quadruple *quad_list, TreeNode *tree){
  if(tree!=NULL){
    switch (tree->nodekind) {
      case StmtK:
        // printf("statement\n");
        generate_statement(quad_list, tree);
        break;
      case ExpK:
        // printf("expression\n");
        generate_expression(quad_list, tree);
        break;
      default:
        break;
    }
    generate_intermediate_code(quad_list, tree->sibling);
  }
}
