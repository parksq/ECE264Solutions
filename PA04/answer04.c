/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */


void partitionAll(int n)
{
  void partition(int*,int,int);
  int arr[MAXLENGTH];
  partition(arr,n,0);
  printf("partitionAll %d\n", n);
  
}

void partition(int * arr,int n, int ind)
{
  int val;
  int i;
  if (n == 0) //prints results
  {
    printf("= %d",arr[0]);
    for (i = 1; i < ind; i++)
    {
      printf(" + %d", arr[i]);
    }
    printf("\n");
  }
  for (val = 1; val <= n; val++) //recursive function
  {
    arr[ind] = val; //defines the first term
    partition(arr, n - val, ind + 1); //partitions the rest
  }
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionIncreasing(int n)
{
  void partitionInc(int*,int,int,int);
  int arr[MAXLENGTH];
  partitionInc(arr,n,0,0);
  printf("partitionIncreasing %d\n", n);
}

void partitionInc(int * arr,int n, int ind, int start)
{
  int val;
  int i;
  if (n == 0)
  {
    printf("= %d",arr[0]);
    for (i = 1; i < ind; i++)
    {
      printf(" + %d", arr[i]);
    }
    printf("\n");
  }
    for (val = 1; val <= n; val++)
    {
      if (val > start)
      {
        arr[ind] = val;
        partitionInc(arr, n - val, ind + 1,val);
      }
    }
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionDecreasing(int n)
{
  void partitionDec(int*,int,int,int);
  int arr[MAXLENGTH];
  partitionDec(arr,n,0,n+1);
  printf("partitionDecreasing %d\n", n);
}

void partitionDec(int * arr,int n, int ind, int start)
{
  int val;
  int i;
  if (n == 0)
  {
    printf("= %d",arr[0]);
    for (i = 1; i < ind; i++)
    {
      printf(" + %d", arr[i]);
    }
    printf("\n");
  }
    for (val = 1; val <= n; val++)
    {
      if (val < start)
      {
        arr[ind] = val;
        partitionDec(arr, n - val, ind + 1,val);
      }
    }
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOdd(int n)
{
  void partitionO(int*,int,int);
  int arr[MAXLENGTH];
  partitionO(arr,n,0);
  printf("partitionOdd %d\n", n);
}

void partitionO(int * arr,int n, int ind)
{
  int val;
  int i;
  if (n == 0)
  {
    printf("= %d",arr[0]);
    for (i = 1; i < ind; i++)
    {
      printf(" + %d", arr[i]);
    }
    printf("\n");
  }
    for (val = 1; val <= n; val++)
    {
      if (val%2)
      {
        arr[ind] = val;
        partitionO(arr, n - val, ind + 1);
      }
    }
}


/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEven(int n)
{
  void partitionE(int*,int,int);
  int arr[MAXLENGTH];
  partitionE(arr,n,0);
  printf("partitionEven %d\n", n);

}

void partitionE(int * arr,int n, int ind)
{
  int val;
  int i;
  if (n == 0)
  {
    printf("= %d",arr[0]);
    for (i = 1; i < ind; i++)
    {
      printf(" + %d", arr[i]);
    }
    printf("\n");
  }
    for (val = 1; val <= n; val++)
    {
      if ((val+1)%2)
      {
        arr[ind] = val;
        partitionE(arr, n - val, ind + 1);
      }
    }
}


/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partitionOddAndEven(int n)
{
  void partitionOE(int*,int,int,int);
  int arr[MAXLENGTH];
  partitionOE(arr,n,0,0);
  printf("partitionOddAndEven %d\n", n);
  
}

void partitionOE(int * arr,int n, int ind,int start)
{
  int val;
  int i;
  if (n == 0)
  {
    printf("= %d",arr[0]);
    for (i = 1; i < ind; i++)
    {
      printf(" + %d", arr[i]);
    }
    printf("\n");
  }
    for (val = 1; val <= n; val++)
    {
      if (((start%2) & (val+1%2)) | ((start+1%2) & val%2))
      {
        arr[ind] = val;
        partitionOE(arr, n - val, ind + 1, val);
      }
    }
}


/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */



void partitionPrime(int n)
{
  int IsPrime(int);
  void partitionP(int*,int,int);
  int arr[MAXLENGTH];
  partitionP(arr,n,0);
  printf("partitionPrime %d\n", n);
}

int IsPrime(int n)
{
  int i;
  if (n == 1)
    return(0);
  for (i = 2; i < n; i++)
  {
    if (n%i == 0)
    {
      return(0);
    }
  }
  return(1);
}

void partitionP(int * arr,int n, int ind)
{
  int val;
  int i;
  if (n == 0)
  {
    printf("= %d",arr[0]);
    for (i = 1; i < ind; i++)
    {
      printf(" + %d", arr[i]);
    }
    printf("\n");
  }
    for (val = 1; val <= n; val++)
    {
      if (IsPrime(val))
      {
        arr[ind] = val;
        partitionP(arr, n - val, ind + 1);
      }
    }
}

