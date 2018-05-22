#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>  
 
sem_t sem_guest, sem_ride; 
int TRIPS;


void *Guest (void *p) 
{ 
  extern sem_t sem_ride, sem_guest; 
  int i, *index; 
   
  index = (int *)p; 
 
  for (i = 0; i < TRIPS; i++) 
    { 
      
      fprintf (stdout, "Guest% d arrived at museum\n", *index+1); 
      sleep (rand()%4); 
 
      
      sem_post (&sem_ride); 
      sem_wait (&sem_guest); 
       
      /* Guests are boarding the rides */
      fprintf (stdout, "Guest% d boarded the ride\n", *index+1); 
      sleep (rand()%3); 
 
      /* Guests finished with the rides. */
    } 
    fprintf (stdout, "Guest% d have done with his% d TRIPS.\n", *index+1, TRIPS); 
} 
 
//Ride are Processing
void *Ride (void *p) 
{ 
  int *index, ridess = 0; 
  extern sem_t sem_ride, sem_guest; 
  index = (int *) p; 
   
  /*The Ride is waiting for Guests*/
  while(1) 
    { 
      
        sem_wait (&sem_ride); 
       
      /*Take Rides*/
      sleep (rand()%3); 
       
        sem_post (&sem_guest); 
       
    }  
}
int main (){ 
     int GUEST;
	int RIDES;
	 
  printf("Enter the no of Guests:\n");
  scanf("%d",&GUEST);
  printf("Enter the no of Rides:\n");
  scanf("%d",&RIDES);
  printf("Enter the no of TRIPS:\n");
  scanf("%d",&TRIPS);
  
  pthread_t visi[GUEST], ride[RIDES]; 
  void *Ride (void *), *Guest (void *); 
  int i, v[GUEST]; 
  extern sem_t sem_ride, sem_guest; 
 
  sem_init (&sem_ride, 0, 0); 
  sem_init (&sem_guest, 0, 0); 
   
  srand (time (NULL));    
   
  for (i=0; i<GUEST; i++) 
  { 
    v[i] = i; 
    if (pthread_create (&visi[i], NULL, Guest, &v[i])) 
      exit (1); 
  } 
 
  for (i = 0; i < RIDES; i++) 
  { 
      v[i] = i; 
      if (pthread_create (&ride[i], NULL, Ride, &v[i])) 
   exit (1); 
  } 
   
  for (i=0; i<GUEST; i++) 
    pthread_join (visi[i], NULL); 
     
  printf("\nAll guests are finished with there Trips\n\n\tThank you for visiting\n"); 
} 
