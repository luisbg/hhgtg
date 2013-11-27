#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int data;
  struct node *next;
} node;

typedef struct stack
{
  node *top;
} stack;

int pop (stack * s);
void push (stack * s, int data);
int peek (stack s);

void
push (stack * s, int data)
{
  node *new = (node *) malloc (sizeof (node));
  new->data = data;

  new->next = s->top;
  s->top = new;
}

int
pop (stack * s)
{
  int ret = -1;
  node *tmp = NULL;

  if (s->top) {
    ret = s->top->data;
    tmp = s->top;
    s->top = s->top->next;
    free (tmp);
  }

  return ret;
}

int
peek (stack s)
{
  if (s.top)
    return s.top->data;
  else
    return -1;
}

int
main ()
{
  stack s;
  printf ("push: %d\n", 1);
  push (&s, 1);
  printf ("push: %d\n", 2);
  push (&s, 2);
  printf ("push: %d\n", 3);
  push (&s, 3);

  printf ("pop: %d\n", pop (&s));

  printf ("push: %d\n", 4);
  push (&s, 4);
  printf ("push: %d\n", 5);
  push (&s, 5);

  printf ("peek: %d\n", peek (s));
  printf ("pop: %d\n", pop (&s));
}
