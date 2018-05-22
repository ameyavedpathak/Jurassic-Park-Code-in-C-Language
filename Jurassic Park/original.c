#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<ctype.h>
int min,max;
float avg; 
int length =0;
void *minimum(void *param); 
void *maximum(void *param);
void *average(void *param);
int main(int argc, char *argv[])
{
	int *numbers = (int*)malloc((argc - 1)*sizeof(int));

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
	for(int i=1;i<argc;i++){
		numbers[i-1]=atoi(argv[i]);
		length++;
	}
	for(int i=0;i<length;i++){
		printf("%d\t",(numbers[i]));
	}
	
	
	printf("\n");
	pthread_create(&thread1,&attribute1,minimum,(void*)numbers);
	pthread_create(&thread2,&attribute2,maximum,(void*)numbers);
	pthread_create(&thread3,&attribute3,average,(void*)numbers);

	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("Minimum = %d \n",min);
	printf("Maximum = %d \n",max);
	printf("Average = %.2f \n",avg);
}

void *minimum(void *param){
	int *numbers = (int *) param;
	min=numbers[0];
	for(int i = 0; i < length; i++){
	    if(numbers[i]<min){
    		min = numbers[i];
    	}
	 }
    pthread_exit(0);
}
void *maximum(void *param){
    int *numbers = (int *) param;
	max=numbers[0];
	for(int i = 0; i < length; i++){
	    if(numbers[i]>max){
    		max = numbers[i];
    	}
	 }
        pthread_exit(0);
}
void *average(void *param){
 int *numbers = (int *) param;
  int sum = 0;
  for(int i = 0; i < length; i++){
    sum += numbers[i];
  }
  avg = sum / (length);
  pthread_exit(0);
}