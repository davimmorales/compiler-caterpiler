#include "object.h"

/* Function to convert a decinal number to binary number */
char *decimal_to_binary(int decimal, int lenght){
  int c, d, count;
  char *pointer;

  count = 0;
  pointer = (char*) malloc(32+1);

  if (pointer==NULL) {
    exit(EXIT_FAILURE);
  }

  for ( c = lenght-1; c >= 0; c--) {
    d = decimal >> c;

    if(d & 1){
      *(pointer + count) = 1 + '0';
    }else{
      *(pointer + count) = 0 + '0';
    }
    count++;
  }
  *(pointer + count) = '\0';

  return pointer;
}

void print_target_code(list_instructions *instructions_list){
  file_target_code = fopen("target_code.gc", "w");

  type_instruction *instruction = instructions_list->start;

  char *number;

  while (instruction!=NULL) {
    fprintf(file_target_code, "\t \t instructionsRAM[%d] = 32'b", instruction->line);
    switch (instruction->type) {
      case G_ADD:
        fprintf(file_target_code, "%s%s%s%s00000000000;//ADD r[%d],r[%d] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_ADDI:
        fprintf(file_target_code, "%s%s%s%s;//ADDi r[%d], #%d to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_c, 5),
        decimal_to_binary(instruction->immediate, 16),
        instruction->register_a, instruction->immediate, instruction->register_c);
      break;
      case G_SUB:
        fprintf(file_target_code, "%s%s%s%s00000000000;//SUB r[%d],r[%d] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_SUBI:
        fprintf(file_target_code, "%s%s%s%s;//SUBi r[%d], #%d to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_c, 5),
        decimal_to_binary(instruction->immediate, 16),
        instruction->register_a, instruction->immediate, instruction->register_c);
      break;
      case G_MUL:
        fprintf(file_target_code, "%s%s%s%s00000000000;//TIMES r[%d],r[%d] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_DIV:
        fprintf(file_target_code, "%s%s%s%s00000000000;//DIVIDE r[%d],r[%d] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_INC:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_DEC:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_AND:
        fprintf(file_target_code, "%s%s%s%s00000000000;//AND r[%d],r[%d] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_OR:
        fprintf(file_target_code, "%s%s%s%s00000000000;//OR r[%d],r[%d] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_MOD:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_XOR:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_NOT:
        fprintf(file_target_code, "%s%s%s0000000000000000;//NOT r[%d] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_c);
      break;
      case G_SHL:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_SHR:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_PBC:
        fprintf(file_target_code, "%s%s000000000000000000000;//Pre Branch r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        instruction->register_a);
      break;
      case G_BOZ:
        fprintf(file_target_code, "%s%s;//Branch on Zero #%d\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->immediate, 26),
        instruction->immediate);
      break;
      case G_BON:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_JMP:
        fprintf(file_target_code, "%s%s;//Jump to #%d\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->immediate, 26),
        instruction->immediate);
      break;
      case G_SLT:
        fprintf(file_target_code, "%s%s%s%s00000000000;//SLT if r[%d] < r[%d], r[%d] = 1 else r[%d] = 0\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c, instruction->register_c);
      break;
      case G_LD:
        fprintf(file_target_code, "%s%s%s;//Load M[#%d] to R[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->immediate, instruction->register_a);
      break;
      case G_ST:
        fprintf(file_target_code, "%s%s%s;//Store R[%d] in M[#%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a, instruction->immediate);
      break;
      case G_LDI:
        fprintf(file_target_code, "%s%s%s;//Loadi #%d to R[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->immediate, instruction->register_a);
      break;
      case G_NOP:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_IN:
        fprintf(file_target_code, "%s%s%s;//Input to R[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a);
      break;
      case G_HLT:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_POUT:
        fprintf(file_target_code, "%s%s%s;//Pre Output R[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a);
      break;
      case G_OUT:
        fprintf(file_target_code, "%s%s%s;//Output R[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a);
      break;
      case G_LDR:
        fprintf(file_target_code, "%s%s%s%s;//Loadr m[r[%d]] to r[%d]\n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_c, 5),
        decimal_to_binary(instruction->immediate, 16),
        instruction->register_a, instruction->register_c);
      break;
      case G_STR:
        fprintf(file_target_code, "%s%s%s%s;//Storer to r[%d] in m[r[%d]] \n",
        decimal_to_binary(instruction->type, 6),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_c, 5),
        decimal_to_binary(instruction->immediate, 16),
        instruction->register_c, instruction->register_a);
      break;
      default:
        printf("Galetype Unknown: %d\n", instruction->type);
      break;
    }
    instruction = instruction->next;
  }

  fclose( file_target_code );
}
