#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;


Stack * stack_pop(Stack*);
Stack * stack_push(Stack*,HuffNode*);
HuffNode * create(int);
HuffNode * build(HuffNode *,char * data);
#endif

