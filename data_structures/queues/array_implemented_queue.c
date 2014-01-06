/* FIFO Queue implemented with an array */

#include <stdlib.h>
#include <stdio.h>

#define maxN 12

typedef struct queue
{
  int N;
  int head;
  int tail;
  int *arr;
} queue_t;


queue_t *
queue_init (int max_num)
{
  queue_t *q = malloc (sizeof (queue_t));
  q->N = max_num + 1;
  q->head = q->N;
  q->tail = 0;
  q->arr = malloc ((max_num + 1) * sizeof (int));
}

int
queue_is_empty (queue_t *q)
{
  if (q->head == q->tail)
    return 1;
  else
    return 0;
}

void
queue_put (queue_t *q, int num)
{
  q->arr[q->tail++] = num;
  q->tail = q->tail % q->N;
}

int
queue_get (queue_t *q)
{
  int num;

  q->head = q->head % q->N;

  if (!queue_is_empty (q))
    num = q->arr[q->head++];
  else
    num = -1;

  return num;
}

void
queue_destroy (queue_t *q)
{
  free(q->arr);
}

int
main ()
{
  queue_t *q = queue_init (maxN);

  printf ("enqueue: %d\n", 0);
  queue_put (q, 0);
  printf ("enqueue: %d\n", 1);
  queue_put (q, 1);
  printf ("enqueue: %d\n", 2);
  queue_put (q, 2);
  printf ("enqueue: %d\n", 3);
  queue_put (q, 3);

  printf ("\n");

  printf ("dequeue: %d\n", queue_get (q));
  printf ("dequeue: %d\n", queue_get (q));
  printf ("dequeue: %d\n", queue_get (q));
  printf ("dequeue: %d\n", queue_get (q));
  printf ("dequeue: %d\n", queue_get (q));

  printf ("\n");

  printf ("enqueue: %d\n", 4);
  queue_put (q, 4);
  printf ("enqueue: %d\n", 5);
  queue_put (q, 5);

  printf ("\n");

  printf ("dequeue: %d\n", queue_get (q));
  printf ("dequeue: %d\n", queue_get (q));

  queue_destroy (q);

  return 0;
}
