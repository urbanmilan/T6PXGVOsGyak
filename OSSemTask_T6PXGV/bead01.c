#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>

void handle_sigusr1(int signum){
//      signal(SIGUSR1, handle_sigusr1);
//      printf("anyad");

        key_t key= 111;
        int shmid;
        char *guess_mem;
        if ((shmid = shmget(key,1024, 0666 | IPC_CREAT)) < 0){
                perror("shmget");
                exit(1);
        }
        if((guess_mem = shmat(shmid,NULL,0)) == (char *) -1){
                perror("shmat");
                exit(1);
        }

        printf("message: %s \n", guess_mem);
        shmdt(guess_mem);
        exit(0);
        //shmctl(shmid,P_PGID,NULL);
}

int main(int argc, char *argv[])
{

        int f, mypid = getpid();
        printf("mypid: %d\n",mypid);
        if(mkfifo("myfifo", 0666) < 0){
                perror("mkfifo"), exit(EXIT_FAILURE);
        }

        f=open("myfifo", O_WRONLY);
        write(f, &mypid, sizeof(int));
        close(f);

        signal(SIGUSR1, handle_sigusr1);
        while(1); //várunk a signálra
        return 0;
}
