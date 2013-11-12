#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

int main(int argc, char ** argv )
{
  if (argc != 3)
  {
    printf("Error: need more inputs\n");
    return EXIT_FAILURE;
  }
  FILE * file = fopen(argv[1],"r");
  if (file == NULL)
  {
    printf("Error: file failed to open\n");
    return EXIT_FAILURE;
  }
  int size = 0;
  char temp = 0;
  while (fscanf(file,"%c",&temp) == 1)
  {
    size++;
  }
  char * data;
  data = malloc(sizeof(char)*size);
  fseek(file,0,SEEK_SET);
  int i = 0;
  while (fscanf(file,"%c",&data[i]) == 1)
  {
    i++;
  }
  fclose(file);
  HuffNode * root = NULL;
  root = build(root,data);
  return 0;
}
