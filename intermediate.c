#include "globals.h"
#include "util.h"
#include "intermediate.h"

int flag_skip_print = 0;
int line_counter = 1;

int get_skip_print(){
  return flag_skip_print;
}

void set_skip_print(int i){
  flag_skip_print = 1;
}

int get_line_counter(){
  return line_counter;
}

void set_line_counter(int new_line_counter){
  line_counter = new_line_counter;
}

void print_lines(){
  int i;
  for (size_t i = 0; i < line_counter; i++)
    printf("%s\n", lines[i]);
}

void jump_to_main(){
  if(flag_skip_print)
    return;
  sprintf(lines[0], "%4d: \t %-6s \t %-2d %-2d\n", 0, OP_JUMPI, 0, line_counter);
}

void format_one(int register1, int register2,  int register3,char *operation){
    if(flag_skip_print){
      line_counter++;
      return;
    }
    sprintf(lines[line_counter], "%4d: \t %-6s \t %-2d %-2d %-2d\n",
     line_counter, operation, register1, register2, register3);
     line_counter++;
  }

void format_two(int register1, int register2, int register3,char *operation){
  if(flag_skip_print){
    line_counter++;
    return;
  }
  sprintf(lines[line_counter], "%4d: \t %-6s \t %-2d %-2d %-2d\n",
   line_counter, operation, register1, register2, register3);
   line_counter++;
}

void format_three(int register1, int register2, int register3,char *operation){
  if(flag_skip_print){
    line_counter++;
    return;
  }
  if(ends_with(operation, "JUMP")||ends_with(operation, "JZ")||ends_with(operation, "JN")){
    sprintf(lines[0], "%4d: \t %-6s \t %-2d %-2d %-2d\n",
     line_counter, operation, register1, register2, register3);
  }else
  sprintf(lines[0], "%4d: \t %-6s \t %-2d %-2d\n",
   line_counter, operation, register1, register3);
   line_counter++;
}

void format_four(int register1, int register2,char *operation){
  if(flag_skip_print){
    line_counter++;
    return;
  }
  if(ends_with(operation, "I"))
    sprintf(lines[0], "%4d: \t %-6s \t %-2d %-2d\n",
    line_counter, operation, register1, register2);
  else if(ends_with(operation, "LOAD") || ends_with(operation, "STORE"))
    sprintf(lines[0], "%4d: \t %-6s \t %-2d @%-2d\n",
    line_counter, operation, register1, register2);
  else if(ends_with(operation,"OUT"))
    sprintf(lines[0], "%4d: \t %-6s \t %-2d #%-2d\n",
    line_counter, operation, register1, register2);
  else if(ends_with(operation, "IN"))
    sprintf(lines[0], "%4d: \t %-6s \t %-2d\n",
    line_counter, operation, register1);
  else
    sprintf(lines[0], "%4d: \t %-6s \t %-2d $%-2d\n",
    line_counter, operation, register1, register2);
  line_counter++;
}

void format_five(char *operation){
  if(flag_skip_print){
    line_counter++;
    return;
  }
  sprintf(lines[0], "%4d: \t %-6s\n",
  line_counter, operation);
}
