// System Calls

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

int main()
{
  pid_t p = fork();
  printf("Helloo\n");

  if (p < 0)
    printf("Fork failed! No child is being created\n");
  else if (p == 0)
  {
    printf("Child Process running. ID of Child is:%d\n", getpid());
    printf("ID of Parent is:%d\n", getppid()); // get parent process id
    printf("Now listing the files in the current directory in long format.\n");
    // exec() replaces the current process image with the specified program
    execl("/bin/ls", "ls", "-l", NULL); // exec() does not return on success
    printf("This won't show if execl succeds");
    // If exec() fails, print error message
    perror("exec failed");
    exit(1);
  }
  else if (p > 0)
  {
    // Parent process: wait for child to complete
    printf("Parent process (PID: %d), waiting for child...\n", getpid());
    wait(NULL);
    printf("Parent Process is Runing.ID of Child is:%d\n", p);
    struct stat fs;
    char *fname = "trial3.txt";
    if (stat(fname, &fs) == -1)
    {
      perror("stat failed");
      exit(1);
    }
    printf(" FileName: %s\n FileSize: %ld\n OwnerUID: %d\n GroupUID: %d\n LastModified: %ld\n Permissions: %o\n", fname, fs.st_size, fs.st_uid, fs.st_gid, fs.st_mtime, fs.st_mode & 0777);

    char *d = "."; // Use current directory
    DIR *dir = opendir(d);
    if (dir == NULL)
    {
      perror("opendir failed");
      return 1;
    }
    printf("Contents of the directory are:");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
      printf("%s\n", entry->d_name);
    }
    closedir(dir);
    int file = open("trial3.txt", O_RDONLY);
    if (file == -1)
    {
      perror("open failed");
      return 1;
    }
    printf("Successfully opened the file 'example.txt' with file descriptor: %d\n", file);

    // Close the file using close()
    close(file);
    printf("Successfully closed the file\n");

    printf("Now Testing exit() system call\n");
    exit(0);
    printf("This won't be printed :)");
  }
}