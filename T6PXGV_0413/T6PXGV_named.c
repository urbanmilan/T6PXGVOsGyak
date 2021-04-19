  #include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAME "BRZGJZ"
#define SIZE 64

int main() {
    pid_t _pid;
    int _fifo;
    int _open;
    char _buffer[SIZE];
    int _temp;

    _pid = fork();
    if (_pid == -1) {
        perror("fork() Error");
        exit(-1);
    }

    if (_pid == 0) { // child
        printf("%d: I'm a child\n", getpid());

        _open = open(NAME, O_RDWR);
        if (_open == -1) {
            perror("open() Error");
            exit(-1);
        }

        strcpy(_buffer, "Urbán Milán T6PXGV\0");
        write(_open, _buffer, SIZE);

        close(_open);

		exit(1);
	} else { // parent
        printf("%d: I'm a parent [1.]\n", getpid());

        _fifo = mkfifo(NAME, 0666);
        if (_fifo == -1) {
            perror("mkfifo() Error");
            exit(-1);
        }
        close(_fifo);

		wait(NULL);

        printf("%d: I'm a parent [2.]\n", getpid());

        _open = open(NAME, O_RDWR);
        if (_open == -1) {
            perror("open()");
            exit(-1);
        }

        printf("0\n");

        while (read(_fifo, _buffer, SIZE) > 0) {
            printf("%s", _buffer);                                  // olvasok
        }
        printf("\n");

        close(_open);
        unlink(NAME);

        exit(1);
	}
    return 0;
}
