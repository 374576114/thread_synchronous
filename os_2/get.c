#include "os_2.h"

int main(){
	int semid = semget((key_t)KEY, 4, IPC_CREAT|0666);
	int shmids, shmidt;
	int fd;
	int n;
	int i=0;
	char temp[20];
	char *S;
	char end[20] ="";//end 

	fd = open(FILE_PATH_SRC, O_RDONLY);
	if(fd == -1){
		printf("cannot open the file\n");
		exit(1);
	}
	shmids = shmget((key_t)KEYS, 20, IPC_CREAT|0666);
	S = (char*)shmat(shmids, NULL, 0);

	do{
		P(semid, 0);//S is empty and copy end;
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
		V(semid, 1);//S is full, then copy can start
	}while(1);

    shmdt(S);
	shmctl(shmids, IPC_RMID, 0);

	close(fd);
	return 0;
}

