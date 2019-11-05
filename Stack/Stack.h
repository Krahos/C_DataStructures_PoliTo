#ifndef STACK_H
#define STACK_H

typedef struct stack *Stack;

Stack newStack(
		void(*itemDelete)(void*));
int   stackPush(Stack, void* item);
void* stackPop(Stack);
void* stackTopView(Stack);
int   stackCount(Stack);
int   stackEmpty(Stack);
void  stackDestructor(Stack);
#endif