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


int loadcmd(char* fichier, mem memory, registre* reg)
{
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Chargement de la mémoire /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
	FILE* felf;
	segment* seg=NULL;
	 unsigned int next_segment_start = START_MEM; // compteur pour designer le début de la prochaine section
	 int i,j;
	//Info machine
	 unsigned int type_machine;
	 unsigned int endianness;   //little ou big endian
	 unsigned int bus_width;    // 32 bits ou 64bits
	 //Table des symboles
	 stab symtab= new_stab(0);
	 //Sections possibles
	 char* section_names[NB_SECTIONS]= {TEXT_SECTION_STR,RODATA_SECTION_STR,DATA_SECTION_STR,BSS_SECTION_STR};
	 unsigned int segment_permissions[NB_SECTIONS]= {R_X,R__,RW_,RW_};


	//Ouverture du fichier elf
	if (   (felf = fopen(fichier, "r") ) == NULL  )
	{
		ERROR_MSG(" Impossible d'ouvrir %s \n", fichier);
		return NULL;
	}
	//On vérifie que le nombre d'argument est correct et que le fichier est bien un fichier elf
	if ( !(is_elf(fichier,  felf)) ) 
	{	ERROR_MSG("Attention, le fichier n'est pas un fichier elf");
		return CMD_UNKOWN_RETURN_VALUE;
	}
	//DEBUG_MSG("ok");
	//On récupère les informations sur la machine
	elf_get_arch_info(felf, &type_machine, &endianness, &bus_width);
	// et des symboles
	elf_load_symtab(felf, bus_width, endianness, &symtab);


	uint nsegments=0;
	nsegments = get_nsegments(symtab,section_names,NB_SECTIONS);

	  // initialiser la memoire virtuelle
	    if (!init_mem(nsegments, reg, memory)) {
			WARNING_MSG("Erreur d'initialisation de la mémoire");
			return 0;
		}
		
	    // Ne pas oublier d'allouer les differentes sections
	    j=0;
	    for (i=0; i<NB_SECTIONS; i++) {
	        if (is_in_symbols(section_names[i],symtab)) {
	            elf_load_section_in_memory(felf,memory, section_names[i],segment_permissions[i],next_segment_start);
	            next_segment_start+= (((memory)->seg[j].size._32+0x1000)>>12 )<<12; // on arrondit au 1k suppérieur
	            //print_segment_raw_content(&memory->seg[j]);
	            j++;
	        }
	    }
	
	if(!(init_tab_mem(memory))) WARNING_MSG("Problème de recopie de la mémoire");
	INFO_MSG("Programme chargé en mémoire avec succés");
	//print_mem( memory );
	
	//printf("\n\n");

	return 1;
}
