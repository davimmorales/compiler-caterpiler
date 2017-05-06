#include "globals.h"
#include "util.h"
#include "intermediate.h"

static void generate_statement(TreeNode *tree) {
  switch (tree->kind.stmt) {
    case IfK:
      printf("IfK\n");
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
      break;
    case FuncVecK:
      printf("FuncVecK\n");
      break;
    default:
      break;
  }
}

static void generate_expression(TreeNode *tree) {
  switch (tree->kind.exp) {
    case TypeK:
      printf("TypeK\n");
      break;
    case RelOpK:
      printf("RelOpK\n");
      break;
    case ArithOpK:
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
        printf("statement");
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
