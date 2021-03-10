#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void)
{
    pid_t asd;
    int status;
    if ( ( asd = fork()) < 0) perror("hiba");
    else if (asd == 0) exit(11);
    if (wait(&status) != asd) perror("idotullepes");
    if (WIFEXITED(status)) printf("Normális befejezés %d\n", WEXITSTATUS(status));

    if ( ( pid = fork()) < 0) perror("hiba");
        else if (asd == 0) abort();
        if (wait(&status) != asd) perror("idotullepes");
        if (WIFSIGNALED(status)) printf("Nem normális befejezés %d\n", WTERMSIG(status));

    if ( ( pid = fork()) < 0) perror("hiba");
        else if (asd == 0) {int a; int b = 0; a = 10 / b;}
        if (wait(&status) != asd) perror("idotullepes");
        if (WIFSIGNALED(status)) printf("Nem normális befejezés %d\n", WTERMSIG(status));

    exit(0);
}
