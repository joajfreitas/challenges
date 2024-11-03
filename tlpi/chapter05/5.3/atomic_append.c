#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi.h"

int
main(int argc, char *argv[])
{
    int fd;
    off64_t off;

    if ((argc != 4 && argc != 3) || strcmp(argv[1], "--help") == 0)
        usageErr("%s filename num_bytes [x]\n", argv[0]);
    
    unsigned flags = O_RDWR | O_CREAT;
    
    if (argc == 4) {
        flags |= O_APPEND;
    }

    fd = open(argv[1], flags, S_IRUSR | S_IWUSR);

    if (fd == -1)
        errExit("open");
    
    if (argc == 4) {
        if (lseek(fd, 0, SEEK_END) == -1) {
            errExit("lseek");
        }
    }

    int num_bytes = atoi(argv[2]);
    
    for (int i=0; i<num_bytes; i++) {
        if (write(fd, "x", 1) == -1)
            errExit("write");
    }

    exit(EXIT_SUCCESS);
}
