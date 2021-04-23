#ifndef ELF_PHEADER_H
#define ELF_PHEADER_H

#include "elf_types.h"

/* `p_type` Types */

/* The array element is unused; other members' values are undefined.
 * This type lets the program header table have ignored entries.
 */
#define PT_NULL     0
/* The array element specifies a loadable segment, described by
 * `p_filesz` and `p_memsz`. The bytes from the file are mapped
 * to the beginning of the memory segment. If the segment's memory
 * size (`p_memsz`) is larger than the file size (`p_filesz`), the
 * "extra" bytes are defined to hold the value 0 and to follow the
 * segment's initialized area. The file size may not be larger than
 * the memory size. Loadable segment entries in the program header
 * table appear in ascending order, sorted on the `p_vaddr` member.
 */
#define PT_LOAD     1
/* The array element specifies dynamic linking information. */
#define PT_DYNAMIC  2
/* The array element specifies the location and size of a NULL-
 * terminated path name to invoke as an interpreter. This segment
 * type is meaningful only for executable files (though it may
 * occur for shared objects); it may not occur more than once in
 * a file. If it is present, it must precede any loadable segment
 * entry.
 */
#define PT_INTERP   3
/* The array element specifies the location and size of auxiliary
 * information.
 */
#define PT_NOTE     4
/* This segment type is reserved by has unspecified semantics.
 * Programs that contain an array element of this type do no conform
 * to the ABI.
 */
#define PT_SHLIB    5
/* The array element, if present, specifies the location and size
 * of the program header table itself, both in the file and in the
 * memory image of the program. This segment type may not occur
 * more than once in a file. Morever, it may occur only if the
 * program header table is part of the memory image of the program.
 * If it is present, it must precede any loadable segment entry.
 */
#define PT_PHDR     6
/* Values in this inclusive range are reserved for processor-specific
 * semantics.
 */
#define PT_LOPROC   0x7000000000000000
#define PT_HIPROX   0x7fffffffffffffff

typedef struct {
    /* This member tells what kind of segment this array element
     * describes or how to interpret the array element's information.
     */
    Elf64_Word  p_type;
    /* This member gives the offset from the beginning of the file
     * at which the first byte of the segment resides.
     */
    Elf64_Off   p_offset;
    /* This member gives the virtual address at which the first byte
     * of the segment resides in memory.
     */
    Elf64_Addr  p_vaddr;
    /* On systems for which physical addressing is relevant, this member
     * is reserved for the segment's physical address. Because System V
     * ignores physical addressing for application programs, this member
     * has unspecified contents for executable files and shared objects.
     */
    Elf64_Addr  p_paddr;
    /* This member gives the number of bytes in the file image of the
     * segment; it may be zero.
     */
    Elf64_Word  p_filesz;
    /* This member gives the number of bytes in the memory image of the
     * segment; it may be zero.
     */
    Elf64_Word  p_memsz;
    /* This member gives flags relevant to the segment. */
    Elf64_Word  p_flags;
    /* Loadable process segments must have congruent values for `p_vaddr`
     * and `p_offset`, modulo the page size. This member gives the value
     * to which the segments are aligned in memory and in the file. Values
     * 0 and 1 mean no alignment is required. Otherwise, `p_align` should
     * be a positive, integral power of 2, and `p_vaddr` should equal
     * `p_offset`, module `p_align`.
     */
    Elf64_Word  p_align;
} Elf64_Phdr;

#endif
