#include <stdlib.h>
#include <stdio.h>

typedef struct stack
{
  int data[4];
  int used;

  struct stack * next;
} stack;

typedef struct l_stacks
{
  struct stack * stack;
} l_stacks;

void push (l_stacks * ls, int data);
int pop (l_stacks * ls);

void push (l_stacks * ls, int data)
{
  printf("push: %d\n", data);
  stack *head = ls->stack;
  while (head->used == 4 && head->next)
    head = head->next;

  if (head->used != 4) {
    head->data[head->used] = data;
    head->used++;
  } else {
    stack *new = (stack *) malloc (sizeof(stack));
    new->data[0] = data;
    new->used = 1;
    new->next = NULL;
    head->next = new;
  }
}

void travel (l_stacks ls) {
  stack *head = ls.stack;

  printf("t: %d %d %d %d\n", head->data[0], head->data[1], head->data[2],
         head->data[3]);

  while (head->next) {
    head = head->next;
    printf("t: %d %d %d %d\n", head->data[0], head->data[1], head->data[2],
           head->data[3]);
  }
}

int pop (l_stacks * ls) {
  int value;

  stack *head = ls->stack;
  while (head->used == 4 && head->next)
    head = head->next;

  if (head->used == 0)
    return -1;

  if (head->used != 1) {
    value = head->data[head->used-1];
    head->used--;
  } else if (ls->stack->used == 1) {
    value = head->data[0];
    head->used--;
  } else {
    head = ls->stack;

    while (head->next->next) {
      head = head->next;
    }
    value = head->next->data[0];
    stack *tmp = NULL;
    head->next = NULL;
    tmp = head->next;
    free(tmp);
  }

  return value;
}


int main ()
{
  l_stacks ls;
  stack *new = (stack *) malloc (sizeof(stack));
  new->used = 0;
  new->next = NULL;
  ls.stack = new;

  push (&ls, 1);
  push (&ls, 2);
  travel(ls);
  push (&ls, 3);
  push (&ls, 4);
  travel(ls);
  push (&ls, 5);
  push (&ls, 6);
  travel(ls);
  push (&ls, 7);
  push (&ls, 8);
  travel(ls);
  push (&ls, 9);
  push (&ls, 10);
  travel(ls);

  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
  printf("pop: %d\n", pop (&ls));
}
