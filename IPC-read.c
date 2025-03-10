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

  // Generate the same key used by the writer
  key = ftok("shmfile", 'R');

  // Locate the shared memory segment
  shmid = shmget(key, SHM_SIZE, 0666);

  if (shmid < 0)
  {
    perror("shmget");
    exit(1);
  }

  // Attach the shared memory segment
  shm = shmat(shmid, NULL, 0);

  if (shm == (char *)-1)
  {
    perror("shmat");
    exit(1);
  }

  // Read from the shared memory
  ptr = shm;
  printf("Message read from shared memory: %s\n", ptr);

  // Detach the shared memory segment
  if (shmdt(shm) == -1)
  {
    perror("shmdt");
    exit(1);
  }

  // Mark the shared memory segment to be destroyed
  if (shmctl(shmid, IPC_RMID, NULL) == -1)
  {
    perror("shmctl");
    exit(1);
  }

  return 0;
}