
#include <strings.h>
#include <string.h>

#include "mem.h"
#include "reg.h"
#include "bits.h"
#include "notify.h"
#include "emulateur.h"







// Definition des pointeurs de fonctions

typedef struct {
	int (*fonction)(interpreteur inter,inst,memory mem,registre* reg)
		}



