#ifndef REG_H_
#define REG_H_

#define NBREG 35
#define PC 32
#define HI 33
#define LO 34
#define a0 4
#define a1 5

#include "notify.h"
#include "types.h"

typedef struct {
	word val;
	char nom[6];
} registre;
/*
typedef enum {zero, at, v0, v1, a0,a1,a2,a3,t0,t1,t2,t3,t4,t5,t6,t7,s0,s1,s2,s3,s4,s5,s6,s7,t8,t9,k0,k1,gp,sp,fp,ra,pc,HI,LO} reg_nom;
*/



registre* alloue_reg(void);
int init_reg(registre* reg);
int del_reg (registre* reg);
void print_tab_reg(registre* reg);
int print_reg(registre* reg, int i);
int is_registre(char* chaine);
int transf_reg(registre *reg, char* nom_reg );

#endif
