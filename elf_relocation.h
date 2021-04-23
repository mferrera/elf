#ifndef ELF_RELOCATION_H_
#define ELF_RELOCATION_H_

#include "elf_types.h"

/* Relocation macros */
#define ELF64_R_SYM(i)      ((i)>>8)
#define ELF64_R_TYPE(i)     ((unsigned char)(i))
#define ELF64_R_INFO(s,t)   (((s)<<8)+(unsigned char)(t))

typedef struct {
    /* This member gives the location at which to apply the relocation
     * action. For a relocatable file, the value is the byte offset from
     * the beginning of the section to the storage unity affected by the
     * relocated. For an executabble file or a shared object, the value
     * is the virtual address of the storage unit affected by the relocation.
     */
    Elf64_Addr  r_offset;
    /* This member gives both the symbol table index with respect to 
     * which the relocation must be made, and the type of relocation to
     * apply. For example, a call instruction's relocation entry would
     * hold the symbol table index of the function being called. If the
     * index of `STN_UNDEF`, the undefined symbol index, the relocation
     * uses 0 as the "symbol value." Relocation types are processor-
     * specific. When the text refers to a location entry's relocation
     * type or symbol table index, it means the result of applying
     * `ELF64_R_TYPE` or `ELF64_R_SYM`, respectively, to the table
     * entry's `r_info` member.
     */
    Elf64_Word  r_info;
} Elf64_Rel;

typedef struct {
    /* Same as above. */
    Elf64_Addr  r_offset;
    /* Same as above. */
    Elf64_Word  r_info;
    /* This member specifies a constant addend used to compute the value
     * to be stored into the relocatable field.
     */
    Elf64_Sword r_addend;
} Elf64_Rela;

#endif
