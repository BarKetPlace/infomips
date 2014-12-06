#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "syms.h"
#include "bits.h"
#include "elf.h"
#include "notify.h"
#include "emulateur.h"
#include "relocator.h"

int ajout_pile( mem memory, registre *reg, uint32_t ajout );

int enleve_pile( mem memory, registre *reg, uint32_t* res );

int visualiser_pile( mem memory, registre *reg );
