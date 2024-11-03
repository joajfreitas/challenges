#include <unistd.h>
#include <fcntl.h>

int dup(int  fd) {
    return fcntl(fd, F_DUPFD, 0);
}

int dup2(int oldfd, int newfd) {

    if(oldfd == newfd)
        return oldfd;

    if(fcntl(oldfd, F_GETFD) == -1)
        return -1;

    if(close(newfd) == -1)
        return -1;

    fcntl(oldfd, F_DUPFD, newfd);

    return newfd;
}

int
main(int argc, char *argv[]) {
    return 0;
}
