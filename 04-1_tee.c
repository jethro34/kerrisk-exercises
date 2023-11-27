// The Linux Programming Interface - M. Kerrisk * Ex 4.1/p. 87

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
  // check usage
  if (argc != 2) err(0, "Usage: %s outputfile", argv[0]);

  // variable declarations
  int outfd, numBs;   // file descriptor & bytes read/written
  char* buffer;       // buffer string

  // dynamically allocate memory for buffer
  buffer = malloc((BUFFER_SIZE+1) * sizeof(char));
  if (buffer == NULL) err(1, "failure mallocking");

  // get input & load it to buffer
  if ((numBs = read(STDIN_FILENO, buffer, BUFFER_SIZE)) == -1)
    err(1, "failure reading from input file");
  buffer[numBs] = '\0';   // null-terminate buffer

  // open output file for writing
  if ((outfd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC)) == -1)
    err(1, "failure opening output file");
 
  // write buffer to stdout
  if ((numBs = write(STDOUT_FILENO, buffer, numBs)) == -1)
    err(1, "failure writing to stdout");

  // write buffer to ouput file
  if ((numBs = write(outfd, buffer, numBs)) == -1)
    err(1, "failure writing to output file");

  free(buffer);   // free dynamically allocated memory

  return 0;
}
