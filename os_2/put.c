#include "os_2.h"

int main(){
	int semid = semget((key_t)KEY, 4, IPC_CREAT|0666);
	int shmidt;
	char end[20] = "";
	char *T;
	int fd;
	int i=0;

	fd = open(FILE_PATH_DES, O_CREAT|O_WRONLY|O_TRUNC, 0666);
	if(fd == -1){
		printf("can not open des.txt\n");
		exit(1);
	}

	shmidt = shmget((key_t)KEYT, 20, IPC_CREAT|0666);
	T = (char*)shmat(shmidt, NULL, SHM_R|SHM_W);

	while(1){
        i++;
		P(semid, 3);//T is full, then put can start
		if(strcmp(T, end) == 0){
			printf("put is end %d\n", i);
			break;
		}
		write(fd, T, strlen(T));
		V(semid, 2);//T is empty, then copy can start
	}

	shmdt(T);
	shmctl(shmidt, IPC_RMID, 0);

	close(fd);
	return 0;
}

