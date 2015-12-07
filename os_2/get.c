#include "os_2.h"

int main(){
	int semid = semget((key_t)1234, 4, IPC_CREAT|0666);
	int shmids, shmidt;
	int fd;
	int n;
	int i=0;
	char temp[20];
	char *S;
	char end[20] ="";
	fd = open(FILE_PATH_SRC, O_RDONLY);
	if(fd == -1){
		printf("cannot open the file\n");
		exit(1);
	}
	shmids = shmget((key_t)1235, 20, IPC_CREAT|0666);
	S = (char*)shmat(shmids, NULL, 0);

	do{
        i++;
		n = read(fd, &temp, sizeof(char)*19);
		strncpy(S, temp, n);
		S[n] = 0;
		if(n == 0){
			printf("end read, %d\n", i);
			strncpy(S, end, 20);
			V(semid, 1);
			break;
		}
		//printf("****get:\n %s %s\n", S, temp);
		//sleep(1);
		V(semid, 1);
		P(semid, 0);
	}while(1);

    shmdt(S);
	shmctl(shmids, IPC_RMID, 0);


//	semctl(semid, 0, IPC_RMID, NULL);
//	semctl(semid, 1, IPC_RMID, NULL);
//	semctl(semid, 2, IPC_RMID, NULL);
//	semctl(semid, 3, IPC_RMID, NULL);

	close(fd);
	return 0;
}

