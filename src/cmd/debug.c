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
#include "emulateur.h"


int debugcmd(interpreteur inter, mem memory, registre *reg)
{
		inter->mode=INTERACTIF;
	
		return cmd_ok;
}
	

