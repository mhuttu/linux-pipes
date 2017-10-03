#include <stdio.h> // printf, fprintf, perror
#include <sys/types.h> // I/O constants
#include <sys/stat.h> // open
#include <fcntl.h> // open
#include <unistd.h> // read, write, close, lseek, getpid
#include <stdlib.h> // exit, system

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    int result, lukutiedosto =-1;
    int kirjoitaputkeen;
    char fifoputki[] = "./testiputki";
    char buffer[BUFFER_SIZE];
    ssize_t readCount;


    lukutiedosto = open("./luettava.txt", O_RDONLY);
    if (lukutiedosto <= 0) {
      // error opening file
      // use perror to display error string
      perror("While opening source file\n");
      // terminate program with exit code 2 (another way of
      // terminating main, but this would work anywhere
      // inside our program, not just main).
      exit(2);
    }
    fprintf(stderr, "FD %d -> source file\n", lukutiedosto);
/*    result = mkfifo(fifoputki, 0777);
    if (result != 0)
    {
        perror("FIFO putken luonti ei onnistunut\n");
        exit(2);
    }*/
    kirjoitaputkeen = open (fifoputki, O_WRONLY);

    while (1) {
    readCount = read(lukutiedosto, buffer, BUFFER_SIZE);
    if (readCount > 0)
        {
        result = write(kirjoitaputkeen, buffer, sizeof(buffer));
        if(result > 0)
            printf("kirjtoitettu putkeen %d\n", result);
        }
    else
    {
        break;
    }
    }
     close(kirjoitaputkeen);
     close(lukutiedosto);

    return 0;
}
