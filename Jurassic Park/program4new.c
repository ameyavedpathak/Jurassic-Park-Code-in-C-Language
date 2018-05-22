
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<ctype.h>
int min,max;
float avg; 
int len =0;
void *min_thread(void *param); 
void *max_thread(void *param);
void *avg_thread(void *param);
int main(int argc, char *argv[])
{
	int *numbers = (int*)malloc((argc - 1)*sizeof(int));
	int i;
	int j;
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3; 
	pthread_attr_t attribute1;
	pthread_attr_t attribute2;
	pthread_attr_t attribute3; 
	
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"%d must be >= 0 \n",atoi(argv[1]));
		return -1;
	}
	for(i=1;i<argc;i++){
		numbers[i-1]=atoi(argv[i]);
		len++;
	}
	for(j=0;j<len;j++){
		printf("%d\t",(numbers[j]));
	}
	/* get the default attributes */
	pthread_attr_init(&attribute1);
	pthread_attr_init(&attribute2);
	pthread_attr_init(&attribute3);
	/* create the thread */
	
	printf("\n");
	pthread_create(&thread1,&attribute1,min_thread,(void*)numbers);
	pthread_create(&thread2,&attribute2,max_thread,(void*)numbers);
	pthread_create(&thread3,&attribute3,avg_thread,(void*)numbers);

	/* an array of threads to be joined upon */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("Min = %d \t",min);
	printf("max = %d \t",max);
	printf("Avg = %.2f \t",avg);
}

void *min_thread(void *param){
	int k;
	int *numbers = (int *) param;
	min=numbers[0];
	for(k = 0; k < len; k++)
	{
	    if(numbers[k]<min){
    		min = numbers[k];
    	}
	 }
    pthread_exit(0);
}
void *max_thread(void *param){
    int m;
	int *numbers = (int *) param;
	max=numbers[0];
	for(m = 0; m < len; m++)
	{
	    if(numbers[m]>max){
    		max = numbers[m];
    	}
	 }
        pthread_exit(0);
}
void *avg_thread(void *param){
 int n;
 int *numbers = (int *) param;
  int totalsum = 0;
  for(n = 0; n < len; n++)
  {
    totalsum = totalsum + numbers[n];
  }
  
  avg = totalsum / (len);
  pthread_exit(0);
}
