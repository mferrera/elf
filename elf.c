#include <stdio.h>
#include <string.h>

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
    *(Elf64_Half *)buf = h->p_flags;
    buf += sizeof(Elf64_Half);
    *(Elf64_Word *)buf = h->p_align;
}

int main() {
    FILE *f = fopen("./b.out", "w");
    char *hbuf[EHDR_SIZE] = {0};
    char *pbuf[PHDR_SIZE] = {0};

    Elf64_Ehdr hdr = {0};
     /* Begin with the magic number: 0x7f 'E' 'L' 'F' */
    hdr.e_ident[EI_MAG0] = ELFMAG0;
    hdr.e_ident[EI_MAG1] = ELFMAG1;
    hdr.e_ident[EI_MAG2] = ELFMAG2;
    hdr.e_ident[EI_MAG3] = ELFMAG3;
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
    /* Our entry point is right ?? */
    hdr.e_entry = 0x40;
    /* The program header table offset.
     * Set to be directly after the ELF header.
     */
    hdr.e_phoff = 0x40;
    /* Section header offset. */
    hdr.e_shoff = SHN_UNDEF;
    /* Processor flags. */
    hdr.e_flags = 0;
    /* The size of this header. */
    hdr.e_ehsize = EHDR_SIZE;
    /* The size of the program header table entry. */
    hdr.e_phentsize = PHDR_SIZE;
    /* The number of program header entries in the table. */
    hdr.e_phnum = 1;
    /* The section header size. */
    hdr.e_shentsize = SHDR_SIZE;
    /* The number of sections. */
    hdr.e_shnum = SHN_UNDEF;
    /* Section header index of the string table. */
    hdr.e_shstrndx = SHN_UNDEF;
    /* Flatten this struct into the buffer. */
    pack_ehdr(hbuf, &hdr);
    fwrite(hbuf, EHDR_SIZE, 1, f);

    Elf64_Phdr phdr = {0};
    /* This is the phdr table itself. */
    phdr.p_type = PT_PHDR;
    /* It's located right here. */
    phdr.p_offset = 0x40;
    /* Same with the virtual and physical address. */
    phdr.p_vaddr = 0x40;
    phdr.p_paddr = 0x40;
    /* The bytes in this segment are 0. */
    phdr.p_filesz = 0;
    phdr.p_memsz = 0;
    /* No flags to set. */
    phdr.p_flags = 0;
    /* We're aligning this congruent with our earlier addresses. */
    phdr.p_align = 0x40;
    /* Flatten this struct & write it */
    pack_phdr(pbuf, &phdr);
    fwrite(pbuf, PHDR_SIZE, 1, f);

    fclose(f);
}
