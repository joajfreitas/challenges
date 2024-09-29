#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <tlpi.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1) {
        errExit("open");
    }
    char buffer[BUF_SIZE] = {0};
    

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
