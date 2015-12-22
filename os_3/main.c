#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
void printNote(){
	printf(" size   tpye  name  time\n");
}
void printInfo(struct stat * pstat, struct dirent * entry, int d, int b){
	printf("%*s", d, "");
	printf("%7ld ", pstat->st_size);
	if(S_ISDIR(pstat->st_mode))
	  printf(" 目录文件 ");
	else if (S_ISBLK(pstat->st_mode))
	  printf(" block ");
	else if(S_ISFIFO(pstat->st_mode))
	  printf(" fifo ");
	else if(S_ISLNK(pstat->st_mode))
	  printf(" link ");
	else if(S_ISREG(pstat->st_mode))
	  printf(" 普通文件 ");
	else
	  printf("xxx ");
	printf("%12s", entry->d_name);
	if(b)
	  printf("/ ");
	else
	  printf(" ");
	printf("%s", ctime(& pstat->st_mtime));
}


void printdir(const char *dir, int depth){
	DIR *dp;
	struct dirent* entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL){
		perror("cannot open the dir\n");
		exit(1);
	}
	
	if(chdir(dir) == -1){
		perror("cannot change to the dir\n");
		exit(1);
	}

	while((entry = readdir(dp)) != NULL ){
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode) ){ //判断是否是目录
			if(!strcmp(entry->d_name, ".") //判断是. .. 两个目录
				|| ! strcmp(entry->d_name, "..")){
				continue;
			}
			//printf("%*s%3d %s/\n", depth, "", depth, entry->d_name);
			printInfo(&statbuf, entry , depth, 1);
			printdir(entry->d_name, depth+4);
		}else{
			printInfo(&statbuf, entry , depth, 0);
			//printf("%*s%3d %s \n", depth, "", depth,entry->d_name);
		}
	}
	if(chdir("..") == -1){//将当前目录转化成父目录
		perror("change to parentdir \n");
		exit(0);
	}
	closedir(dp);
}

int main(){
	char d[100];
	int depth=0;

//	printf("please input the dir\n");
//	scanf("%s", d);

	printNote();
	//printdir(d, depth);
	printdir("/home/craboyang/tmp", 0);
	return 0;
}
