#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void print_elf_header(Elf64_Ehdr *header) {
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             %s\n",
           header->e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "ELF32");

    printf("  Data:                              %s\n",
           header->e_ident[EI_DATA] == ELFDATA2LSB
               ? "2's complement, little endian"
               : "2's complement, big endian");

    printf("  Version:                           %d\n",
           header->e_ident[EI_VERSION]);

    printf("  OS/ABI:                            %d\n",
           header->e_ident[EI_OSABI]);

    printf("  Type:                              %d\n", header->e_type);

    printf("  Machine:                           %d\n", header->e_machine);

    printf("  Entry point address:               0x%lx\n", header->e_entry);

    printf("  Start of program headers:          %ld (bytes into file)\n",
           header->e_phoff);

    printf("  Start of section headers:          %ld (bytes into file)\n",
           header->e_shoff);

    printf("  Number of program headers:         %d\n", header->e_phnum);

    printf("  Number of section headers:         %d\n", header->e_shnum);

    printf("  Section header string table index: %d\n", header->e_shstrndx);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    void *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    Elf64_Ehdr *header = (Elf64_Ehdr *)map;

    // Check if it's a valid ELF file
    if (memcmp(header->e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Not an ELF file\n");
        munmap(map, st.st_size);
        close(fd);
        return 1;
    }

    print_elf_header(header);

    munmap(map, st.st_size);
    close(fd);

    return 0;
}