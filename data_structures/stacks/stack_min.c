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
  node *min;
} stack;

void push (stack * s, int data);
int pop (stack * s);
int peek (stack s);
int min (stack s);

void
push (stack * s, int data)
{
  node *new = (node *) malloc (sizeof (node));
  new->data = data;

  new->next = s->top;
  s->top = new;

  if (data < min (*s)) {
    node *new_min = (node *) malloc (sizeof (node));
    new_min->data = data;
    new_min->next = s->min;
    s->min = new_min;
  }
}

int
pop (stack * s)
{
  int value = -1;
  node *tmp = NULL;

  if (s->top) {
    value = s->top->data;
    tmp = s->top;
    s->top = s->top->next;
    free (tmp);
  }

  if (value == min (*s)) {
    tmp = s->min;
    s->min = s->min->next;
    free (tmp);
  }

  return value;
}

int
min (stack s)
{
  if (!s.min) {
    return 10000;
  } else {
    return s.min->data;
  }
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
  printf ("push: %d\n", 2);
  push (&s, 2);
  printf ("push: %d\n", 3);
  push (&s, 3);
  printf ("push: %d\n", 1);
  push (&s, 1);
  printf ("\n");

  printf ("min: %d\n", min (s));
  printf ("pop: %d\n", pop (&s));
  printf ("min: %d\n", min (s));
  printf ("pop: %d\n", pop (&s));
  printf ("min: %d\n", min (s));
  printf ("\n");

  printf ("push: %d\n", 4);
  push (&s, 4);
  printf ("push: %d\n", 5);
  push (&s, 5);
  printf ("\n");

  printf ("pop: %d\n", pop (&s));
  printf ("min: %d\n", min (s));
}
