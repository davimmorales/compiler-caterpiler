#include "globals.h"
#include "util.h"
#include "intermediate.h"

// static void generate_typeK(TreeNode *tree) {
//   TreeNode *c0, *c1;
//   c0 = tree->child[0];
//   c1 = tree->child[1];
//
//   if (c0->kind.stmt==FuncK) {
//     /* code */
//   }
//
// }

static int temporary = 0;

static void generate_relop(TreeNode *tree) {
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
        generate_intermediate_code(c0);
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
        generate_intermediate_code(c1);
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
        generate_intermediate_code(c0);
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
        generate_intermediate_code(c1);
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
          generate_intermediate_code(c0);
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
          generate_intermediate_code(c1);
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
          generate_intermediate_code(c0);
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
          generate_intermediate_code(c1);
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
          generate_intermediate_code(c0);
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
          generate_intermediate_code(c1);
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
          generate_intermediate_code(c0);
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
          generate_intermediate_code(c1);
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
      break;
    default:
      break;
  }
}

static void generate_arithop(TreeNode *tree){
  TreeNode *c0, *c1, *c2;
  c0 = tree->child[0];
  c1 = tree->child[1];
  c2 = tree->child[2];

  quadruple *quad = malloc(sizeof(quadruple));

  switch (tree->attr.oprtr) {
    case PLUS:
      printf("PLUS\n");
      break;
    case MINUS:
      printf("MINUS\n");
      break;
    case TIMES:
      printf("TIMES\n");
      break;
    case OVER:
      printf("OVER\n");
      break;
    default:
      break;
  }
}


static void generate_statement(TreeNode *tree) {
  TreeNode *c0, *c1, *c2;
  c0 = tree->child[0];
  c1 = tree->child[1];
  c2 = tree->child[2];

  switch (tree->kind.stmt) {
    case IfK:
    // printf("IfK\n");
      // if
      if(c0)
        generate_intermediate_code(c0);
      //store temporary;
      // then
      // if(c1)
      //   generate_intermediate_code(c1);
      // else
      // if(c2)
      //   generate_intermediate_code(c2);
      break;
    case WhileK:
      printf("WhileK\n");
      break;
    case AssignK:
      printf("AssignK\n");
      break;
    case ReturnK:
      printf("ReturnK\n");
      break;
    case VarK:
      printf("Vark\n");
      break;
    case VecK:
      printf("Veck\n");
      break;
    case FuncK:
      printf("FuncK\n");
      printf("Label: %s \n", tree->attr.name);
      if (c1) {
        generate_intermediate_code(c1);
      }
      break;
    case FuncVecK:
      printf("FuncVecK\n");
      printf("Array: %s\n", c0->attr.name);
      break;
    case FuncVarK:
      printf("FuncVarK\n");
      printf("Variable: %s\n", c0->attr.name);
      break;
    default:
    printf("Oops: uncomment something!\n");
      break;
  }
}

static void generate_expression(TreeNode *tree) {
  TreeNode *c0, *c1;
  c0 = tree->child[0];
  c1 = tree->child[1];

  switch (tree->kind.exp) {
    case TypeK:
      printf("TypeK\n");//print nothing
      generate_intermediate_code(c0);
      break;
    case RelOpK:
      generate_relop(tree);//print nothing
      printf("RelOpK\n");
      break;
    case ArithOpK:
      generate_arithop(tree);
      printf("ArithOpK\n");
      break;
    case ConstK:
      printf("ConstK\n");
      break;
    case IdK:
      printf("IdK\n");
      break;
    case VecIndexK:
      printf("VecIndexK\n");
      break;
    case CallK:
      printf("CallK\n");
      break;
    default:
      break;
  }
}

void generate_intermediate_code(TreeNode *tree){
  if(tree!=NULL){
    switch (tree->nodekind) {
      case StmtK:
        printf("statement\n");
        generate_statement(tree);
        break;
      case ExpK:
        printf("expression\n");
        generate_expression(tree);
        break;
      default:
        break;
    }
    generate_intermediate_code(tree->sibling);
  }
}
