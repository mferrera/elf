#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "elf.h"
#include "elf_pheader.h"
#include "elf_section.h"

/* Some of these could be skipped as they are sequentially 0, but
 * set them explicitly anyway.
 */
void pack_ehdr(void *buf, Elf64_Ehdr *h) {
    memcpy(buf, h->e_ident, EI_NIDENT); // NOLINT
    buf += EI_NIDENT;
    *(Elf64_Short *)buf = h->e_type;
    buf += sizeof(Elf64_Short);
    *(Elf64_Short *)buf = h->e_machine;
    buf += sizeof(Elf64_Short);
    *(Elf64_Half *)buf = h->e_version;
    buf += sizeof(Elf64_Half);
    *(Elf64_Addr *)buf = h->e_entry;
    buf += sizeof(Elf64_Addr);
    *(Elf64_Off *)buf = h->e_phoff;
    buf += sizeof(Elf64_Off);
    *(Elf64_Off *)buf = h->e_shoff;
    buf += sizeof(Elf64_Off);
    *(Elf64_Half *)buf = h->e_flags;
    buf += sizeof(Elf64_Half);
    *(Elf64_Short *)buf = h->e_ehsize;
    buf += sizeof(Elf64_Short);
    *(Elf64_Short *)buf = h->e_phentsize;
    buf += sizeof(Elf64_Short);
    *(Elf64_Short *)buf = h->e_phnum;
    buf += sizeof(Elf64_Short);
    *(Elf64_Short *)buf = h->e_shentsize;
    buf += sizeof(Elf64_Short);
    *(Elf64_Short *)buf = h->e_shnum;
    buf += sizeof(Elf64_Short);
    *(Elf64_Short *)buf = h->e_shstrndx;
}

void pack_phdr(void *buf, Elf64_Phdr *h) {
    *(Elf64_Half *)buf = h->p_type;
    buf += sizeof(Elf64_Half);
    *(Elf64_Half *)buf = h->p_flags;
    buf += sizeof(Elf64_Half);
    *(Elf64_Off *)buf = h->p_offset;
    buf += sizeof(Elf64_Off);
    *(Elf64_Addr *)buf = h->p_vaddr;
    buf += sizeof(Elf64_Addr);
    *(Elf64_Addr *)buf = h->p_paddr;
    buf += sizeof(Elf64_Addr);
    *(Elf64_Word *)buf = h->p_filesz;
    buf += sizeof(Elf64_Word);
    *(Elf64_Word *)buf = h->p_memsz;
    buf += sizeof(Elf64_Word);
    *(Elf64_Word *)buf = h->p_align;
}

int main() {
    FILE *f = fopen("./b.out", "w");
    char *hbuf[EHDR_SIZE] = {0};
    char *pbuf[PHDR_SIZE] = {0};

    /*
     * ##################
     * #   Elf Header   #
     * ##################
     */
    Elf64_Ehdr hdr = {0};
     /* Begin with the magic number: 0x7f 'E' 'L' 'F' */
    hdr.e_ident[EI_MAG0] = ELFMAG0;
    hdr.e_ident[EI_MAG1] = ELFMAG1;
    hdr.e_ident[EI_MAG2] = ELFMAG2;
    hdr.e_ident[EI_MAG3] = ELFMAG3;
    /* The file class. */
    hdr.e_ident[EI_CLASS] = ELFCLASS64;
    /* The data encoding. */
    hdr.e_ident[EI_DATA] = ELFDATA2LSB;
    /* The ELF version, which has been 1 since... */
    hdr.e_ident[EI_VERSION] = EV_CURRENT;
    /* The type of ELF file this is */
    hdr.e_type = ET_EXEC;
    /* The type of machine this is. */
    hdr.e_machine = EM_X86_64;
    /* The version of this ELF file. */
    hdr.e_version = EV_CURRENT;
    /* Our entry point is
     *      v_addr + 0x78
     * where 78 is the 120 bytes of the ELF header and program header*/
    hdr.e_entry = 0x100078;
    /* The program header table offset. Directly after the ELF header.  */
    hdr.e_phoff = 0x40;
    /* Section header offset. */
    hdr.e_shoff = 0x0;
    /* Processor flags. */
    hdr.e_flags = 0x0;
    /* The size of this header. */
    hdr.e_ehsize = EHDR_SIZE;
    /* The size of the program header table entry. */
    hdr.e_phentsize = PHDR_SIZE;
    /* The number of program header entries in the table. */
    hdr.e_phnum = 0x1;
    /* The section header size. */
    hdr.e_shentsize = 0x0;
    /* The number of sections. */
    hdr.e_shnum = 0x0;
    /* Section header index of the string table. */
    hdr.e_shstrndx = 0x0;
    /* Flatten this struct into the buffer. */
    pack_ehdr(hbuf, &hdr);
    fwrite(hbuf, EHDR_SIZE, 1, f);

    /*
     * ##################
     * # Program Header #
     * #################
     */
    Elf64_Phdr phdr = {0};
    /* This is the phdr table itself. */
    phdr.p_type = PT_LOAD;
    /* Flags */
    phdr.p_flags = PF_X;
    /* It's located right here. */
    phdr.p_offset = 0x0;
    /* Same with the virtual and physical address. */
    phdr.p_vaddr = 0x100000;
    /* The physical address isn't used. */
    phdr.p_paddr = 0x100000;
    /* Our .text code is only 7 bytes of instructions. */
    phdr.p_filesz = 0x7;
    phdr.p_memsz = 0x7;
    /* We're aligning this congruent with our earlier addresses. */
    phdr.p_align = 0x100000;
    /* Flatten this struct & write it */
    pack_phdr(pbuf, &phdr);
    fwrite(pbuf, PHDR_SIZE, 1, f);

    /* Call exit(0)
     *      0x100078    mov    $0x3c,%al ; b0 3c
     *      0x10007a    xor    %rdi,%rdi ; 48 31 ff
     *      0x10007d    syscall          ; 0f 05
    */
    char text[] = "\xb0\x3c\x48\x31\xff\x0f\x05";
    fwrite(text, 7, 1, f);
    fclose(f);
    /* chmod 770 */
    chmod("./b.out", S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP);
}
