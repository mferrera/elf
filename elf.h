#ifndef ELF_H_
#define ELF_H_

#include "elf_types.h"

/* #########################################
 * These headers are, to some degree, just a
 * "rewrite" of <linux/elf.h>. While rote, 
 * going through all of them one-by-one has
 * great educational value!
 * ########################################
 */

/* Identification indexes 
 *
 * These are the indexes of the first 16 bytes of the ELF
 * header. For example, the first 4 bytes of an ELF header are 
 *      [0x7f, 'E', 'L', 'F']
 * Hence
 *      e_ident[EI_MAG0] = 0x7f
 *      e_ident[EI_MAG1] = 'E'
 *      e_ident[EI_MAG2] = 'L'
 *      e_ident[EI_MAG3] = 'F'
 * etc.
 * */
#define EI_MAG0    0 // File identification
#define EI_MAG1    1 // File identification
#define EI_MAG2    2 // File identification
#define EI_MAG3    3 // File identification
#define EI_CLASS   4 // File class
#define EI_DATA    5 // Data encoding
#define EI_VERSION 6 // File version. Must be EV_CURRENT
#define EI_PAD     7 // Start of unused bytes in `e_ident`
#define EI_NIDENT 16 // Size of `e_ident[]`
/* EI_MAG magic number values */
#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'
/* EI_CLASS values. The file's class, or capacity. */
#define ELFCLASSNONE 0 // Invalid class
#define ELFCLASS32   1 // 32-bit objects
#define ELFCLASS64   2 // 64-bit objects
/* EI_DATA values. These specific the data encoding of
 * the processor-specific data in the object file.
 */
#define ELFDATANONE 0 // Invalid data encoding
#define ELFDATA2LSB 1 // 2's complement least-significant values
#define ELFDATA2MSB 2 // 2's complement most-significant values
/* Object file types */
#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4
/* Processor specific */
#define ET_LOPROC 0xff00
#define ET_HIPROX 0xffff
/* Machine type */
#define EM_NONE   0
#define EM_X86_64 0x3e // 62
/* ELF Version */
#define EV_NONE    0
#define EV_CURRENT 1
/* Flat size */
#define EHDR_SIZE 64

/* ELF binary object header. */
typedef struct {
    /* The initial bytes mark the file as an object file and provide
     * machine-independent data with which to decode and interpret 
     * the file's contents.
     */
    unsigned char   e_ident[EI_NIDENT]; // 16 bytes
    /* This member identifies the object file type.
     *      Name    Value   Meaning
     *      -----------------------
     *      ET_NONE     0   No file type
     *      ET_REL      1   Relocatable file
     *      ET_EXEC     2   Executable file
     *      ET_DYN      3   Shared object file
     *      ET_CORE     4   Core file
     *
     *      ET_LOPROC   0xff00  Processor specific
     *      ET_HIPROC   0xffff  Processor specific
     */
    Elf64_Short     e_type;
    /* This member's value specifies the required architecture for
     * an individual file.
     *      Name    Value   Meaning
     *      -----------------------
     *      EM_NONE     0   No machine
     *      ...
     *      EM_X86_64  62   AMD x86-64 architecture
     *
     * Other values are reserved and will be assigned to new machines
     * as necessary. Processor-specific ELF names use the machine name
     * to distinguish them. For example, the flags mentioned below use
     * the prefix EF_; a flag named WIDGET for the EM_XYZ machine 
     * would be called EF_XYZ_WIDGET.
     */
    Elf64_Short     e_machine;
    /* This member identifies the object file version.
     *      Name    Value   Meaning
     *      -----------------------
     *      EV_NONE     0   Invalid version
     *      EV_CURRENT  1   Current version
     *
     * The value 1 signifies the original file format; extensions will
     * create new versions with higher numbers. The value of EV_CURRENT,
     * though given as 1 above, will change as necessary to reflect the
     * current version number.
     */
    Elf64_Half      e_version;
    /* This member gives the virtual address to which the system first
     * transfers control, thus starting the process. If the file has no
     * associated entry point, this member holds zero.
     */
    Elf64_Addr      e_entry;
    /* This member holds the program header table's file offset in
     * bytes. If the file has no program header table, this member
     * holds zero.
     */
    Elf64_Off       e_phoff;
    /* This member holds the section header table's file offset in
     * bytes. If the file has no section header table, this member
     * holds zero.
     */
    Elf64_Off       e_shoff;
    /* This member holds processor-specific flags associated with the
     * file. Flag names take the form EF_machine_flag.
     */
    Elf64_Half      e_flags;
    /* This member holds the ELF header's size in bytes. */
    Elf64_Short     e_ehsize;
    /* This member holds the size in bytes of one entry in the file's
     * program header table; all entries are the same size.
     */
    Elf64_Short     e_phentsize;
    /* This member holds the number of entries in the program header
     * table. Thus the product of `e_phentsize` and `e_phnum` gives
     * the table's size in bytes. If a file has no program header
     * table, `e_phnum` holds the value zero.
     */
    Elf64_Short     e_phnum;
    /* This member holds a section header's size in bytes. A section
     * header is one entry in the section header table; all entries 
     * are the same size.
     */
    Elf64_Short     e_shentsize;
    /* This member holds the number of entries in the section header
     * table. Thus the product of `e_shentsize` and `e_shnum` gives
     * the section header table's size in bytes. If a file has no
     * section header table, `e_shnum` holds the value zero.
     */
    Elf64_Short     e_shnum;
    /* This member holds the section header table index of the entry
     * associated with the section name string table. If the files
     * has no section name string table, this member holds the value
     * SHN_UNDEF.
     */
    Elf64_Short     e_shstrndx;
} Elf64_Ehdr;

#endif
