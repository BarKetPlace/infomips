#ifndef fct_h
#define fct_h

#include "mem.h"
#include "elf.h"
#include "emulateur.h"
#include "reg.h"
#include "dico.h"

#define max_inst 0xffffffff

int fct_add(inst k, virtualmem vm);
int fct_sw(inst k, virtualmem vm);
int fct_subu(inst k, virtualmem vm);
int fct_sub(inst k, virtualmem vm);
int fct_srl(inst k, virtualmem vm);
int fct_sra(inst k, virtualmem vm);
int fct_sltu(inst k, virtualmem vm);
int fct_slti(inst k, virtualmem vm);
int fct_slt(inst k, virtualmem vm);
int fct_sll(inst k, virtualmem vm);
int fct_ori(inst k, virtualmem vm);
int fct_or(inst k, virtualmem vm);
int fct_mflo(inst k, virtualmem vm);
int fct_mfhi(inst k, virtualmem vm);
int fct_lw(inst k, virtualmem vm);
int fct_lui(inst k, virtualmem vm);
int fct_div(inst k, virtualmem vm);
int fct_bne(inst k, virtualmem vm);
int fct_bltz(inst k, virtualmem vm);
int fct_bgtz(inst k, virtualmem vm);
int fct_bglz(inst k, virtualmem vm);
int fct_bgez(inst k, virtualmem vm);
int fct_beq(inst k, virtualmem vm);
int fct_andi(inst k, virtualmem vm);
int fct_and(inst k, virtualmem vm);
int fct_addu(inst k, virtualmem vm);
int fct_addiu(inst k, virtualmem vm);
int fct_addi(inst k, virtualmem vm);
int fct_mult(inst k, virtualmem vm);
int fct_syscall(inst k, virtualmem vm);
int fct_j(inst k, virtualmem vm);
int fct_jal(inst k, virtualmem vm);
int fct_jalr(inst k, virtualmem vm);
int fct_jr(inst k, virtualmem vm);
int fct_break(inst k, virtualmem vm);
int fct_lbu(inst k, virtualmem vm);
int fct_sb(inst k, virtualmem vm);

int fct_seb(inst k, virtualmem vm);
int fct_nop(inst k, virtualmem vm);
int fct_move(inst k, virtualmem vm);
int fct_neg(inst k, virtualmem vm);
int fct_li(inst k, virtualmem vm);
int fct_blt(inst k, virtualmem vm);
int fct_exec(uint32_t adresse, virtualmem vm);




#endif
