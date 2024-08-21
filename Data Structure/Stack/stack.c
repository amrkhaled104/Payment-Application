/**
 **********************************************************************************
 * @file           : stack.c >> Linked-Based Implementatio
 * @author         : Amr Khaled
 * @brief          : stack.c that consists of the implementation of the functions 
 * @date           : 22/6/2024
 **********************************************************************************
**/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "stack.h"

// initialize the stack.
void CreateStack(Stack *ps) {
    ps->Top=NULL;
	ps->size=0;
}

// push an element to the stack
void Push(StackEntry e, Stack *ps) {
    StackNode*pn=(StackNode*)malloc(sizeof(StackNode));
	pn->Entry=e;
	pn->Next=ps->Top;
	ps->Top=pn;
	ps->size++;
}

// pop an element from the stack
void Pop(StackEntry *pe, Stack *ps) {
    StackNode*pn;
	*pe=ps->Top->Entry;
	pn=ps->Top;
	ps->Top=ps->Top->Next;
	free(pn);
	ps->size--;
}

// check if the stack is empty or not
int StackEmpty(Stack *ps) {
    return ps->Top==NULL;
}

// check if the stack is full or not
int StackFull(Stack *ps) {
    return 0;
}

// clear stack and destroy all elements in it
void ClearStack(Stack *ps) {
   StackNode*pn;
   while(ps->Top!=NULL)
   {
     pn=ps->Top;
	 ps->Top=ps->Top->Next;
	 free(pn);
	 ps->size--;   
   }
}

/*
pre  conditions: stack is initialized and not empty
post conditions: the last element is returned without change the stack
*/
void StackTop(StackEntry *pe, Stack *ps) {
    *pe = ps->Top->Entry;
}

// calculate the number of elements in the stack
int StackSize(Stack *ps) {
    return ps->size;
}

// traverse stack to do specific job like display all elements in it.
void TraverseStack(Stack *ps, void (*pe)(StackEntry)) {
	 StackNode*pn=ps->Top;
   while(pn)
   {
	   (*pe)(pn->Entry);
	   pn=pn->Next;
   }
}

