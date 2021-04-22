#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSGKEY 654311L
#define SIZE 2

struct msgbuf1 {
	long mtype;
	int  mtext[SIZE+1];
} message, *msgPointer;

int main() {
    int mymsg;
	key_t mykey;
	int myflag;
	int myreturn, mysize;
    int i;

	mykey = MSGKEY;
	myflag = 00666 | IPC_CREAT;
	mymsg = msgget(mykey, myflag);
	if (mymsg == -1) {
		perror("Hiba!");
		exit(-1);
	}
	printf("Sikeres letrehozas: %d, %x\n", mymsg, mymsg);
	msgPointer = &message;
	msgPointer->mtype = 0;

	for (i = 1; i < SIZE + 1; i++) {
		printf("Szamot pls: %d\n",i);
		scanf("%d", &(msgPointer->mtext[i]));
		printf("%d", msgPointer->mtext[i]);
	}
	mysize = sizeof(int) * (SIZE + 1);
	myreturn = msgsnd(mymsg, (struct msgbuf *)msgPointer, mysize, myflag);
	printf("Visszateresi ertek: %d\n", myreturn);
	printf("Uzenet: %s\n", msgPointer->mtext);

	exit(0);
}
