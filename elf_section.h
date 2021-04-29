#ifndef ELF_SECTION_H_
#define ELF_SECTION_H_

#include "elf_types.h"

/*  
 * ELF Binary Sections.
 *
 * Sections contain all information in an object file, except the ELF
 * header, the program header table, and the section header table.
 */

/* This value marks an undefined, missing, irrelevant, or otherwise
 * meaningless section reference. For example, a symbol "defined" 
 * relative to section number `SHN_UNDEF` is an undefined symbol.
 */
#define SHN_UNDEF       0
/* This value specifies the lower bound of the range of reserverd 
 * indexes.
 */
#define SHN_LORESERVE   0xff00
/* Values in this inclusive range are reserved for processor-specific
 * semantics.
 */
#define SHN_LOPROC      0xff00
#define SHN_HIPROC      0xff1f
/* This value specifies absolute values for the corresponding reference.
 * For example, symbols defined relative to section number `SHN_ABS` have
 * absolute values and are not affected by relocation.
 */
#define SHN_ABS         0xfff1
/* Symbols defined relative to this section are common symbols, such as
 * FORTRAN `COMMON` or unallocated C external variables.
 */
#define SHN_COMMON      0xfff2
/* This value specifies the upper bound of the range of reserved indexes.
 * The system reserves indexes between `SHN_LORESERVE` and `SHN_HIRESERVE`,
 * inclusive; the values do no reference the section header table. That is,
 * the section header table does _not_ contain entries for the reserved
 * indexes.
 */
#define SHN_HIRESERVE   0xffff

/* 
 * Section Types 
 */

/* This value marks the section header as inactive; it does not have
 * an associated section. Other members of the section header have
 * undefined values.
 */
#define SHT_NULL     0
/* This section holds information defined by the program, whose format
 * and meaning are determined solely by the program.
 */
#define SHT_PROGBITS 1
/* This section (along with `SHT_DYNSYM`) hold a symbol table. Currently,
 * an object file may have only one section of each type, but this
 * restriction may be relaxed in the future. Typically, `SHT_SYMTAB` 
 * provides symbols for link editing, though it may also be used for
 * dynamic linking. As a complete symbol table, it may contain many
 * symbols unnecessary for dynamic linking. Consequently, an object file
 * may also contain a `SHT_DYNSYM` section, which holds a minimal set of
 * dynamic linking symbols, to save space.
 */
#define SHT_SYMTAB   2
/* This section holds a string table. An object file may have multiple
 * string table sections.
 */
#define SHT_STRTAB   3
/* This section holds relocation entries with explicit addends, such as
 * type `Elf64_Rela` for the 64-bit class of object files. An object file
 * may have multiple relocation sections.
 */
#define SHT_RELA     4
/* This section holds a symbol hash table. All objects participating in
 * dynamic linking must contain a symbol hash table. Currently, an object
 * file may have only one hash table, but this restriction may be relaxed
 * in the future.
 */
#define SHT_HASH     5
/* This section holds information for dynamic linking. Currently, an
 * object file may have only one dynamic section, but this restriction
 * may be relaxed in the future.
 */
#define SHT_DYNAMIC  6
/* This section holds information that marks the file in some way. */
#define SHT_NOTE     7
/* A section of this type occupies no space in the file but otherwise
 * resembles `SHT_PROGBITS`. Although this section contains no bytes,
 * the `sh_offset` member contains the conceptual file offset.
 */
#define SHT_NOBITS   8
/* The section holds relocation entries without explicit addends,
 * such as type `Elf64_rel` for the 64-bit class of object files.
 * An object file may have multiple relocation sections.
 */
#define SHT_REL      9
/* This section type is reserve but has unspecified semantics. Programs
 * that contain a section of this type do not conform to the ABI.
 */
#define SHT_SHLIB    10
/* See `SHT_SYMTAB` above. */
#define SHT_DYNSYM   11
/* Values in this inclusive range as reserved for processor-specific
 * semantics.
 */
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff
/* This value specifies the lower bound of the range of indexes reserved
 * for application programs.
 */
#define SHT_LOUSER   0x80000000
/* This value specifies the upper bound of the range of indexes reserved
 * for application programs. Section types between `SHT_LOUSER` and
 * `SHT_HIUSER` may be used by the application, without conflicting with 
 * current or future system-defined section types.
 */
#define SHT_HIUSER   0xffffffff

/*
 * Section Attribute Flags for `sh_flags`
 */

/* This section contains data that should be writable during process
 * execution.
 */
#define SHF_WRITE       0x1
/* This section occupies memory during process execution. Some control
 * sections do not reside in the memory image of an object file; this
 * attribute is off for those sections.
 */
#define SHF_ALLOC       0x2
/* This section contains executable machine instructions. */
#define SHF_EXECINSTR   0x4
/* All bits included in this mask are reserved for processor-specific
 * semantics.
 */
#define SHF_MASKPROC    0xf0000000
/* Flat size */
#define SHDR_SIZE 64


/* ELF Binary Section Header */
typedef struct {
    /* This member specifies the name of the section. Its value is an
     * index into the section header string table section, giving the
     * location of a NULL-terminated string.
     */
    Elf64_Half  sh_name;
    /* This member categorizes the section's contents and semantics. */
    Elf64_Half  sh_type;
    /* Sections support 1-bit flags that describe miscellaneous attributes. */
    Elf64_Word  sh_flags;
    /* If the section will appear in the memory image of a process, this
     * member gives the address at which the section's first byte should
     * reside. Otherwise, the member contains 0.
     */
    Elf64_Addr  sh_addr;
    /* This member's value gives the bbyte offset from the beginning of
     * the file to the first byte in the section. One section type,
     * `SHT_NOBITS` described above, occupies no space in the file, and
     * its `sh_offset` member locates the conceptual placement in the file.
     */
    Elf64_Off   sh_offset;
    /* This member gives the section's size in bytes. Unless the section
     * type is `SHT_NOBITS`, the section occupies `sh_size` bytes in the
     * file. A section of type `SHT_NOBITS` may have a non-zero size, but
     * it occupies no space in the file.
     */
    Elf64_Word  sh_size;
    /* This member holds a section header table index link, whose
     * interpretation depends on the section type.
     */
    Elf64_Half  sh_link;
    /* This member holds extra information, whose interpretation depends
     * on the section type.
     */
    Elf64_Half  sh_info;
    /* Some sections have address alignment constraints. For example, if a
     * section holds a doubleword, the system must ensure doubleword
     * alignment for the entire section. That is, the value of `sh_addr`
     * must be congruent to 0, module the value of `sh_addralign`.
     * Currently, only 0 and positive integral powers of two are allowed.
     * Values 0 and 1 mean the section has no alignment constraints.
     */
    Elf64_Word  sh_addralign;
    /* Some sections hold a table of fixed-size entries, such as a symbol
     * table. For such a section, this member gives the size in bytes of
     * each entry. The member contains 0 if the section does not hold a
     * table of fixed-size entries.
     */
    Elf64_Word  sh_entsize;
} Elf64_Shdr;

#endif
