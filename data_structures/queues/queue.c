#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int data;
  struct node *next;
} node;

typedef struct queue
{
  node *head;
  node *last;
} queue;

void enqueue (queue * q, int data);
int dequeue (queue * q);

void
enqueue (queue * q, int data)
{
  node *new = (node *) malloc (sizeof (node));
  new->data = data;
  new->next = NULL;

  if (q->head) {
    q->last->next = new;
    q->last = new;
  } else {
    q->head = new;
    q->last = new;
  }
}

int
dequeue (queue * q)
{
  int d = -1;
  node *tmp = NULL;

  if (q->head) {
    d = q->head->data;
    tmp = q->head;
    q->head = q->head->next;
    free (tmp);
  }

  return d;
}


int
main ()
{
  queue q;
  q.head = NULL;
  q.last = NULL;

  printf ("enqueue: %d\n", 0);
  enqueue (&q, 0);
  printf ("enqueue: %d\n", 1);
  enqueue (&q, 1);
  printf ("enqueue: %d\n", 2);
  enqueue (&q, 2);
  printf ("enqueue: %d\n", 3);
  enqueue (&q, 3);

  printf ("\n");

  printf ("dequeue: %d\n", dequeue (&q));
  printf ("dequeue: %d\n", dequeue (&q));
  printf ("dequeue: %d\n", dequeue (&q));
  printf ("dequeue: %d\n", dequeue (&q));
  printf ("dequeue: %d\n", dequeue (&q));

  printf ("\n");

  printf ("enqueue: %d\n", 4);
  enqueue (&q, 4);
  printf ("enqueue: %d\n", 5);
  enqueue (&q, 5);

  printf ("\n");

  printf ("dequeue: %d\n", dequeue (&q));
  printf ("dequeue: %d\n", dequeue (&q));
}
