#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int system(const char *command);

int main()
{
    char gets(char* strptr);
    char str[64];
    gets(str);

    char cmd[32];
    strcpy(cmd, str);
    system(cmd);
    return 0;
}
