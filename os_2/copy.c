#include "os_2.h"

int main(){
	int semid = semget((key_t)KEY, 4, IPC_CREAT|0666);
	int shmids, shmidt;
	char end[20] = "";
	char* S, *T;
	int i=0;

	shmids = shmget((key_t)KEYS, 20, IPC_CREAT|0666);
	shmidt = shmget((key_t)KEYT, 20, IPC_CREAT|0666);
	S = (char*)shmat(shmids, NULL, SHM_R|SHM_W);
	T = (char*)shmat(shmidt, NULL, SHM_R|SHM_W);

	while(1){
        i++;
		P(semid, 1);//S is full
		P(semid, 2);//T is empty , then copy can start
		strncpy(T, S, 20);
		if(strcmp(T, end) == 0){
			printf("copy is end, %d\n", i);
			V(semid, 3);
			break;
		}
		V(semid, 3);// T is full, then put can start
		V(semid, 0);// S is empty, then get can start
	}

    shmdt(S);
    shmdt(T);
	shmctl(shmids, IPC_RMID, 0);
	shmctl(shmidt, IPC_RMID, 0);

	return 0;
}
