#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int 
dup(int  fd) {
    return fcntl(fd, F_DUPFD, 0);
}

int 
dup2(int oldfd, int newfd) {

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
check_same_flags(int fd1, int fd2) {
    int flags1 = fcntl(fd1, F_GETFL);
    int flags2 = fcntl(fd2, F_GETFL);
    
    return flags1 == flags2;
}

int check_same_offset(int fd1, int fd2) {
    off_t offset1 = lseek(fd1, 0, SEEK_CUR);
    off_t offset2 = lseek(fd2, 0, SEEK_CUR);
    
    return offset1 == offset2;
}

int
main(int argc, char *argv[]) {
    int fd = open(argv[1], O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

    int new_fd = dup(fd);
    
    return !(check_same_flags(fd, new_fd) && check_same_offset(fd, new_fd));
}
