#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
    int p,j,q;
    pid_t pid;

     printf( "Enter a number :");
       scanf("%d", &p);
       int numbers[14];
       numbers[0]=p;
       j=1;
       if(p<=0){
           printf("Enter Positive number\n");
           exit(0);
       }

       printf( "Number entered by you: %d\n ", p);


    
    pid = fork();

    if (pid < 0) { 
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { 
        while(p>1){
            if(p%2==0){
                p = p/2;
                
                numbers[j]=p;
                j++;
            }else{
                p = 3*p+1;
                
                numbers[j]=p;
                j++;
            }
        }
       for ( q = 0; q < j; q++ ) {
          printf("%d\n", numbers[q]);
       }
        
    }
    else { 
        wait(NULL);
    }
    return 0;
}
