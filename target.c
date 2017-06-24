#include "object.h"

void print_target_code(list_instructions *instructions_list){
  file_target_code = fopen("target_code.gc", "w");

  type_instruction *instruction = instructions_list->start;

  while (instruction!=NULL) {
    switch (instruction->type) {
      case G_ADD:
      break;
      case G_ADDI:
      break;
      case G_SUB:
      break;
      case G_SUBI:
      break;
      case G_MUL:
      break;
      case G_DIV:
      break;
      case G_INC:
      break;
      case G_DEC:
      break;
      case G_AND:
      break;
      case G_OR:
      break;
      case G_MOD:
      break;
      case G_XOR:
      break;
      case G_NOT:
      break;
      case G_SHL:
      break;
      case G_SHR:
      break;
      case G_PBC:
      break;
      case G_BOZ:
      break;
      case G_BON:
      break;
      case G_JMP:
      break;
      case G_SLT:
      break;
      case G_LD:
      break;
      case G_ST:
      break;
      case G_LDI:
      break;
      case G_NOP:
      break;
      case G_IN:
      break;
      case G_HLT:
      break;
      case G_POUT:
      break;
      case G_OUT:
      break;
      case G_LDR:
      break;
      case G_STR:
      break;
      default:
        printf("Galetype Unknown: %d\n", instruction->type);
      break;
    }
    instruction = instruction->next;
  }

  fclose( file_target_code );
}
