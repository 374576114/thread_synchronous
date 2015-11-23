#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <unistd.h>

void P(int semid, int index);
void V(int semid, int index);
void* subp1();
void* subp2();
int semid;
pthread_t p1, p2;
int a = 0;

// p operation
void P(int semid, int index){
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);

	return ;
}
// v operation
void V(int semid, int index){
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);

	return;
}
// thread1 :print number
void *subp1(){
	while(1){
		P(semid, 1);//if v(s1), that can run

		//print somrhing...
		printf(" %d \n", a);
		sleep(1);//sleep 0.1
		//print end
		
		V(semid, 0);//v (s0), sub2 p(s1) can run
	}
}
// thread2: compute
void * subp2(){
	while(1){

		//compute something..
		if(a < 0){
			a = 0;
		}else{
			a += 1;
		}
		//compute end
		
		V(semid, 1);//v (s1), subp1 p(s1) can run
		P(semid, 0);//if v(s0), it will run
	}
}

int main(){
	union semun arg;
	arg.val = 0;//sem will be  0
	semid = semget((key_t)1234, 2, IPC_CREAT|0666);
	semctl(semid, 0, SETVAL, arg);
	semctl(semid, 1, SETVAL, arg);
	pthread_create(&p1, NULL, subp1, NULL);
	pthread_create(&p2, NULL, subp2, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	return 0;
}


