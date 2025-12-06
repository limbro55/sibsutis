#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_symbol(
    int index,
    Elf64_Sym *sym,
    const char *name)
{
    const char *types[] = {
        "NOTYPE", "OBJECT", "FUNC", "SECTION",
        "FILE", "COMMON", "TLS"
    };
    const char *binds[] = {
        "LOCAL", "GLOBAL", "WEAK"
    };
    const char *vis[] = {
        "DEFAULT", "INTERNAL", "HIDDEN", "PROTECTED"
    };

    unsigned char t = ELF64_ST_TYPE(sym->st_info);
    unsigned char b = ELF64_ST_BIND(sym->st_info);
    unsigned char v = ELF64_ST_VISIBILITY(sym->st_other);

    printf("%-5d %-8lx %-5lu %-6s %-6s %-8s ",
        index,
        sym->st_value,
        sym->st_size,
        t < 7 ? types[t] : "UNKNOWN",
        b < 3 ? binds[b] : "UNKNOWN",
        v < 4 ? vis[v] : "UNKNOWN"
    );

    if (sym->st_shndx == SHN_UNDEF)
        printf("UND ");
    else
        printf("%-3d ", sym->st_shndx);

    printf("%s\n", name);
}

void process_table(
    FILE *file,
    Elf64_Shdr *symtab,
    Elf64_Shdr *strtab)
{
    Elf64_Sym sym;

    int count = symtab->sh_size / symtab->sh_entsize;

    for (int i = 0; i < count; i++) {
        fseek(file, symtab->sh_offset + i * symtab->sh_entsize, SEEK_SET);
        fread(&sym, sizeof(sym), 1, file);

        char name[256] = {0};
        fseek(file, strtab->sh_offset + sym.st_name, SEEK_SET);
        fread(name, 1, sizeof(name), file);

        print_symbol(i, &sym, name);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <elf-file>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    Elf64_Ehdr eh;
    fread(&eh, 1, sizeof(eh), file);

    Elf64_Shdr sh;
    Elf64_Shdr symtab = {0}, strtab = {0};
    Elf64_Shdr dynsym = {0}, dynstr = {0};

    for (int i = 0; i < eh.e_shnum; i++) {
        fseek(file, eh.e_shoff + i * eh.e_shentsize, SEEK_SET);
        fread(&sh, sizeof(sh), 1, file);

        if (sh.sh_type == SHT_SYMTAB)
            symtab = sh;

        if (sh.sh_type == SHT_STRTAB && i == eh.e_shstrndx)
            continue;

        if (sh.sh_type == SHT_STRTAB && !strtab.sh_size)
            strtab = sh;

        if (sh.sh_type == SHT_DYNSYM)
            dynsym = sh;

        if (sh.sh_type == SHT_STRTAB &&
            dynsym.sh_link == i)
            dynstr = sh;
    }

    printf("Index Value     Size  Type   Bind   Vis      Ndx Name\n");

    if (dynsym.sh_size && dynstr.sh_size) {
        process_table(file, &dynsym, &dynstr);
    }

    if (symtab.sh_size && strtab.sh_size) {
        process_table(file, &symtab, &strtab);
    }

    fclose(file);
    return 0;
}
