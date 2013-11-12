#include "pa09.h"
#include <stdio.h>
#include <stdlib.h>

Stack * stack_pop(Stack * st)
{
  if (st == NULL)
  {
    return NULL;
  }
  Stack * b = st -> next;
  free(st);
  return(b);
}

Stack * stack_push(Stack * st,HuffNode * t)
{
  Stack * topnode = malloc(sizeof(Stack));
  topnode -> node= t;
  topnode -> next = st;
  return topnode;
}

HuffNode * insert(HuffNode * array,int value)
{
  if (array == NULL)
  {
    return create(value);
  }
  if (array -> value > value)
  {
    array -> left = insert(array -> left,value);
    return array;
  }
  array -> right = insert(array -> right,value);
  return array;
}

HuffNode * create(int value)
{
  HuffNode * hn = malloc(sizeof(HuffNode));
  hn -> value = value;
  hn -> left = NULL;
  hn -> right = NULL;
  return hn;
}

HuffNode * build(HuffNode * root,char * data)
{
  char command;
  char data_point;
  int done = 0;
  int i = 0;
  Stack * stack = NULL;
  while (done != 1)
  {
    command = data[i];
    i++;
    if (command == 1)
    {
      data_point = data[i];
      root = create(data_point);
      Stack * stack_head = NULL;
      stack_head = stack_push(stack_head,root);
      i++;
    }
    if (command == 0)
    {
      HuffNode * a = stack -> node;
      stack = stack_pop(stack);
printf("TEST1\n");
      if (stack == NULL)
      {
printf("TEST2\n");
        done = 1;
        root = a;
      }
      else
      {
        HuffNode * b = stack -> node;
        HuffNode * parent = malloc(sizeof(HuffNode));
        parent -> left = b;
        parent -> right = a;
        stack = stack_push(stack,parent);
      }
    }
  }
  return root;
}
