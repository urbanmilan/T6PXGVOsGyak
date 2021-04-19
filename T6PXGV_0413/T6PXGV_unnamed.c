#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SIZE 64

int main() {
    int _pipe[2];
    int _pid;
    char _buffer[SIZE];

    if (pipe(_pipe) == -1) {                                        // pipe hiba kezeles
        perror("pipe() Error");
        exit(-1);
    }

    _pid = fork();
    if (_pid == -1) {                                               // fork hiba kezeles
        perror("fork() Error");
        exit(-1);
    }

    if (_pid == 0) {                                                // gyerek vagyok
        printf("%d: I'm a child\n", getpid());

        close(_pipe[0]);                                            // Lezárom mivel csak beleirok

        strcpy(_buffer, "Urbán MIlán T6PXGV\0");
        write(_pipe[1], _buffer, sizeof(_buffer));                  // szoveg irása

        close(_pipe[1]);                                            // lezárom
    } else {                                                        // szulo vagyok
        printf("%d: I'm a parent\n", getpid());

        close(_pipe[1]);                                            // lezárom mivel csak olvasok

        while (read(_pipe[0], _buffer, sizeof(_buffer)) > 0) {
            printf("%s", _buffer);                                  // olvasok
        }
        printf("\n");

        close(_pipe[0]);                                            // lezárom
    }
    wait(NULL);
    return 0;
}
