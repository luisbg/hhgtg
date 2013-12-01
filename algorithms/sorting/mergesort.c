#include <stdlib.h>
#include <stdio.h>

typedef enum
{
  FALSE, TRUE
} bool;

typedef struct queue
{
  int value;
  struct queue *next;
} queue;


void
enqueue (queue ** q, int value)
{
  queue *node = (queue *) malloc (sizeof (queue));
  node->value = value;
  node->next = NULL;

  if (!*q) {
    *q = node;

  } else {
    queue *curr = *q;
    while (curr->next != NULL) {
      curr = curr->next;
    }

    curr->next = node;
  }
}

int
dequeue (queue ** q)
{
  if (*q) {
    queue *node = *q;
    int value = node->value;
    *q = node->next;
    free (node);

    return value;
  } else {
    return -1;
  }
}

int
headq (queue * q)
{
  return q->value;
}

bool
empty_queue (queue * q)
{
  if (!q)
    return TRUE;
  else
    return FALSE;
}

void
merge (int *l, int low, int middle, int high)
{
  int i;                        // counter
  queue *buffer1 = NULL;
  queue *buffer2 = NULL;        // buffers to hold elements for merging

  for (i = low; i <= middle; i++)       // queue first half in buffer 1
    enqueue (&buffer1, l[i]);
  for (i = middle + 1; i <= high; i++)  // queue second half in buffer 2
    enqueue (&buffer2, l[i]);

  i = low;                      // run through the buffers getting the lowest number in either head
  while (!empty_queue (buffer1) && !empty_queue (buffer2)) {
    if (headq (buffer1) <= headq (buffer2))
      l[i++] = dequeue (&buffer1);
    else
      l[i++] = dequeue (&buffer2);
  }

  while (!empty_queue (buffer1))        // one of the buffers still has elements
    l[i++] = dequeue (&buffer1);
  while (!empty_queue (buffer2))
    l[i++] = dequeue (&buffer2);
}

void
mergesort (int *l, int low, int high)
{
  int middle;

  if (low < high) {             // divide the list recursively in halves, merge the halves
    middle = (low + high) / 2;
    mergesort (l, low, middle);
    mergesort (l, middle + 1, high);
    merge (l, low, middle, high);
  }
}

void
print_list (int *l, int len)
{
  int c;
  for (c = 0; c < len; c++) {
    printf ("%d ", l[c]);
  }
  printf ("\n");
}

int
main ()
{
  int l[50];
  int size = 50;
  int c;
  for (c = 0; c < size; c++)
    l[c] = rand () % 100;

  printf ("out of order: ");
  print_list (l, size);

  mergesort (l, 0, size - 1);
  printf ("in order:     ");
  print_list (l, size);
}
