
/**
 * @file mem.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Nov  1 00:56:03 2013
 * @brief Memory.
 *
 * Memory.
 */

#ifndef _MEM_H_
#define _MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "types.h"
#include "reg.h"
#include "syms.h"
#include "dico.h"
#include "relocator.h"
#include "elf.h"
#define MEMSZ		  4  //Mo
#define MEMSZ_BYTES  (long) (MEMSZ*1024*1024)

typedef union {
    uint32_t _32;
    uint64_t _64;
} vsize;

typedef struct {
    char      *name;
    byte      *content;
    vaddr      start;
    vsize      size;
    uint32_t   attr;
} segment;

typedef struct {
    vsize       extent;
    uint32_t    nseg;
    segment    *seg;
	int start_mem;
} *mem;



#define R__   1
#define RW_   2
#define R_X   3
#define UNDEF 7 /* For optionnal sections (.rodata) */

#define PGSZ          4  /* Page size:  4K */
#define STACKSZ       8  /* Stack size: 8M */
#define STACKSZ_BYTES (STACKSZ*1024*1024)
#define NPAGES(b) ( (b) ? ( (b)>>10 ) ? ((b)>>10)/PGSZ : 1 : 0 )


#define RODATA      0
#define TEXT        1
#define DATA        2
#define BSS         3
#define HEAP        4
#define LIBC_TEXT   5
#define LIBC_DATA   6
#define STACK       7
#define VSYSCALL    8 /* CAUTION: Make sure this one is the very last */

#define LAST_SEG    ((VSYSCALL)+1)

#define SCN_ATTR(width, rights)  (((width==0x1?32:64)<<8)+rights)
#define SCN_RIGHTS(attr)         (((attr)&0x000000ff))
#define SCN_WIDTH(attr)          (((attr))>>8)

// On fixe ici une adresse basse dans la mémoire virtuelle. Le premier segment
// ira se loger à cette adresse.
#define START_MEM 0
#define STOP_MEM 0xfffff000
// nombre max de sections que l'on extraira du fichier ELF
#define NB_SECTIONS 4

// nom de chaque section
#define TEXT_SECTION_STR ".text"
#define RODATA_SECTION_STR ".rodata"
#define DATA_SECTION_STR ".data"
#define BSS_SECTION_STR ".bss"

//nom du prefix à appliquer pour la section
#define RELOC_PREFIX_STR ".rel"

int init_stack(mem vm, registre* reg, unsigned int nseg);
mem alloue_mem(void);
int init_mem( uint32_t nseg, registre* reg, mem vm );
int attach_scn_to_mem( mem vm, char *name, uint32_t attr );
int fill_mem_scn( mem vm, char *name, vsize sz, vaddr start, byte *content );
void print_mem( mem vm );
int del_mem( mem vm );
void print_segment_raw_content(segment* seg);
  void reloc_segment(FILE* fp, segment seg, mem memory,unsigned int endianness,stab* symtab, stab*, FILE*);
int init_tab_mem(mem memory);

int print_byte_mem(mem memory, uint32_t adr);
int print_case_mem(mem memory,uint debut,uint fin);
int find_word(mem memory, uint32_t adresse, uint32_t* res);
int find_byte(mem memory, uint32_t adresse, uint8_t* res);
int load_word(mem memory, uint32_t addresse, uint32_t wordtoload);
int load_byte(mem memory, uint32_t adresse, byte bytetoload);
int elf_load_section_in_memory(FILE* fp, mem memory, char* scn,unsigned int permissions,unsigned long long add_start);
  uint32_t find_sec_start(mem memory, int syms, char* name );
  void print_rel_table(char* reloc_name, Elf32_Rel* rel, uint32_t scnsz);
  uint32_t swap_mot(uint32_t mot);
#ifdef __cplusplus
}
#endif

#endif /* _MEM_H_ */
