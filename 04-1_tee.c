// The Linux Programming Interface - M. Kerrisk * Ex 4.1/p. 87

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 64

int main(int argc, char* argv[])
{
  if (argc != 2) {
    printf("Usage: %s outputfile", argv[0]);
    exit(0);
  }

  int outfd, numBs;

  if ((outfd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC)) == -1)
    perror("failure opening output file");
  
  char* buffer[BUFFER_SIZE+1];
  for (int i=0; i<BUFFER_SIZE+1; i++)
    buffer[i] = malloc(sizeof(char));

  if ((numBs = read(STDIN_FILENO, buffer, BUFFER_SIZE)) == -1)
    perror("failure reading from input file");
  buffer[numBs] = '\0'; 

  if ((numBs = write(STDOUT_FILENO, buffer, numBs)) == -1)
    perror("failure writing to stdout");
  if ((numBs = write(outfd, buffer, numBs)) == -1)
    perror("failure writing to output file");

  for (int i=0; i<BUFFER_SIZE+1; i++)
    free(buffer[i]);

  return 0;
}
