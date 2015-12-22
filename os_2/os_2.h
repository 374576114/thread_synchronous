#ifndef OS_2_H
#define OS_2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define FILE_PATH_SRC "./src.txt"
#define FILE_PATH_DES "./des.txt"
#define KEY  123456
#define KEYS 123457
#define KEYT 1234568

void P(int semid, int index);
void V(int semid, int index);
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
#endif
