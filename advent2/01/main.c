#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(char argc, char *argv[]) {
  char buffer[4096] = {0};
  for (int i = 1; i < argc; i++) {
    int fd = open(argv[i], 0);
    read(fd, buffer, 4096);
    write(1, buffer, 4096);
    close(fd);
  }

  close(1);
  return 0;
}
