#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    int fd;
    struct stat stat_file;
    char dummy;
    char *map_address;

    fd = open("test.txt", O_RDWR | O_CREAT | S_IRUSR | S_IRGRP, 0644);

    if (fd == -1)
        fprintf(stderr, "open\n");
    if (fstat(fd, &stat_file))
        fprintf(stderr, "fstat\n");

    map_address = (char *)mmap(0, stat_file.st_size, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE, fd, 0);
    if (map_address == MAP_FAILED)
        fprintf(stderr, "mmap\n");

    dummy = map_address[1];
    map_address[0] = map_address[5] - 0x20;
    map_address[1] = map_address[3];
    map_address[2] = map_address[4];
    map_address[3] = map_address[10];
    map_address[4] = dummy;
    map_address[14] = 63;

    write(fd, map_address, stat_file.st_size);
    munmap(map_address, stat_file.st_size);
    close(fd);

    return 0;
}
