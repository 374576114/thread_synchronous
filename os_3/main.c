#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

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
		if(S_ISDIR(statbuf.st_mode) ){
			if(!strcmp(entry->d_name, ".")
				|| ! strcmp(entry->d_name, "..")){
				continue;
			}
			printf("%*s%3d %s/\n", depth, "", depth, entry->d_name);
			printdir(entry->d_name, depth+4);
		}else{
			printf("%*s%3d %s \n", depth, "", depth,entry->d_name);
		}
	}
	if(chdir("..") == -1){
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

//	printdir(d, depth);

	printdir("/home/craboyang/tmp", depth);
	return 0;
}
