#ifndef fct_h
#define fct_h

#include "mem.h"
#include "elf.h"
#include "emulateur.h"
#include "reg.h"
#include "dico.h"

#define max_inst 0xffffffff

int fct_add(inst i, registre* regs);
int fct_sw(inst i, registre* regs);
int fct_subu(inst i, registre* regs);
int fct_sub(inst i, registre* regs);
int fct_srl(inst i, registre* regs);
int fct_sra(inst i, registre* regs);
int fct_sltu(inst i, registre* regs);
int fct_add(inst i, registre* regs);
int fct_slti(inst i, registre* regs);
int fct_slt(inst i, registre* regs);
int fct_sll(inst i, registre* regs);
int fct_ori(inst i, registre* regs);
int fct_or(inst i, registre* regs);
int fct_mflo(inst i, registre* regs);
int fct_mfhi(inst i, registre* regs);
int fct_lw(inst i, registre* regs);
int fct_lui(inst i, registre* regs);
int fct_div(inst i, registre* regs);
int fct_bne(inst i, registre* regs);
int fct_bltz(inst i, registre* regs);
int fct_bgtz(inst i, registre* regs);
int fct_bglz(inst i, registre* regs);
int fct_bgez(inst i, registre* regs);
int fct_beq(inst i, registre* regs);
int fct_andi(inst i, registre* regs);
int fct_and(inst i, registre* regs);
int fct_addu(inst i, registre* regs);
int fct_addiu(inst i, registre* regs);
int fct_addi(inst i, registre* regs);
int fct_mult(inst i, registre* regs);
int fct_syscall(inst i, registre* regs);
int fct_j(inst i, registre* regs);
int fct_jal(inst i, registre* regs);
int fct_jalr(inst i, registre* regs);
int fct_jr(inst i, registre* regs);
int fct_break(inst i, registre* regs);
int fct_lbu(inst i, registre* regs);
int fct_sb(inst i, registre* regs);
int fct_lui(inst i, registre* regs);
int fct_seb(inst i, registre* regs);
int fct_nop(inst i, registre* regs);
int fct_move(inst i, registre* regs);
int fct_neg(inst i, registre* regs);
int fct_li(inst i, registre* regs);
int fct_blt(inst i, registre* regs);





#endif
