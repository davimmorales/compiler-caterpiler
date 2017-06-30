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

int count_instructions(list_instructions *instructions_list){
  type_instruction *instruction = instructions_list->start;
  int count;
  count = 0;

  while (instruction!=NULL) {
    count++;
    instruction = instruction->next;
  }

  return count;
}

void print_target_code(list_instructions *instructions_list){
  file_target_code = fopen("simpleInstructionsRam.v", "w");

  type_instruction *instruction = instructions_list->start;

  fprintf(file_target_code, "module simpleInstructionsRam(clock, address, iRAMOutput);\n");
  fprintf(file_target_code, "\t input [9:0] address;\n");
  fprintf(file_target_code, "\t input clock;\n");
  fprintf(file_target_code, "\t output [31:0] iRAMOutput;\n");
  fprintf(file_target_code, "\t integer firstClock = 0;\n");
  fprintf(file_target_code, "\t reg [31:0] instructionsRAM[%d:0];\n", count_instructions(instructions_list));
  fprintf(file_target_code, "\n");
  fprintf(file_target_code, "\t always @ ( posedge clock ) begin\n");
  fprintf(file_target_code, "\t \t if (firstClock==0) begin\n \n");

  while (instruction!=NULL) {
    fprintf(file_target_code, "\t \t instructionsRAM[%d] = 32'b", instruction->line);
    switch (instruction->type) {
      case G_ADD:
        fprintf(file_target_code, "000000%s%s%s00000000000;//ADD r[%d],r[%d] to r[%d]\n",
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_ADDI:
        fprintf(file_target_code, "000001%s%s%s;//ADDi r[%d], #%d to r[%d]\n",
        decimal_to_binary(instruction->register_c, 5),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 16),
        instruction->register_a, instruction->immediate, instruction->register_c);
      break;
      case G_SUB:
        fprintf(file_target_code, "000010%s%s%s00000000000;//SUB r[%d],r[%d] to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_SUBI:
        fprintf(file_target_code, "000011%s%s%s;//SUBi r[%d], #%d to r[%d]\n",

        decimal_to_binary(instruction->register_c, 5),
        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 16),
        instruction->register_a, instruction->immediate, instruction->register_c);
      break;
      case G_MUL:
        fprintf(file_target_code, "000100%s%s%s00000000000;//TIMES r[%d],r[%d] to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_DIV:
        fprintf(file_target_code, "000101%s%s%s00000000000;//DIVIDE r[%d],r[%d] to r[%d]\n",

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
        fprintf(file_target_code, "001000%s%s%s00000000000;//AND r[%d],r[%d] to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c);
      break;
      case G_OR:
        fprintf(file_target_code, "001001%s%s%s00000000000;//OR r[%d],r[%d] to r[%d]\n",

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
        fprintf(file_target_code, "001101%s%s0000000000000000;//NOT r[%d] to r[%d]\n",

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
        fprintf(file_target_code, "011111%s000000000000000000000;//Pre Branch r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        instruction->register_a);
      break;
      case G_BOZ:
        fprintf(file_target_code, "010011%s;//Branch on Zero #%d\n",

        decimal_to_binary(instruction->immediate, 26),
        instruction->immediate);
      break;
      case G_BON:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_JMP:
        fprintf(file_target_code, "010101%s;//Jump to #%d\n",

        decimal_to_binary(instruction->immediate, 26),
        instruction->immediate);
      break;
      case G_JMPR:
        fprintf(file_target_code, "100011%s%s;//Jump to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a);
      break;
      case G_NOP:
        fprintf(file_target_code, "01101100000000000000000000000000;//Nop\n",
        decimal_to_binary(instruction->type, 6));
      break;
      case G_SLT:
        fprintf(file_target_code, "010111%s%s%s00000000000;//SLT if r[%d] < r[%d], r[%d] = 1 else r[%d] = 0\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_b, 5),
        decimal_to_binary(instruction->register_c, 5),
        instruction->register_a, instruction->register_b, instruction->register_c, instruction->register_c);
      break;
      case G_LD:
        fprintf(file_target_code, "011000%s%s;//Load m[#%d] to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->immediate, instruction->register_a);
      break;
      case G_ST:
        fprintf(file_target_code, "011001%s%s;//Store r[%d] in m[#%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a, instruction->immediate);
      break;
      case G_LDI:
        fprintf(file_target_code, "011010%s%s;//Loadi #%d to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->immediate, instruction->register_a);
      break;
      case G_IN:
        fprintf(file_target_code, "011101%s%s;//Input to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a);
      break;
      case G_HLT:
        fprintf(file_target_code, "forgot %d\n", instruction->type);
      break;
      case G_POUT:
        fprintf(file_target_code, "011110%s%s;//Pre Output r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a);
      break;
      case G_OUT:
        fprintf(file_target_code, "100000%s%s;//Output r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->immediate, 21),
        instruction->register_a);
      break;
      case G_LDR:
        fprintf(file_target_code, "100001%s%s%s;//Loadr m[r[%d]] to r[%d]\n",

        decimal_to_binary(instruction->register_a, 5),
        decimal_to_binary(instruction->register_c, 5),
        decimal_to_binary(instruction->immediate, 16),
        instruction->register_a, instruction->register_c);
      break;
      case G_STR:
        fprintf(file_target_code, "100010%s%s%s;//Storer to r[%d] in m[r[%d]] \n",

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

  fprintf(file_target_code, "\n\t \t firstClock <= 0;\n");
  fprintf(file_target_code, "\t \t end\n");
  fprintf(file_target_code, "\t end\n\n");
  fprintf(file_target_code, "\t assign iRAMOutput = instructionsRAM[address];\n");
  fprintf(file_target_code, "endmodule // simpleInstructionsRAM\n");

  fclose( file_target_code );
}
