#include "object.h"

int register_zero = 0;
int register_result = 1;
int register_operator_loader = 2;
int register_operator_left = 3;
int register_operator_right = 4;
int register_context_offset = 5;
int register_operator_offset = 6;
int line_counter = 0;

//numbers relate to amount of registers in the operation
void format_zero(galetype type, int immediate){
  if(type==G_HLT||type==G_NOP)
    printf("%4d: \ttype: %d\n", line_counter, type);
  else
    printf("%4d: \ttype: %d \timmediate: %d\n", line_counter, type, immediate);
  line_counter++;
}

void format_one(galetype type, int register_a, int immediate){
  printf("%4d: \ttype: %d \tregister: %d \timmediate: %d\n", line_counter, type, register_a, immediate);
  line_counter++;
}

void format_two(galetype type, int register_source, int register_target, int immediate){
  printf("%4d: \ttype: %d \tsource: %d \ttarget: %d \timmediate: %d\n",
  line_counter, type, register_source,register_target, immediate);
  line_counter++;
}

void format_three(galetype type, int register_source_a, int register_source_b, int register_target){
  printf("%4d: \ttype: %d \tsource_a: %d \tsource_b: %d \ttarget: %d\n",
  line_counter, type, register_source_a, register_source_b, register_target);
  line_counter++;
}

void generate_code(list_quadruple *quad_list){
    quadruple *p = quad_list->start;
    while (p!=NULL) {
      switch (p->op) {
        case AddK:
        // printf("galeto\n");
          // format_three(G_ADD, , register_result)
          break;
        case SubK:
          break;
        case TimK:
          break;
        case EqlK:
          break;
        case GeqK:
          break;
        case AsvK:
          break;
        case AsaK:
          break;
        case InnK:
          break;
        case OutK:
          break;
        case PrmK:
          break;
        case CalK:
          break;
        case RetK:
          break;
        case IffK:
          break;
        case GtoK:
          break;
        case HltK:
          break;
        case LblK:
          break;
        case CstK:
          break;
        case VstK:
          break;
        case AstK:
          break;
        default:
          break;
      }
      // printf("%d\n", p->op);
      p = p->next;
    }
  }


void generate_code_launcher(list_quadruple *quad_list){
  file_target_code = fopen("target_code.gc", "w");
  generate_code(quad_list);
  fclose( file_target_code );
}

to do:
- attribute index to quadruples
- find functions declarations and specify them in symbols table
- allocate global/main variables in memory (static)
