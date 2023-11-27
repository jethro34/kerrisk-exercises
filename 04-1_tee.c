// The Linux Programming Interface - M. Kerrisk * Ex 4.1/p. 87

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  if (argc != 3) {
    //printf("%d", argc);
    printf("Usage: %s < inputfile > outputfile", argv[0]);
    exit(0);
  }

  int infd, outfd, numBs;

  if ((infd = open(argv[1], O_RDONLY)) == -1)
    perror("failure opening input file");
  if ((outfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC)) == -1)
    perror("failure opening output file");

  char* c; 
  while ((numBs = read(infd, &c, 1)) != 0) {
    if (numBs == -1) perror("failure reading from input file");
    else {
      putchar(*c);
      if ((numBs = write(outfd, &c, 1)) == -1)
        perror("failure writing to output file");
    }
  }

  return 0;
}
