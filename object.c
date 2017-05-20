#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "object.h"

int register_zero = 0;
int register_result = 1;
int register_operator_loader = 2;
int register_operator_left = 3;
int register_operator_right = 4;
int register_context_offset = 5;
int register_operator_offset = 6;

void format_zero(galetype type, int immediate);

void format_one(galetype type, int register_a, int immediate);

void format_two(galetype type, int register_source, int register_target, int immediate);

void format_three(galetype type, int register_source_a, int register_source_b, int register_target);
