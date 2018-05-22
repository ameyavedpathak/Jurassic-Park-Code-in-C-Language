#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  const char* name = "AMEYA";
  const int SIZE = 4096;
  int p;
  printf( "Enter number :");
  scanf("%d", &p);
  if(p<=0){
    printf("Enter Positive number\n");
    exit(0);
  }
  int shm_fd;
  void *ptr;
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  pid_t id = fork();
if (id == 0) {
    shm_fd = shm_open(name, O_RDWR, 0666);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    while (p > 1) {
        ptr += sprintf(ptr, "%d ", p);
        if (p % 2 == 0){
          p = p/2;
        }else{
          p = 3 * p + 1;
        } 
    }
   ptr += sprintf(ptr, "%d ", p);
} else {
    wait(NULL);
    printf("Pattern in Parent:\n");
    printf("%s\n", (char*) ptr);
    shm_unlink(name);
}
return 0;
}
