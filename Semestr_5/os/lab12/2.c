#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char *map_address;

    fd = open("test_shared.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        fprintf(stderr, "open failed\n");
        return 1;
    }

    if (lseek(fd, 255, SEEK_SET) == -1)
    {
        fprintf(stderr, "lseek failed\n");
        close(fd);
        return 1;
    }

    if (write(fd, "", 1) == -1)
    {
        fprintf(stderr, "write failed\n");
        close(fd);
        return 1;
    }

    lseek(fd, 0, SEEK_SET);

    map_address = mmap(0, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map_address == MAP_FAILED)
    {
        fprintf(stderr, "mmap failed\n");
        close(fd);
        return 1;
    }
    close(fd);

    char phrase[] = "Take it easy!";
    size_t phrase_len = strlen(phrase) + 1;

    if (phrase_len <= 256)
    {
        memcpy(map_address, phrase, phrase_len);
    }
    else
    {
        fprintf(stderr, "Data too large for mapped region\n");
    }

    printf("Data written. Press Enter to exit...\n");
    getc(stdin);

    if (munmap(map_address, 256) == -1)
    {
        fprintf(stderr, "munmap failed\n");
    }

    return 0;
}
