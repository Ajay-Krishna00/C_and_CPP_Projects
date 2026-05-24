#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{
  int shmid;
  key_t key;
  char *shm, *ptr;

  // Generate a key
  key = ftok("shmfile", 'R');

  // Create the shared memory segment
  shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

  // Attach the shared memory segment
  shm = shmat(shmid, NULL, 0);

  // Write to the shared memory
  ptr = shm;
  sprintf(ptr, "Hello, shared memory!");
  printf("data written to shared memory \n");
  // Detach the shared memory segment
  shmdt(shm);

  return 0;
}