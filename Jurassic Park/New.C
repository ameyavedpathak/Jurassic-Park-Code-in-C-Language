#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
int main(){
	int pid;
	pid = fork();
	if(pid>0){
		exit(0);
	}else{
		sleep(0);
	}
	if(pid<0){
		sprintf("Fork Failed");
	}
}