#ifndef ELF_SYMBOL_H_
#define ELF_SYMBOL_H_

#include "elf_types.h"

/* Useful for manipulating a symbol's type and binding attributes. */
#define ELF64_ST_BIND(i)    ((i)>>4)
#define ELF64_ST_TYPE(i)    ((i)&0xf)
#define ELF64_ST_INFO(b,t)  (((b)<<4)+((t)&0xf))
/* Local symbols are not visible outside the object file containing
 * their definition. Local symbols of the same name may exist in
 * multiple files without interfering with each other.
 */
#define STB_LOCAL   0
/* Global symbols are visible to all object files being combined.
 * One file's definition of a global symbol will satisfy another
 * file's undefined reference to the same global symbol.
 */
#define STB_GLOBAL  1
/* Weak symbols resemble global symbols, but their definitions have
 * lower precedence.
 */
#define STB_WEAK    2
/* Values in this inclusive range are reserved for processor-specific
 * semantics.
 */
#define STB_LOPROC 13
#define STD_HIPROC 15

/* An entry in the symbol table. */
typedef struct {
    /* This member holds an index into the object file's symbol
     * string table, which holds the character representations
     * of the symbol names. If the value is non-zero, it represents
     * a string table index that gives the symbol name. Otherwise,
     * the symbol table entry has no name.
     */
    Elf64_Word      st_name;
    /* This member gives the value of the associated symbol.
     * Depending on the context, this may be an absolute value,
     * and address, etc.
     */
    Elf64_Addr      st_value;
    /* Many symbols have associated sizes. For example, a data object's
     * size is the number of bytes contained in the object. This member
     * holds 0 if the symbol has no size or an unknown size.
     */
    Elf64_Word      st_size;
    /* This member specifies the symbol's type and binding attributes. */
    unsigned char   st_info;
    /* This member currently holds 0 and has no defined meaning. */
    unsigned char   st_other;
    /* Every symbol table entry is "defined" in relation to some
     * section; this member holds the relevant section header table
     * index.
     */
    Elf64_Short     st_shndx;
} Elf64_Sym;

#endif
