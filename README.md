# ELF

This repository is my attempt to get a better understanding of ELF
binaries. It loosely follows the ELF32 standard laid out in the TIS
Portable Formats Specification 1.1, and updates various things for our
modern 64-bit world.

Currently, all this does is write bytes in ELF64 format for a binary file
named `b.out`. This binary contains only the minimum necessary: the ELF
header, program header, and 7 bytes of 32-bit shellcode that call
`exit(0)`. The binary it outputs is 127 bytes in size.

# Usage

```
make
./b.out
echo &?
```
