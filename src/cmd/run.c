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


int runcmd(interpreteur inter, mem memory, registre* reg, Liste dico)
{
	char* token;
	int start = START_MEM;
	token = get_next_token(inter);
	
	if (token && is_hexa(token)) {
		sscanf(token, "%x", &start);
	}
	reg[pc] = start;
		
	while(1) {	
	disasm_(memory, reg, reg[pc], reg[pc], dico);

	}
	
	return cmd_ok;
}
