/* A stack where the smallest element can be peeked */

#include <stdlib.h>
#include <stdio.h>

#define MAX (sizeof(int) << 25)

typedef struct node
{
  int data;
  struct node *next;
} node;

typedef struct stack
{
  node *top;    // stack linked list
  node *min;    // minimum element linked list
} stack;

void push (stack * s, int data);
int pop (stack * s);
int peek (stack s);
int min (stack s);


/* push data to the top of the stack */
void
push (stack * s, int data)
{
  node *new = (node *) malloc (sizeof (node));
  new->data = data;

  new->next = s->top;
  s->top = new;

  // Only need to store if new minimum, the rest will never be minimum later on
  if (data < min (*s)) {
    node *new_min = (node *) malloc (sizeof (node));
    new_min->data = data;
    new_min->next = s->min;
    s->min = new_min;
  }
}

/* get element from top of the stack */
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

  // if value is the minimum, next minimum in queue is minimum now
  if (value == min (*s)) {
    tmp = s->min;
    s->min = s->min->next;
    free (tmp);
  }

  return value;
}

/* peek at the smallest element contained in the stack */
int
min (stack s)
{
  if (!s.min) {
    return MAX;
  } else {
    return s.min->data;
  }
}

/* peek at top of the stack */
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

  return 0;
}
