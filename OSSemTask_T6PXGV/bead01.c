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

void handle_sigusr1(int signum){ // signal lekezelő method

        key_t key= 111; //shm kulcs
        int shmid;
        char *guess_mem;
        if ((shmid = shmget(key,1024, 0666 | IPC_CREAT)) < 0){ //shm 
                perror("shmget");
                exit(1);
        }
        if((guess_mem = shmat(shmid,NULL,0)) == (char *) -1){ // shm csatlakozás
                perror("shmat");
                exit(1);
        }

        printf("message: %s \n", guess_mem); // kiírja az üzenetet
        shmdt(guess_mem);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
}

int main(int argc, char *argv[])
{

        int f, mypid = getpid(); // saját pid
        printf("mypid: %d\n",mypid); 
        if(mkfifo("myfifo", 0666) < 0){ // kreál fifo
                perror("mkfifo"), exit(EXIT_FAILURE);
        }

        f=open("myfifo", O_WRONLY); // nyit fifo
        write(f, &mypid, sizeof(int)); // beír pid
        close(f);
        unlink("myfifo"); 

        signal(SIGUSR1, handle_sigusr1); // signal lekezelő beállítása
        while(1); //várunk a signálra
        return 0;
}
