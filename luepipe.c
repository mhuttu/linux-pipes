#include <stdio.h> // printf, fprintf, perror
#include <sys/types.h> // I/O constants
#include <sys/stat.h> // open
#include <fcntl.h> // open
#include <unistd.h> // read, write, close, lseek, getpid
#include <stdlib.h> // exit, system

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int lukuputki;
    char fifoputki[] = "./testiputki";
    char buffer[BUFFER_SIZE];
    ssize_t readCount;


    lukuputki = open(fifoputki, O_RDONLY);
    if (lukuputki == -1) {
      // error opening file
      // use perror to display error string
      perror("While opening source pipe\n");
      // terminate program with exit code 2 (another way of
      // terminating main, but this would work anywhere
      // inside our program, not just main).
      exit(2);
    }

    while (1) {
    readCount = read(lukuputki, buffer, BUFFER_SIZE);
    if (readCount > 0)
        {
        fprintf(stdout, buffer);
        }
    else
        break;
    }
     close(lukuputki);

    return 0;
}
