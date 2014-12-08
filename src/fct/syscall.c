#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"

#include "fct.h"
#include "dico.h"

#include "typesmem.h"




// Fonction SYSCALL


int fct_syscall(inst k, mem memory, registre* reg)
{ //DEBUG_MSG("");	
  char lecture[MAX_STR];
	uint32_t entierlu;
	int i;
	//DEBUG_MSG("%d",reg[2].val);
	switch(reg[2].val){
		case 1: 
			printf("SYSCALL %d :: %d\n",reg[2].val, reg[4].val); break;
		case 4:
			printf("SYSCALL %d :: %s\n",reg[2].val, reg[4].val); break;
		case 5:
			printf("SYSCALL %d :: ", reg[2].val);
			scanf("%s",&lecture);
			sscanf(lecture,"%d", &reg[2].val);printf("\n");
			break;
		case 8:
			printf("SYSCALL %d :: ", reg[2].val);
			scanf("%s",&lecture);
			for (i=0;i<reg[5].val;i++) ;
			break;
		
		case 10: exit(0);
			break;
	default: return cmd_unknown;
	}
	reg[PC].val+=4;
	return cmd_ok;
}
