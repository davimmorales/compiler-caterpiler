
#ifndef _CODE_H_
#define _CODE_H_

char lines [300][100];

int get_line_counter();

void jump_to_main();
int get_skip_print();
void print_lines();
void set_line_counter(int new_line_counter);
void set_skip_print(int i);

void format_one(int register1, int register2,  int register3,char *operation);
void format_two(int register1, int register2, int register3,char *operation);
void format_three(int register1, int register2, int register3,char *operation);
void format_four(int register1, int register2,char *operation);
void format_five(char *operation);

#endif
