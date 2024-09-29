#include <sys/stat.h>
#include <fcntl.h>

#include <tlpi.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int fd1 = open(
            argv[1], 
            O_RDONLY, 
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
    );
    if (fd1 == -1) {
        errExit("fd1 open");
    }


    int fd2 = open(
            argv[2], 
            O_WRONLY | O_CREAT, 
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
    );
    if (fd2 == -1) {
        errExit("fd2 open");
    }


    char buffer[BUF_SIZE] = {0};
    while (true) {
        int nread = read(fd1, buffer, BUF_SIZE);
        if (nread == 0) {
            close(fd1);
            close(fd2);
            return 0;
        }

        write(fd2, buffer, nread);

    }
}
