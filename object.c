#include "object.h"

int register_zero = 0;
int register_result = 1;
int register_operator_loader = 2;
int register_operator_left = 3;
int register_operator_right = 4;
int register_context_offset = 5;
int register_operator_offset = 6;
int line_counter = 0;

void format_zero(galetype type, int immediate){
  if(type==G_HLT||type==G_NOP)
    printf("%4d: \ttype: %d\n", line_counter, type);
  else
    printf("%4d: \ttype: %d \timmediate: %d\n", line_counter, type, immediate);
  line_counter++;
}

void format_one(galetype type, int register_a, int immediate){
  printf("%4d: \ttype: %d \tregister: %d \timmediate: %d\n", line_counter, type, register_a, immediate);
}

void format_two(galetype type, int register_source, int register_target, int immediate);

void format_three(galetype type, int register_source_a, int register_source_b, int register_target);

void generate_code_launcher(list_quadruple *quad_list){
  file_target_code = fopen("target_code.gc", "w");

  fclose( file_target_code );

}
