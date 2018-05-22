#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
int main(){
    pid_t pid;
    pid = fork();
    if(pid>0){
        sleep (10);
		
    }else{
        exit(0);
		    }
    if(pid<0){
        printf("Fork Failed");
    }
}
