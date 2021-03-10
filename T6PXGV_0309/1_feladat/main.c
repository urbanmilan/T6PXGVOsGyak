#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int system(const char *command);

int main()
{
    pid_t pid = fork();

    char cmd[32];
    int status;
    if(pid == 0){
        strcpy(cmd, "ls -l");
        system(cmd);
    }

    waitpid(pid, &status, 0);
    if(WIFEXITED(status) == 1){
        _exit(WEXITSTATUS(status));
    }

    return 0;
}
