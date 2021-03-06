
#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * stack = malloc(sizeof(Stack));
  stack -> list = NULL;
  return stack;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
  if (stack == NULL)
  {
    return;
  }
void destroy_help(ListNode *);
  ListNode * head = stack -> list;
  destroy_help(head);
  free(stack);
}

void destroy_help(ListNode * head)
{
  if (head == NULL)
  {
    return;
  }
  destroy_help(head -> next);
  free(head);
}
/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if (stack -> list == NULL)
  {
    return TRUE;
  }
  return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
  if (stack == NULL)
  {
    return -1;
  }
  ListNode * n = stack -> list -> next;
  int value = stack -> list -> value;
  free(stack -> list);
  stack -> list = n;
  return(value);
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  ListNode * top = malloc(sizeof(ListNode));
  top -> value = value;
  top -> next = stack -> list;
  stack -> list = top;
  return;
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len)
{
if (isStackSortable(array,len))
{
  int i;
  int sorted[len];
  int value;
  int j = 0;
  Stack * stack = Stack_create();
  Stack_push(stack,array[0]);
  for (i=1;i<len;i++)
  {
    if(!Stack_isEmpty(stack) && array[i] > stack -> list -> value)
    {
      while(!Stack_isEmpty(stack) && array[i] > stack -> list -> value)
      {
        value = Stack_pop(stack);
        sorted[j] = value;
        j++;
      }
      Stack_push(stack,array[i]);
    }
    else
    {
      Stack_push(stack,array[i]);
    }
  }
  while (stack -> list != NULL)
  {
    value = Stack_pop(stack);
    sorted[j] = value;
    j++;
  }
  for (i=0;i<len;i++)
  {
    array[i] = sorted[i];
  }
  Stack_destroy(stack);
}
}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int isStackSortable(int * array, int len)
{
  if (len == 0)
  {
    return FALSE;
  }
  int i;
  int test_left;
  int test_right;
  int max = array[0];
  int index_max = 0;
  for (i=0;i<len;i++)
  {
    if (array[i] > max)
    {
      max = array[i];
      index_max = i;
    }
  }
  if ((index_max != 0) && (index_max != (len - 1)))
  {
    int max_left = array[0];
    for (i=0;i<index_max;i++)
    {
      if (array[i] > max_left)
      {
        max_left = array[i];
      }
    }
    int min_right = array[index_max+1];
    for (i=index_max+1;i<len;i++)
    {
      if (array[i] < min_right)
      {
        min_right = array[i];
      }
    }
    if (max_left > min_right)
    {
      return FALSE;
    }
      test_left = isStackSortable(&array[0],index_max);
      test_right = isStackSortable(&array[index_max+1],len-1-index_max);
      if (!test_left || !test_right)
      {
        return FALSE;
      }
  }
  else if ((index_max == 0) && (len > 2))
  {
    return(isStackSortable(&array[1],len-1));
  }
  else if ((index_max == (len-1)) && (len > 2))
  {
    return(isStackSortable(array,len-1));
  }
  return TRUE;
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [1..k] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */
void genShapes(int k)
{
  int array[k];
  int i;
  void permute(int*,int,int);
  for (i=0;i<k;i++)
  {
    array[i] = i;
  }
  permute(array,k,0);
}

void permute(int * array,int k,int i) 
{ 
  if (k == i)
  {
    if (isStackSortable(array,k))
    {
      TreeNode * root = Tree_build(array,k);
      Tree_printShape(root);
      Tree_destroy(root);
    }
    return;
  }
  int j = i;
  int temp;
  for (j = i; j < k; j++) 
  { 
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    permute(array,k,i+1);
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
  return;
}

