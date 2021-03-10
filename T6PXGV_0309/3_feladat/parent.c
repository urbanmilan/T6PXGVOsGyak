#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void)
{
    pid_t asd;
    if ( ( asd = fork()) < 0) perror("hiba");
    else if (asd == 0) execl("./child.out", "child", NULL);
    if (waitpid(asd, NULL, 0) < 0) perror("idotullepes");
    exit(0);
}
