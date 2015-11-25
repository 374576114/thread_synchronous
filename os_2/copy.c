#include "os_2.h"

int main(){
	int semid = semget((key_t)1234, 4, IPC_CREAT|0666);
	int shmids, shmidt;
	char end[20] = "";
	char* S, *T;
	int i=0;

	shmids = shmget((key_t)1235, 20, IPC_CREAT|0666);
	shmidt = shmget((key_t)1236, 20, IPC_CREAT|0666);
	S = (char*)shmat(shmids, NULL, SHM_R|SHM_W);
	T = (char*)shmat(shmidt, NULL, SHM_R|SHM_W);

	while(1){
        i++;
		P(semid, 1);
		strncpy(T, S, 20);
		if(strcmp(T, end) == 0){
			printf("copy is end, %d\n", i);
			V(semid, 3);
			break;
		}
		//strncpy(T, S, 20);
		V(semid, 3);
		V(semid, 0);
		P(semid, 2);
		//printf("***copy:\n %s %s\n", S, T);
		//sleep(1);
	}

    shmdt(S);
    shmdt(T);
	shmctl(shmids, IPC_RMID, 0);
	shmctl(shmidt, IPC_RMID, 0);

	semctl(semid, 0, IPC_RMID, NULL);
	semctl(semid, 1, IPC_RMID, NULL);
	semctl(semid, 2, IPC_RMID, NULL);
	semctl(semid, 3, IPC_RMID, NULL);

	return 0;
}
