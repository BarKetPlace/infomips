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


int resumecmd(interpreteur inter, mem memory, registre *reg)
{
		inter->mode=DEBUG_MODE;
		return cmd_ok;
}
