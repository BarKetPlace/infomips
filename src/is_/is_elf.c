#include <stdlib.h>
#include <stdio.h>

#include "notify.h"
#include "is_.h"
#include "elf.h"


int is_elf(char* fichier, FILE* felf)
{	
	if (!assert_elf_file(felf)) //Le fichier est il un fichier elf
	{
		WARNING_MSG("file '%s' is not an ELF file", fichier);
		return cmd_exit;
	}
	return cmd_ok;
}
