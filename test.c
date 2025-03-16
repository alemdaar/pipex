#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd = open ("fruit", O_RDWR);
    if (fd == -1) {
        perror ("open");
        return 1;
    }
    write (fd, "hello\n", 5);
}
