/**
 * @file mem.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Nov  1 01:37:19 2013
 * @brief Memory.
 *
 * Memory.
 */

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
// strdup is defined in the string.h header but included only for glibc >=2.12.
// the following declaration bypasses the version declaration
char *strdup( const char * );


/**
 * Creates a virtual memory and performs the necessary memory allocations
 * @param size  the number of segments that composes this virtual memory
 * @return the new allocated virtual memory or NULL in case of failure
 */

mem alloue_mem(void)
{
	mem vm = calloc( 1, sizeof( *vm ) );
	return vm;
}

int init_mem( uint32_t nseg, registre* reg, mem vm ) {

    

    if ( NULL == vm ) {
        WARNING_MSG( "Unable to allocate host memory for vmem" );
        return 0;
    }
    else {
        uint i;

        vm->seg = calloc( nseg+1, sizeof( *(vm->seg) ) );
        if ( NULL == vm->seg ) {
            WARNING_MSG( "Unable to allocate host memory for vmem segment" );
            free( vm );
            return 0;
        }

        // each segment is initialised to a null value
        // Note that though this is unnecessary since a calloc is used
        // this permits future evolution of the default initialisation values
        for ( i= 0; i< nseg+1; i++ ) {
            vm->seg[i].name      = NULL;
            vm->seg[i].content   = NULL;
            vm->seg[i].start._64 = 0x0;
            vm->seg[i].size._64  = 0x0;
            vm->seg[i].attr      = 0x0;
        }
        vm->nseg = nseg+1;
		WARNING_MSG("Chargement de la pile");
		if (!init_stack(vm, reg, nseg))
		{
			ERROR_MSG("Erreur lors du chargement de la pile");
    	}
		INFO_MSG("Pile initialisée");
	}
	vm->start_mem = 0;
    return 1;

}

/**
 * allocates an available segment in the virtual memory to the section named 'name'.
 * @param name the name of the segment (e.g., ".text", ".data"...)
 * @param attribute an integer value corresponding to the access and execution permissions of the segment (@see mem.h)
 * @return 0 in case of success, a non null value otherwise
 */
int attach_scn_to_mem( mem vm, char *name, uint32_t attr ) {

    if ( NULL != vm ) {
        uint i;

        for ( i= 0; i< vm->nseg; i++ ) {
            if ( NULL == vm->seg[i].name ) {
                vm->seg[i].attr = attr;
                vm->seg[i].name = strdup( name );
                return 0;
            }
        }

        WARNING_MSG( "All vmem segments already allocated" );
        return 1;
    }
    else {
        WARNING_MSG( "Virtual memory not initialized" );
        return 1;
    }
}

/**
 * Sets a segment with all the information about a section read from a ELF file
 * @param vm the virtual memory in which the segment to fill in can be found
 * @param name the name of the segment to look for (e.g., ".text", ".data"...)
 * @param size the size of the section content (in bytes)
 * @param start the virtual address in the virtual memory at which the beginning of the segment is located
 * @param content the real address at which the bytes of the section is located
 * @return 0 if succeed, a non null value otherwise
 */

int fill_mem_scn( mem vm, char *name, vsize sz, vaddr start, byte *content ) {

    if ( NULL != vm ) {
        uint i;

        for ( i= 0; i< vm->nseg; i++ ) {
            if ( 0 == strncasecmp( vm->seg[i].name, name, strlen(name) ) ) {
                switch( SCN_WIDTH( vm->seg[i].attr ) ) {
                case 32 :
                    vm->seg[i].size._32 = sz._32;
                    vm->seg[i].start._32 = start._32;
                    vm->seg[i].content = calloc( 1, sz._32 );
                    if ( NULL == vm->seg[i].content ) {
                        WARNING_MSG( "Unable to allocate host memory for vmem segment %s content", name );
                        vm->seg[i].size._32 = 0;
                        vm->seg[i].start._32 = 0;
                        return 1;
                    }
                    if ( NULL != content ) {
                        memcpy( vm->seg[i].content, content, sz._32 );
                    }
                    return 0;
                    break;
                case 64 :
                    vm->seg[i].size._64 = sz._64;
                    vm->seg[i].start._64 = start._64;
                    vm->seg[i].content = calloc( 1, sz._64 );
                    if ( NULL == vm->seg[i].content ) {
                        WARNING_MSG( "Unable to allocate host memory for vmem segment %s content", name );
                        vm->seg[i].size._64 = 0;
                        vm->seg[i].start._64 = 0;
                        return 1;
                    }
                    if ( NULL != content ) {
                        memcpy( vm->seg[i].content, content, sz._64 );
                    }
                    return 0;
                    break;
                default :
                    WARNING_MSG( "Wrong width" );
                    return 1;
                }
                return 0;
            }
        }

        WARNING_MSG( "Segment %s not attached yet", name );
        return 1;
    }
    else {
        WARNING_MSG( "Virtual memory not initialized" );
        return 1;
    }
}


/**
* prints the content of a virtual memory
* @param a virtual memory
*/
/*
int tab_mem(mem memory)
{	int i,k,word;
	int cpt=0;
	segment segm;
	//printf("%d\n",memory->nseg);
	for (i=0; i<memory->nseg-1; i++)
	{	//printf("\n%d\n", (*(memory->seg+i)).size._32);
		
		//print_segment_raw_content(memory->seg+i);printf("\n");

		
		for (k=0;k<(*(memory->seg+i)).size._32;k+=4)
		{	
			//printf("0x%08x\n", *(  (unsigned int *) (  *(memory->seg+i)->content+k  )     ) );

	 		word = *((unsigned int *) ((memory->seg+i)->content+k));
            FLIP_ENDIANNESS(word);
            //printf("%08x\n",	word);

			(memory->tab)[cpt] = word ;
			cpt+=4;

		}
		
	}
	return 1;
}
*/
void build_rel_table(char* reloc_name, Elf32_Rel* rel, uint32_t scnsz) {
  
}


void print_rel_table(char* reloc_name, Elf32_Rel* rel, uint32_t scnsz) {
  uint j;
  printf("Table de relocation : %s\n",reloc_name);
  printf("Offset\tInfo\tType\tVal.-syms\n");
  word offset = 0, info = 0;
  
  for(j=0;j<scnsz/sizeof(*rel);j++)
    {
      offset = swap_mot(rel[j].r_offset);
      info = swap_mot(rel[j].r_info);

      printf("%x\t%x\t%s\n",offset,info,MIPS32_REL[(info&0xff)]);
    }
}

uint32_t find_sec_start(mem memory, char* name ) {
  int i;
  for (i=0; i<memory->nseg; i++) {
    if ( ! strcmp(memory->seg[i].name, name) ) return memory->seg[i].start._32;
  }
  ERROR_MSG("impossible de l'adresse de depart de %s", name);
}

/*--------------------------------------------------------------------------  */
/**
 * @param fp le fichier elf original
 * @param seg le segment à reloger
 * @param mem l'ensemble des segments
 *
 * @brief Cette fonction effectue la relocation du segment passé en parametres
 * @brief l'ensemble des segments doit déjà avoir été chargé en memoire.
 *
 * VOUS DEVEZ COMPLETER CETTE FONCTION POUR METTRE EN OEUVRE LA RELOCATION !!
 */
void reloc_segment(FILE* fp, segment seg, mem memory,unsigned int endianness,stab symtab) {
    byte *ehdr    = __elf_get_ehdr( fp );
    uint32_t  scnsz  = 0;
    Elf32_Rel *rel = NULL;
    char* reloc_name = malloc(strlen(seg.name)+strlen(RELOC_PREFIX_STR)+1);
    scntab section_tab;

    // on recompose le nom de la section
    memcpy(reloc_name,RELOC_PREFIX_STR,strlen(RELOC_PREFIX_STR)+1);
    strcat(reloc_name,seg.name);

    // on récupere le tableau de relocation et la table des sections
    rel = (Elf32_Rel *)elf_extract_scn_by_name( ehdr, fp, reloc_name, &scnsz, NULL );
    elf_load_scntab(fp ,32, &section_tab);



    if (rel != NULL &&seg.content!=NULL && seg.size._32!=0) {

        INFO_MSG("--------------Relocation de %s-------------------\n",seg.name) ;
        INFO_MSG("Nombre de symboles a reloger: %ld\n",scnsz/sizeof(*rel)) ;
	int j,k;
	uint32_t info=0, offset=0, type_rel=0, nb_symb=0;

	uint32_t needed_sec_start;
        char* needed_sec_name;
	uint32_t inst_HI, inst_LO;
	
	uint32_t rel_inst;
	word word_rel;
	print_rel_table(reloc_name, rel, scnsz);
	for(j=0;j<scnsz/sizeof(*rel);j++)
	  {
	    
	    offset = swap_mot(rel[j].r_offset);
	    info = swap_mot(rel[j].r_info);
	    type_rel = (info&0xff);
	    //DEBUG_MSG("%x",( info&0xffffff00)>>8 );
	    needed_sec_name = strdup(symtab.sym[( (info&0xffffff00)>>8 ) ].name);

	    needed_sec_start = find_sec_start(memory, needed_sec_name);

	    //DEBUG_MSG("%x",needed_sec_start);


	    switch(type_rel){
	    case R_MIPS_26: // Branchement
	      find_word(memory, needed_sec_start+offset, &word_rel);
	      nb_symb = (word_rel&0x03ffffff);
	      //DEBUG_MSG("%d", nb_symb);
	      //DEBUG_MSG("%x",symtab.sym[nb_symb+1].addr._32);
	      //sym32_print(symtab.sym[nb_symb+1]); 
	      word_rel = (word_rel&0xfc000000) + symtab.sym[nb_symb+1].addr._32;
	      
	      load_word(memory, needed_sec_start+offset, swap_mot(word_rel));

	      break;
	      
	    case R_MIPS_HI16: 
	      DEBUG_MSG("hi16");
	      //DEBUG_MSG("offset :: %x\tinfo :: %x\n",offset,info);
	      // On va chercher les 16 bits de poids fort de l'adresse @+offset
	      find_word(memory, seg.start._32+offset, &inst_HI);
	      //DEBUG_MSG("%x",word_rel);

	      inst_HI = inst_HI&0xffff0000;
	      break;
	      
	   
	    case R_MIPS_LO16: DEBUG_MSG("lo16");
	      //On charge le mot à l'adresse P
	      find_word(memory, seg.start._32+offset+4, &inst_LO);
	      //On extrait les 16 derniers bits
	      inst_LO = inst_LO&0x0000ffff;
	      //On concatène les deux pour reconstituer l'instruction à reloger
	      rel_inst = inst_HI + inst_LO;
	      //DEBUG_MSG("%x",rel_inst);
	      //On va chercher le numéro du symbole dans la table de symboles
	      nb_symb = (rel_inst&0x0000ffff);
	      // DEBUG_MSG("%x", nb_symb);
	      //On place dans word_rel la valeur du mot après relocation
	      word_rel = needed_sec_start + symtab.sym[nb_symb].addr._32;
	      //DEBUG_MSG("word_rel :: %08x",word_rel);
	      //On reloge l'adresse en la coupant en deux :: les bits de poids fort sur les poids faibles de la première
	      // Les bits de poids faible sur les poids faible de la deuxième 
	        //Première partie
	      find_word(memory, seg.start._32+offset-4, &rel_inst);
	      rel_inst= rel_inst&0xffff0000 + ((word_rel&0xffff0000)>>16) ;
	      load_word(memory, seg.start._32+offset-4, swap_mot(rel_inst)   );

	        //Deuxième partie
	      find_word(memory, seg.start._32+offset, &rel_inst);
	      //DEBUG_MSG("%x",rel_inst);
	      rel_inst= (rel_inst&0xffff0000) + (word_rel&0x0000ffff) ;
	      //DEBUG_MSG("%x", word_rel&0x0000ffff);
	      load_word(memory, seg.start._32+offset,  swap_mot(rel_inst));
	      break;
	    case R_MIPS_32: break;
	    }
	    
	    
	  }


        //------------------------------------------------------

        //TODO : faire la relocation ICI !

        //------------------------------------------------------

    }
    del_scntab(section_tab);
    free( rel );
    free( reloc_name );
    free( ehdr );

}



void print_mem( mem vm ) {
    if ( NULL != vm ) {
        uint i;
        uint n = 0;

        for ( i= 0; i< vm->nseg; i++ ) {
            if ( UNDEF != SCN_RIGHTS( vm->seg[i].attr ) ) {
                n++;
            }
        }

        printf( "Virtual memory map (%u segments)\n", n );

        for ( i= 0; i< vm->nseg; i++ ) {

            if ( UNDEF == SCN_RIGHTS( vm->seg[i].attr ) ) {
                continue;
            }

            printf( "%-8s\t", vm->seg[i].name );
            switch( SCN_RIGHTS( vm->seg[i].attr ) ) {
            case R__ :
                printf( "r--" );
                break;
            case RW_ :
                printf( "rw-" );
                break;
            case R_X :
                printf( "r-x" );
                break;
            default :
                printf( "???" );
            }
            printf( "\tVaddr: " );
            switch( SCN_WIDTH( vm->seg[i].attr ) ) {
            case 32 :
                printf( "0x%08x", vm->seg[i].start._32 );
                break;
            case 64 :
                printf( "0x%016lx", (long unsigned int)vm->seg[i].start._64 );
                break;
            default :
                printf( "?????????" );
                break;
            }
            printf( "\tSize: " );
            switch( SCN_WIDTH( vm->seg[i].attr ) ) {
            case 32 :
                printf( "%u", vm->seg[i].size._32 );
                break;
            case 64 :
                printf( "%lu", (long unsigned int)vm->seg[i].size._64 );
                break;
            default :
                printf( "?????????" );
                break;
            }
            printf( " bytes\n" );
            /*
            printf( " bytes\t(%s)\n", vm->seg[i].content==NULL?"empty":"filled" );
            */
        }
    }

    return;
}


/**
 * Destroys a virtual memory by making all the necessary free operations
 * @param a virtual memory
 */
int del_mem( mem vm ) {

    if ( NULL != vm ) {

        if ( NULL != vm->seg ) {
            uint i;

            for ( i= 0; i< vm->nseg; i++ ) {
                if ( NULL != vm->seg[i].content ) {
                    free( vm->seg[i].content );
                }
                if ( NULL != vm->seg[i].name ) {
                    free( vm->seg[i].name );
                }
            }

            free( vm->seg );
        }

        free( vm );
	return 1;
    }

    return 0;
}

int init_stack(mem vm, registre* reg, unsigned int nseg)
{	if (vm ==NULL)
	{	ERROR_MSG("Memoire virtuelle mal chargée\n");
		return 0;
	}

	vm->seg[nseg].name      = strdup("[STACK]");

        vm->seg[nseg].start._32 = 0xfffff000;
        vm->seg[nseg].size._32  = STACKSZ_BYTES;
        vm->seg[nseg].attr      = SCN_ATTR(1, RW_);
        vm->seg[nseg].content   = calloc(vm->seg[nseg].size._64,1);

	reg[29].val = vm->seg[nseg].start._32 ;
	//INFO_MSG("Pile chargée avec succès");
	return 1;
}

// fonction affichant les octets d'un segment sur la sortie standard
// parametres :
//   seg        : le segment de la mémoire virtuelle à afficher

void print_segment_raw_content(segment* seg) {
    uint k;
    int word =0;
    if (seg!=NULL && seg->size._32>0) {
        for(k=0; k<seg->size._32; k+=4) {
            if( k%16==0 ) printf("\n  0x%08x ",k);
            word = *((unsigned int *) (seg->content+k));
            FLIP_ENDIANNESS(word);
            printf("%08x ",	word);
        }
    }
}

/*int print_case_mem(mem memory,uint debut,uint fin)
{	//Gestion des erreurs :
	if (debut<memory->start_mem) 
	{
		WARNING_MSG("La memoire commence en 0x%08x",memory->start_mem);
		return cmd_unknown;
	}
	uint fin_memory = 0xff7ff000;
	if (fin>fin_memory)
	{	WARNING_MSG("La memoire termine en 0x%08x",fin_memory);
		return cmd_unknown;
	}
	//Si les adresses demandées sont correctes
	
	for(i=1;i<NB_SECTIONS;i++)
	if (debut >start < memory->start_mem+(memory->seg.size._64)
	{	printf("

	

	return cmd_ok;
}*/

int print_byte_mem(mem memory, uint32_t adr)
{
  int tmp;
  byte valb;
  
  tmp = find_byte(memory, adr, &valb);
  if (tmp==cmd_unknown)
    {	//printf("\n");
     
      return tmp;
    }
  else {
    printf("%02x ",valb);
    
  }
  return cmd_ok;
}


int print_case_mem(mem memory, uint debut_, uint fin_)
{
	uint i;
	uint debut=debut_;
	uint fin=fin_;
	//uint val=0, tmp;
	//uint adr=debut;
	//DEBUG_MSG("%x %x",debut,fin);
	//if (debut_%4!=0) debut = debut_ - (debut_%4);
	//if (fin_%4!=0) fin = fin_ -(fin_%4);

	//DEBUG_MSG("%x %x",debut,fin);
	
	printf("0x%08x :: ", debut);
	for (i=debut;i<fin;i++)
	  {	if (i%0x10==0 && i != debut ) printf("\n0x%08x :: ", i);
		//if (i%4==0) adr=i;
		
		//tmp = find_word(memory, adr, &val);
		//if (tmp==cmd_unknown) return tmp;
	    
	    if(print_byte_mem(memory, i)==cmd_unknown) return cmd_unknown;
	}
printf("\n");
//DEBUG_MSG("");
}

int find_word(mem memory, uint32_t adresse, uint32_t* res) {	
	//DEBUG_MSG("");
	uint i=0;
	uint taille;
	uint32_t word = 0;
	uint start =0;
	segment* seg =NULL;
	//DEBUG_MSG("%d",memory->nseg);
	
	if (adresse<memory->start_mem) ERROR_MSG("La memoire commence en 0x%08x",memory->start_mem);
	if (adresse>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);	

	//if (adresse%4 != 0) adresse = adresse - (adresse%4);
	//DEBUG_MSG("nb seg %d",memory->nseg);
	for ( i=0; i< memory->nseg;) {
		seg = memory->seg+i;
		taille = seg->size._32;
		start = seg->start._32;
		//DEBUG_MSG("seg %d starts : 0x%08x taille: %d byte(s)",i,start,taille);
		//DEBUG_MSG("faddr %d",faddr);
		
		//faddr = faddr - seg->start._32;

		if (adresse > start+taille) i++; 
		else if ( adresse < start ){
			//ERROR_MSG("L'adresse 0x%08x n'est pas allouee", adresse);
			break;
		}
		else
		{//DEBUG_MSG("");
			word = *((uint32_t *) (seg->content+adresse-start));
			FLIP_ENDIANNESS(word);
			*res = word;
			return cmd_ok;
		}
		
	}
	puts("");
	WARNING_MSG("L'adresse 0x%08x n'est pas allouee", adresse);
	
	return cmd_unknown;
}

int find_byte(mem memory, uint32_t adresse, uint8_t* res) {	
	//DEBUG_MSG("");
	uint i=0;
	uint taille;
	uint32_t word = 0;
	uint start =0;
	segment* seg =NULL;
	//DEBUG_MSG("%d",memory->nseg);
	
	if (adresse<memory->start_mem) ERROR_MSG("La memoire commence en 0x%08x",memory->start_mem);
	if (adresse>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);	

	//if (adresse%4 != 0) adresse = adresse - (adresse%4);
	//DEBUG_MSG("nb seg %d",memory->nseg);
	for ( i=0; i< memory->nseg;) {
		seg = memory->seg+i;
		taille = seg->size._32;
		start = seg->start._32;
		//DEBUG_MSG("seg %d starts : 0x%08x taille: %d byte(s)",i,start,taille);
		//DEBUG_MSG("faddr %d",faddr);
		
		//faddr = faddr - seg->start._32;

		if (adresse > start+taille) i++; 
		else if ( adresse < start ){
			//ERROR_MSG("L'adresse 0x%08x n'est pas allouee", adresse);
			break;
		}
		else
		{//DEBUG_MSG("");
			*res = *((uint8_t *) (seg->content+adresse-start));
			//FLIP_ENDIANNESS(word);
		        
			return cmd_ok;
		}
		
	}
	puts("");
	WARNING_MSG("L'adresse 0x%08x n'est pas allouee", adresse);
	
	return cmd_unknown;
}

	
//Charger un mot en mémoire, l'adresse fournie doit être multiple de 4
int load_word(mem memory, uint32_t adresse, uint32_t wordtoload){
	uint taille;
	uint start =0;
	segment* seg =NULL;
	uint i;
	if (adresse<memory->start_mem) ERROR_MSG("La memoire commence en 0x%08x",memory->start_mem);
	if (adresse>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);	

	//if (adresse%4 != 0) adresse = adresse - (adresse%4);
	//DEBUG_MSG("nb seg %d",memory->nseg);
	for ( i=0; i< memory->nseg;) {
		seg = memory->seg+i;
		taille = seg->size._32;
		start = seg->start._32;
		//DEBUG_MSG("seg %d starts : 0x%08x taille: %d byte(s)",i,start,taille);
		//DEBUG_MSG("faddr %d",faddr);
		
		//faddr = faddr - seg->start._32;

		if (adresse > start+taille) i++; 
		else if ( adresse < start ){
			//ERROR_MSG("L'adresse 0x%08x n'est pas allouee", adresse);
			break;
		}
		else
		{//DEBUG_MSG("");
			*( (uint32_t *) (seg->content+adresse-start)) = wordtoload;
			
			return cmd_ok;
		}
		
	}
	
	return cmd_ok;
}

int load_byte(mem memory, uint32_t adresse, byte bytetoload){
	uint taille;
	uint start =0;
	segment* seg =NULL;
	uint i;
	//L'adresse fournie est elle valide
	if (adresse<memory->start_mem) ERROR_MSG("La memoire commence en 0x%08x",memory->start_mem);
	if (adresse>STOP_MEM) ERROR_MSG("La memoire termine en 0x%08x",STOP_MEM);	
	
	//if (adresse%4 != 0) adresse = adresse - (adresse%4);
	//DEBUG_MSG("nb seg %d",memory->nseg);
	for ( i=0; i< memory->nseg;) {
		seg = memory->seg+i;
		taille = seg->size._32;
		start = seg->start._32;
		//DEBUG_MSG("seg %d starts : 0x%08x taille: %d byte(s)",i,start,taille);
		//DEBUG_MSG("faddr %d",faddr);
		
		//faddr = faddr - seg->start._32;

		if (adresse > start+taille) i++; 
		else if ( adresse < start ){
			//ERROR_MSG("L'adresse 0x%08x n'est pas allouee", adresse);
			break;
		}
		else
		{//DEBUG_MSG("");
			*((byte *) (seg->content+adresse-start)) = bytetoload;
			
			return cmd_ok;
		}
		
	}
	
	return cmd_ok;
}



// fonction permettant d'extraire une section du fichier ELF et de la chargée dans le segment du même nom
// parametres :
//   fp         : le pointeur du fichier ELF
//   memory     : la structure de mémoire virtuelle
//   scn        : le nom de la section à charger
//   permission : l'entier représentant les droits de lecture/ecriture/execution
//   add_start  : l'addresse virtuelle à laquelle la section doit être chargée
//
// retourne 0 en cas de succes, une valeur non nulle sinon
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start) {
    byte *ehdr    = __elf_get_ehdr( fp );
    byte *content = NULL;
    uint  textsz  = 0;
    vsize sz;
    vaddr addr;

    byte *useless = elf_extract_section_header_table( ehdr, fp );
    free( useless );

    if ( NULL == ehdr ) {
        WARNING_MSG( "Can't read ELF file" );
        return 1;
    }

    if ( 1 == attach_scn_to_mem(memory, scn, SCN_ATTR( WIDTH_FROM_EHDR( ehdr ), permissions ) ) ) {
        WARNING_MSG( "Unable to create %s section", scn );
        free( ehdr );
        return 1;
    }

    content = elf_extract_scn_by_name( ehdr, fp, scn, &textsz, NULL );
    if ( NULL == content ) {
        WARNING_MSG( "Corrupted ELF file" );
        free( ehdr );
        return 1;
    }

    switch( WIDTH_FROM_EHDR(ehdr) ) {
    case 32 :
        sz._32   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._32 = add_start;
        break;
    case 64 :
        sz._64   = textsz/*+8*/; /* +8: In case adding a final sys_exit is needed */
        addr._64 = add_start;
        break;
    default :
        WARNING_MSG( "Wrong machine width" );
        return 1;
    }

    if ( 1 == fill_mem_scn(memory, scn, sz, addr, content ) ) {
        free( ehdr );
        free( content );
        WARNING_MSG( "Unable to fill in %s segment", scn );
        return 1;
    }

    free( content );
    free( ehdr );

    return 0;
}


//Inverse tout les octets d'un entier
uint32_t swap_mot(uint32_t mot)
{	uint res=0;
	res = ((mot&0xff000000)>>24) + ((mot&0x00ff0000)>>8) + ((mot&0x0000ff00)<<8) + ((mot&0x000000ff)<<24);
	return res;
}
