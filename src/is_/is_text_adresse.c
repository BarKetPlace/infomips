#include <string.h>
#include "mem.h"
#include "emulateur.h"


int is_text_adresse(mem memory, uint32_t adresse, uint32_t* text_start, uint32_t* text_taille)
{	
	int i, taille, start;
	segment* seg = NULL;
	
	for (i=0;i<memory->nseg;i++) {
		seg = memory->seg+i;
		taille = seg->size._32;
		start = seg->start._32;
		if (!strcmp(seg->name,".text")) break;
	}
	*text_start = start;
	*text_taille = taille;
	if (adresse > start + taille || adresse < start) return cmd_unknown;
	
	
	return cmd_ok;
}
