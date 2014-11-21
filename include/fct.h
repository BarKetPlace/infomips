#ifndef fct_h
#define fct_h

#include "mem.h"
#include "elf.h"
#include "emulateur.h"
#include "reg.h"
#include "dico.h"

#define max_inst 0xffffffff

int fct_add(inst k, mem memory, registre* regs);
int fct_sw(inst k, mem memory, registre* regs);
int fct_subu(inst k, mem memory, registre* regs);
int fct_sub(inst k, mem memory, registre* regs);
int fct_srl(inst k, mem memory, registre* regs);
int fct_sra(inst k, mem memory, registre* regs);
int fct_sltu(inst k, mem memory, registre* regs);
int fct_add(inst k, mem memory, registre* regs);
int fct_slti(inst k, mem memory, registre* regs);
int fct_slt(inst k, mem memory, registre* regs);
int fct_sll(inst k, mem memory, registre* regs);
int fct_ori(inst k, mem memory, registre* regs);
int fct_or(inst k, mem memory, registre* regs);
int fct_mflo(inst k, mem memory, registre* regs);
int fct_mfhi(inst k, mem memory, registre* regs);
int fct_lw(inst k, mem memory, registre* regs);
int fct_lui(inst k, mem memory, registre* regs);
int fct_div(inst k, mem memory, registre* regs);
int fct_bne(inst k, mem memory, registre* regs);
int fct_bltz(inst k, mem memory, registre* regs);
int fct_bgtz(inst k, mem memory, registre* regs);
int fct_bglz(inst k, mem memory, registre* regs);
int fct_bgez(inst k, mem memory, registre* regs);
int fct_beq(inst k, mem memory, registre* regs);
int fct_andi(inst k, mem memory, registre* regs);
int fct_and(inst k, mem memory, registre* regs);
int fct_addu(inst k, mem memory, registre* regs);
int fct_addiu(inst k, mem memory, registre* regs);
int fct_addi(inst k, mem memory, registre* regs);
int fct_mult(inst k, mem memory, registre* regs);
int fct_syscall(inst k, mem memory, registre* regs);
int fct_j(inst k, mem memory, registre* regs);
int fct_jal(inst k, mem memory, registre* regs);
int fct_jalr(inst k, mem memory, registre* regs);
int fct_jr(inst k, mem memory, registre* regs);
int fct_break(inst k, mem memory, registre* regs);
int fct_lbu(inst k, mem memory, registre* regs);
int fct_sb(inst k, mem memory, registre* regs);
int fct_lui(inst k, mem memory, registre* regs);
int fct_seb(inst k, mem memory, registre* regs);
int fct_nop(inst k, mem memory, registre* regs);
int fct_move(inst k, mem memory, registre* regs);
int fct_neg(inst k, mem memory, registre* regs);
int fct_li(inst k, mem memory, registre* regs);
int fct_blt(inst k, mem memory, registre* regs);





#endif
