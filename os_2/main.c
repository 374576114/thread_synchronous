#include "os_2.h"

#define GET "./get"
#define COPY "./copy"
#define PUT "./put"

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int main(){
	int semid = semget((key_t)KEY, 4, IPC_CREAT|0666);
	union semun arg1, arg0;
	int shmids, shmidt;
	char*S, *T;
	char init[20] ="123";
	pid_t p1, p2, p3;


	arg1.val = 1;
	arg0.val = 0;

	semctl(semid, 0, SETVAL, arg1);// 1: S is empty (copy end)
	semctl(semid, 1, SETVAL, arg0);// 1: S is full  (get end )
	semctl(semid, 2, SETVAL, arg1);// 1: T is empty (put end )
	semctl(semid, 3, SETVAL, arg0);// 1: T is full  (copy end)

	shmids = shmget((key_t)KEYS, 20, IPC_CREAT|0666);
	shmidt = shmget((key_t)KEYT, 20, IPC_CREAT|0666);

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

