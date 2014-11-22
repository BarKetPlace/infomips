#ifndef typesmem_
#define typesmem_


#include "mem.h"
#include "reg.h"
#include "dico.h"


typedef struct {
	mem memory;
	registre* reg;
	Liste dico;
}* virtualmem;


#endif
