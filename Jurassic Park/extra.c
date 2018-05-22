
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<ctype.h>
int min,max;
float avg; /* this data is shared by the thread(s) */
int len =0;
void *min_thread(void *param); /* threads call this function */
void *max_thread(void *param);
void *avg_thread(void *param);
int main(int argc, char *argv[])
{
	int *numbers = (int*)malloc((argc - 1)*sizeof(int));
	int i,j;
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3; /* the thread identifier */
	pthread_attr_t attribute1;
	pthread_attr_t attribute2;
	pthread_attr_t attribute3; /* set of thread attributes */
	/*if (argc != 2) {
		fprintf(stderr,"usage: a.out <integer value> \n");
	return -1;
	}*/
	if (atoi(argv[1]) < 0) {
		fprintf(stderr,"%d must be >= 0 \n",atoi(argv[1]));
		return -1;
	}
	for( i=1;i<argc;i++){
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
	pthread_create(&thread2,&attribute2,min_thread,(void*)numbers);
	pthread_create(&thread3,&attribute3,avg_thread,(void*)numbers);

	/* an array of threads to be joined upon */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("Min = %d \n",min);
	printf("Max = %d \n",max);
	printf("Avg = %.2f \n",avg);
}

void *min_thread(void *param){
	int *numbers = (int *) param;
	int k;
	min=numbers[0];
	for(k = 0; k < len; k++)
	{
	    if(min>numbers[k]){
    		min = numbers[k];
    	}
	 }
    pthread_exit(0);
}
void *max_thread(void *param){
    int *numbers = (int *) param;
	int l;
	max=numbers[0];
	for(l = 0; l < len; l++)
	{
	    if(max<numbers[l]){
    		max = numbers[l];
    	}
	 }
        pthread_exit(0);
}
void *avg_thread(void *param){
 int *numbers = (int *) param;
  int totalsum = 0;
  int o;
  for(o = 0; o < len; o++)
  {
    totalsum = totalsum + numbers[o];
  }
  
  avg = totalsum / (len);
  pthread_exit(0);
}