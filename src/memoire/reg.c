#include <strings.h>
#include <string.h>

#include "reg.h"
#include "mem.h"
#include "notify.h"

/* 0->31 : registre généraux voir p 10
 * 32 : registre pc
 * 33 et 34 : HI et LO
 */



registre* alloue_reg(void)
{	registre* reg=NULL;
	if( (reg = calloc(NBREG, sizeof(*reg)) )==NULL ) 
	{
		ERROR_MSG("Erreur allocation registres");
	}
	return reg;
}

int init_reg(registre* reg)
{
	
	//attention registre v1 en double
	char * reg_str[]={"zero","at","v0","v1","a0","a1","a2","a3","t0","t1",
			"t2","t3","t4","t5","t6","t7","s0","s1","s2","s3","s4","s5",
			"s6","s7","t8","t9","k0","k1","gp","sp","fp","ra","pc","HI","LO"};

	int i=0;

	for (i =0;i<NBREG;i++)
	{
		strcpy(reg[i].nom,reg_str[i]);		
		reg[i].val=0; 
	}
	//INFO_MSG("Registres chargés avec succès");
	return 1;
	
}
int del_reg(registre* reg)
{
	free(reg);
	return 1;
}




void print_tab_reg(registre* reg)
{
	int i=0;
	while (i<NBREG)
	{
		printf("%s\t: 0x%08x\t",reg[i].nom,reg[i].val); i++;
		printf("%s\t: 0x%08x\t",reg[i].nom,reg[i].val); i++;
		printf("%s\t: 0x%08x\t",reg[i].nom,reg[i].val); i++;
		if(i==NBREG) {printf("\n");break;}
		printf("%s\t: 0x%08x\n",reg[i].nom,reg[i].val); i++;
	}

}

int print_reg(registre* reg, int i)
{
	if(i==-1) {return i;}
	else{
		printf("%s\t0x%08x\n",reg[i].nom,reg[i].val);
	}
}


int nom_indice(char* nom)
{
		
}

int transf_reg(registre *reg, char* nom_reg )
{
	int i;
	for(i=0;i<NBREG;i++)
	{
		//puts(reg[i].nom);
		//puts(nom_reg+1);
		if (!strcmp(reg[i].nom,nom_reg+1) ) {return i;}
	}	
	return -1;
}
