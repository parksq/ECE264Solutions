#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa05.h"
#define MAXIMUM_LENGTH 180

/*
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numInteger: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fscanf
 *
 * You do NOT know how many integers are in the file until you have
 * read it. Once you know how many integers there are, you can modify
 * the "numberOfIntegers" variable. (Note that this is a pointer, not
 * an integer) You must allocate memory to store the integers.
 * 
 * Once memory is allocated to store the integers, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 *
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read integeres is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readInteger(char * filename, int * numInteger)
{
  int size = 0;
  int temp;
  FILE * file;
  file = fopen(filename,"r");
  if (file == NULL)
  {
    return NULL;
  }
  while(fscanf(file,"%d",&temp) == 1)
  {
    size++;
  }
  int * intarr;
  intarr = malloc(size * sizeof(int));
  fseek(file,0,SEEK_SET);
  int i = 0;
  while (fscanf(file,"%d",&intarr[i]) == 1)
  {
    i++;
  }
  *numInteger = size;
  fclose(file);
  return(intarr);
}

/* ----------------------------------------------- */

/*
 * Read a file of strings. This is similar to readInteger. However,
 * each string is an array of characters. The function needs to
 * allocate memory for an array of strings, i.e., array of arrays of
 * characters. In other words, this is a two-dimensional array (thus,
 * char **).
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of strings (one
 * per line)
 * 
 * numString: pointer to store the number of strings in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of strings from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fgets. 
 * 
 * Remember that an array of strings is a two-dimensional array of
 * characters
 *
 * You do NOT know how many strings are in the file until you have
 * read it. Once you know how many strings there are, you can modify
 * the "numberOfStrings" variable. (Note that this is a pointer, not
 * an string) You must allocate memory to store the strings.
 * 
 * Once memory is allocated to store the strings, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 *
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read stringes is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of strings in the file.  For example, if
 * you write this
 *
 * char array[10000];
 * 
 *
 */

char * * readString(char * filename, int * numString)
{
  int size = 0;
  char buf[MAXIMUM_LENGTH];
  FILE * file;
  file = fopen(filename,"r");
  if (file == NULL)
  {
    return NULL;
  }
  while (fgets(buf,MAXIMUM_LENGTH,file) != NULL)
  {
    size++;
  }
  *numString = size;
  char * * strarr = malloc(sizeof(char*)*size);
  fseek(file,0,SEEK_SET);
  if (fgets(buf,MAXIMUM_LENGTH,file) == 0)
  {
    return NULL;
  }
  int i = 0;
  fseek(file,0,SEEK_SET);
  while (fgets(buf,MAXIMUM_LENGTH,file) != 0)
  {
    strarr[i] = malloc(sizeof(char)*(strlen(buf)+1));
    strcpy(strarr[i],buf);
    i++;
  }
  fclose(file);
  return(strarr);
}

/* ----------------------------------------------- */
/*
 * print an array of integers, one integer per line
 */
void printInteger(int * arrInteger, int numInteger)
{
  int i;
  printf("%d",arrInteger[0]);
  for (i = 1;i < numInteger; i++)
  {
    printf("\n%d",arrInteger[i]);
  }
}

/* ----------------------------------------------- */
/*
 * print an array of strings, one string per line
 *
 * Hint: printf("%s" ... can print a string
 */
void printString(char * * arrString, int numString)
{
  int i;
  for (i = 0; i < numString; i++)
  {
    printf("%s", arrString[i]);     
    int len = strlen(arrString[i]);     
    if(len == 0 || arrString[i][len-1] != '\n') 
    {
      printf("\n");
    }
  }
}

/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of integers
 */
void freeInteger(int * arrInteger, int numInteger)
{
  free(arrInteger);
}

/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of strings
 *
 * Hint: an array of strings is a two-dimensional array of characters
 */
void freeString(char * * arrString, int numString)
{
  int i;
  for (i = 0;i < numString; i++)
  {
    free(arrString[i]);
  }
  free(arrString);
}

/* ----------------------------------------------- */
/*
 * Write integers to a file, one integer per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrInteger: an array of integers
 * numInteger: the number of integers 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %d
 *
 */

int saveInteger(char * filename, int * arrInteger, int numInteger)
{
  int i;
  FILE * file;
  file = fopen(filename,"w");
  if (file == NULL)
  {
    return 0;
  }
  fprintf(file,"%d",arrInteger[0]);
  for( i = 1;i<numInteger;i++)
  {
    fprintf(file,"\n%d",arrInteger[i]);
  }
  return 0;
}

/* ----------------------------------------------- */
/*
 * Write strings to a file, one string per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrString: an array of strings
 * numString: the number of strings 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %s
 *
 */

int saveString(char * filename, char * * arrString, int numString)
{
  int i;
  FILE * file;
  file = fopen(filename,"w");
  if (file == NULL)
  {
    return 0;
  }
  for (i=0;i<numString;i++)
  {
    fprintf(file,"%s",arrString[i]);
  }
  return 1;
}

/* ----------------------------------------------- */
/*
 * sort an arry of integers by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 */

void sortInteger(int * arrInteger, int numInteger)
{
  int compint(const void *,const void *);
  qsort(arrInteger,numInteger,sizeof(int),compint);
}

int compint(const void * p1, const void * p2)
{
  return (*(int*)p1 - *(int*)p2);
}

/* ----------------------------------------------- */
/*
 * sort an arry of strings by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 * Hint: use strcmp in the comparison function
 *
 */


void sortString(char * * arrString, int numString)
{
  int compstr(const void *, const void *);
  qsort(arrString,numString,sizeof(char*),compstr);
}

int compstr(const void * s1, const void * s2)
{
  char * a = *(char * *) s1;
  char * b = *(char * *) s2;
  return (strcmp(a,b));
}

