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

static void generate_relop(TreeNode *tree) {
  switch (tree->attr.oprtr) {
    case EQ:
      printf("EQ\n");
      break;
    case NEQ:
      printf("NEQ\n");
      break;
    case LT:
      printf("LT\n");
      break;
    case LET:
      printf("LET\n");
      break;
    case HT:
      printf("HT\n");
      break;
    case HET:
      printf("HET\n");
      break;
    default:
      break;
  }
}

static void generate_arithop(TreeNode *tree){
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
      printf("IfK\n");
      // if
      if(c0)
        generate_intermediate_code(c0);
      // then
      if(c1)
        generate_intermediate_code(c1);
      // else
      if(c2)
        generate_intermediate_code(c2);
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
      printf("Label: %s\n", tree->attr.name);
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
