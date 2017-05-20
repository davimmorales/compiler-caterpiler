
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

typedef enum{
    /* Adição  000000 &*/ ADD, // R[DR] <- R[SA] + R[SB]
  /* Adição Imediato  000001 &*/ ADDI, // R[DR] <- R[SA] + IM
  /* Subtração  000010 &*/ SUB, // R[DR] <- R[SA] + \overline{R[SB]} + 1
  /* Subtração Imediato  000011 &*/ SUBI, // R[DR] <- R[SA] + \overline{IM} + 1
  /* Multiplicação  000100 &*/ MUL, // R[DR] <- R[SA] * R[SB]
  /* Divisão  000101 &*/ DIV, // R[DR] <- R[SA] / R[SB]
  /* Incrementa  000110 &*/ INC, // R[DR] <- R[SA] + 1
  /* Decrementa  000111 &*/ DEC, // R[DR] <- R[SA] - 1
  /* And  001000 &*/ AND, // R[DR] <- R[SA] \wedge R[SB]
  /* Or  001001 &*/ OR, // R[DR] <- R[SA] \vee R[SB]
  /* Resto  001010 &*/ MOD, // R[DR] <- R[SA] \% R[SB]
  /* Xor  001100 &*/ XOR, // R[DR] <- R[SA] \bigoplus R[SB]
  /* Not  001101 &*/ NOT, // R[DR] <- \overline{R[SA]}
  /* Desloca Esquerda  010000 &*/ SHL, // R[DR] <- sl (shamt)R[SA]
  /* Desloca Direita  010001 &*/ SHR, // R[DR] <- sr (shamt)R[SA]
  /* Pré-branch  011111 &*/ PBC, // se R[SA] = 0, FZ = 1;  se R[SA] < 0, FN = 1;
  /* Branch em Zero  010011 &*/ BOZ, // se FZ = 1, então PC <- PC + 1 + IM e FZ = 0, então PC <- PC + 1
  /* Branch em Negativo  010100 &*/ BON, // se FN = 1, então PC <- PC + IM e FN = 0, então PC <- PC + 1
  /* Jump  010101 &*/ JMP, // PC <- IM
  /* Set on Less Than  010111 &*/ SLT, // se R[SA] < R[SB], então R[DR] <- 1
  /* Load  011000 &*/ LD, // R[DR] <- M[IM]
  /* Store  011001 &*/ ST, // M[IM] <- R[SA]
  /* Load Imediato  011010 &*/ LDI, // R[DR] <- IM
  /* Nop  011011 &*/ NOP, // Sem Operação
  /* Entrada  011101 &*/ IN, // R[DR] <- alavancas
  /* HLT  011100 &*/ HLT, // Parar Operação
  /* Saída  011110 &*/ OUT // Displays <- R[SA]
}galetype;


//numbers relate to amount of registers in the operation
void format_zero(galetype type, int immediate);

void format_one(galetype type, int register_a, int immediate);

void format_two(galetype type, int register_source, int register_target, int immediate);

void format_three(galetype type, int register_source_a, int register_source_b, int register_target);


















#endif
