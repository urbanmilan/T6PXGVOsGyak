
/*14. Irjon C nyelvu programokat, ami
    hozzon letre egy osztott memoria szegmenst
    a felhasznalotol olvasson be szoveget, es ezt irja be az osztott memoria teruletere es kuldjon signalt a fogado
    felnek, hogy kesz az uzenet (SIGUSR1)
    (segitsegkeppen a masik program pid-je fixen beleteheto a programba)
    a masik program pedig olvass ki az osztott mem szegmensbol, de csak egy adott signal hatasara (SIGUSR1)
    vegul szuntesse meg az shm szegmenst*/

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


int main(int argc, char *argv[])
{
    key_t key= 111; //shm kulcsa
    int shmid;
        char *guess_mem, *userinput;
        if(( shmid = shmget(key,1024,0666|IPC_CREAT)) < 0 ){ //osztott memória kreálása (kulcs, méret, jogosultság | creálásmód)
                perror("shmget"); // error kezelés
                exit(1);
        }

    int f,pid;
    

        f = open("myfifo", O_RDONLY); //fifo nyit
        
        read(f, &pid, sizeof(int)); //pid kiolvas
        close(f);
        unlink("myfifo"); //bezár minden
        printf("read pid: %d \n", pid);
        printf("Adja meg az üzenetet: ");
    
    size_t len = 0;
    ssize_t lineSize = 0;

    if ((guess_mem = shmat(shmid,NULL,0)) == (char *) -1){ //osztott mem hez csatlakozás
                perror("shmat"); //error kezelés
                exit(1);
        }
    lineSize = getline(&userinput, &len, stdin); //get user input
    strcpy(guess_mem, userinput); // inputot az osztott memóriába másoljuk
    shmdt(guess_mem); //lecsatlakozás az osztott mem
    kill(pid, SIGUSR1); //signal küld
    exit(0); //kilép
    return 0;
}