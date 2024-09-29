#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <tlpi.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    char buffer[BUF_SIZE] = {0};
    
    int flags = O_RDWR | O_CREAT;
    char c = 0;
    while((c = getopt(argc, argv, "a")) != -1) {
        switch (c) {
            case 'a':
                flags |= O_APPEND;
                break;
            default:
                printf("%c", c);
                break;
        }
    }
    
    int fd = open(argv[optind], flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1) {
        errExit("open");
    }

    while (true) {
        int nread = read(STDIN_FILENO, buffer, BUF_SIZE);
        if (nread == 0) {
            close(fd);
            return 0;
        }

        write(STDOUT_FILENO, buffer, nread);
        write(fd, buffer, nread);

    }

    return 0;
}
