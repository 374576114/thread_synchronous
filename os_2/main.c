#include "os_2.h"

#define GET "./get"
#define COPY "./copy"
#define PUT "./put"

int main(){
	int semid = semget((key_t)1234, 4, IPC_CREAT|0666);
	//union semun arg;
	int shmids, shmidt;
	char*S, *T;
	char init[20] ="123";
	pid_t p1, p2, p3;

	int arg = 0;

	semctl(semid, 0, SETVAL, arg);
	semctl(semid, 1, SETVAL, arg);
	semctl(semid, 2, SETVAL, arg);
	semctl(semid, 3, SETVAL, arg);

	shmids = shmget((key_t)1235, 20, IPC_CREAT|0666);
	shmidt = shmget((key_t)1236, 20, IPC_CREAT|0666);

	S = (char*)shmat(shmids, NULL, 0);
	T = (char*)shmat(shmidt, NULL, SHM_R|SHM_W);

	strncpy(S,init, 20);
	strncpy(T,init, 20);

	if((p1=fork()) == 0){
		execv("./get", NULL);
	}else if((p2=fork()) == 0){
		execv("./copy", NULL);
	}
	else if((p3=fork()) == 0){
		execv("./put", NULL);
	}


	while(wait(NULL) > 0);

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

