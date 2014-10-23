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
#include "bits.h"
#include "notify.h"
#include "emulateur.h"

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
int init_tab_mem(mem memory)
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

	reg[30].val = vm->seg[nseg].start._32 ;
	//INFO_MSG("Pile chargée avec succès");
	return 1;
}

// fonction affichant les octets d'un segment sur la sortie standard
// parametres :
//   seg        : le segment de la mémoire virtuelle à afficher

void print_segment_raw_content(segment* seg) {
    int k;
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
	if (debut<START_MEM) 
	{
		WARNING_MSG("La memoire commence en 0x%08x",START_MEM);
		return CMD_UNKOWN_RETURN_VALUE;
	}
	uint fin_memory = 0xff7ff000;
	if (fin>fin_memory)
	{	WARNING_MSG("La memoire termine en 0x%08x",fin_memory);
		return CMD_UNKOWN_RETURN_VALUE;
	}
	//Si les adresses demandées sont correctes
	
	for(i=1;i<NB_SECTIONS;i++)
	if (debut >start < START_MEM+(memory->seg.size._64)
	{	printf("

	

	return CMD_OK_RETURN_VALUE;
}*/

void print_byte_mem(mem memory, uint32_t adr, uint32_t val)
{
	/*uint32_t val;
	
	if(find_val(memory, adr-adr%4, &val) == CMD_EXIT_RETURN_VALUE) return CMD_EXIT_RETURN_VALUE;*/
	
	val = swap_mot(val);
	if (adr%4==0) 		printf(" %02x",val&0x000000ff);
	else if (adr%4==1) 	printf(" %02x",(val&0x0000ff00)>>8);
	else if (adr%4==2)	printf(" %02x",(val&0x00ff0000)>>16);
	else if (adr%4==3)	printf(" %02x",(val&0xff000000)>>24);
	return;
}


int print_case_mem(mem memory, uint debut_, uint fin_)
{
	int i, tmp;
	uint debut=debut_;
	uint fin=fin_;
	uint val=0;
	uint adr=debut;
	//DEBUG_MSG("%x %x",debut,fin);
	//if (debut_%4!=0) debut = debut_ - (debut_%4);
	//if (fin_%4!=0) fin = fin_ -(fin_%4);

	//DEBUG_MSG("%x %x",debut,fin);
	
	printf("0x%08x", debut);
	for (i=debut;i<fin;i++)
	{	if (i%0x10==0 && i != debut ) printf("\n0x%08x", i);
		if (i%4==0) adr=i;
		
		tmp = find_val(memory, adr, &val);
		if (tmp==CMD_UNKOWN_RETURN_VALUE) return tmp;
		
		else print_byte_mem(memory, i, val);
	}
printf("\n");
DEBUG_MSG("");
}

int find_val(mem memory, uint32_t adresse, uint32_t* res) {	
	//DEBUG_MSG("");
	int i=0;
	int taille;
	uint32_t word = 0;
	int start =0;
	segment* seg =NULL;
	//DEBUG_MSG("%d",memory->nseg);
	
	if (adresse<START_MEM) ERROR_MSG("La memoire commence en 0x%08x",START_MEM);
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
		{DEBUG_MSG("");
			word = *((uint32_t *) (seg->content+adresse-start));
			FLIP_ENDIANNESS(word);
			*res = word;
			return CMD_OK_RETURN_VALUE;
		}
		
	}
	puts("");
	WARNING_MSG("L'adresse 0x%08x n'est pas allouee", adresse);
	
	return CMD_UNKOWN_RETURN_VALUE;
}	

//Inverse tout les octets d'un entier
uint32_t swap_mot(uint32_t mot)
{	int res=0;
	res = ((mot&0xff000000)>>24) + ((mot&0x00ff0000)>>8) + ((mot&0x0000ff00)<<8) + ((mot&0x000000ff)<<24);
	return res;
}
