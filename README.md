# ELF

This repository is my attempt to get a better understanding of ELF
binaries. It loosely follows the ELF32 standard laid out in the TIS
Portable Formats Specification 1.1, and updates various things for our
modern 64-bit world.

Currently, all this does is write bytes in ELF64 format for a binary file
named `b.out`. This binary contains only the minimum necessary: the ELF
header, program header, and 7 bytes of shellcode that call `exit(0)`.
There's (not yet) actual `.data`, `.bss`, or `.text` sections (or any of
the other sections). The binary it outputs is 127 bytes in size.

# Usage

```
make
./elf
./b.out
echo $?
```

# Future

- Add proper sections?
- Run more interesting operations?
- Add ARM support?
- ?
