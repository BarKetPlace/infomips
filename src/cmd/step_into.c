#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "mem.h"
#include "notify.h"
#include "bits.h"
#include "formats.h"
#include "types.h"
#include "syms.h"
#include "section.h"
#include "reg.h"
#include "is_.h"
#include "dico.h"


int step_intocmd(mem memory, registre* reg, Liste dico)
{	
	uint32_t val;
	int tmp;
	definition def = NULL;
	tmp =find_word(memory, reg[PC].val, &val);
	inst mot;

	if ( tmp == cmd_unknown ) return tmp;
	
	mot.code=val;	
	

	def = find_def(dico, mot);

	//DEBUG_MSG("");
	if (!def)  {//Si def == NULL
		printf("\n");
		WARNING_MSG(" Instruction inconnue ");
		return cmd_exit;
		}
	//DEBUG_MSG("");
	tmp = fct_exec(reg[PC].val, memory, reg, dico);
	if ( tmp != cmd_ok ) return tmp;
	//detail_def(def);

	//def->f(mot, reg);
	reg[PC].val += 4;

	return cmd_ok;

}
