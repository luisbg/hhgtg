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

typedef enum
{ FALSE, TRUE } bool;


int pop (stack * s);
void push (stack * s, int data);
int peek (stack s);
bool empty (stack s);
stack init ();


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

bool
empty (stack s)
{
  if (s.top)
    return FALSE;
  else
    return TRUE;
}

stack
init ()
{
  stack * s = (stack *) malloc (sizeof (stack));
  s->top = NULL;

  return *s;
}


int
main ()
{
  stack s = init();
  s.top = NULL;

  printf ("push: %d\n", 1);
  push (&s, 1);
  printf ("push: %d\n", 2);
  push (&s, 2);
  printf ("push: %d\n\n", 3);
  push (&s, 3);

  printf ("empty stack? %s\n\n", empty (s)? "yes": "no");

  printf ("pop: %d\n", pop (&s));

  printf ("push: %d\n", 4);
  push (&s, 4);
  printf ("push: %d\n\n", 5);
  push (&s, 5);

  printf ("peek: %d\n\n", peek (s));
  printf ("pop: %d\n", pop (&s));
  printf ("pop: %d\n", pop (&s));
  printf ("pop: %d\n", pop (&s));
  printf ("pop: %d\n\n", pop (&s));

  printf ("empty stack? %s\n", empty (s)? "yes": "no");
}
