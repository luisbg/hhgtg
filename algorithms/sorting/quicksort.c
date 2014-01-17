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


static void swap (int *a, int *b);
static int get_pivot (int low, int high);
static int partition (int *l, int low, int high);
void quicksort (int *l, int low, int high);


void
print_list (int *l, int len)
{
  int c;
  for (c = 0; c < len; c++) {
    printf ("%d ", l[c]);
  }
  printf ("\n");
}

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
stackempty (stack * s)
{
  if (s->top)
    return 0;
  else
    return 1;
}

static void
swap (int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static int
get_pivot (int low, int high)
{
  return (low + high) / 2;
}

static int
partition (int *l, int low, int high)
{
  int c;
  int middle;

  int k = get_pivot (low, high);
  int pivot = l[k];
  swap (&l[low], &l[k]);        // move pivot out of array to order

  c = low + 1;
  middle = high;
  while (c <= middle)           // run the array
  {
    while ((c <= high) && (l[c] <= pivot))      // before pivot
      c++;
    while ((middle >= low) && (l[middle] > pivot))      // after pivot
      middle--;
    if (c < middle)
      swap (&l[c], &l[middle]);
  }

  swap (&l[low], &l[middle]);   // bring the pivot to its place

  return middle;
}

void
quicksort (int *l, int low, int high)
{
  if (low >= high)
    return;

  int middle;

  middle = partition (l, low, high);
  quicksort (l, low, middle - 1);
  quicksort (l, middle + 1, high);
}

void
quicksort_non_recursive (int *l, int low, int high)
{
  int middle;

  stack s;
  push (&s, high);
  push (&s, low);

  while (!stackempty (&s)) {
    low = pop(&s);
    high = pop(&s);

    if (low >= high)
      continue;

    middle = partition (l, low, high);
    if (middle - 1 > high - middle) {
      push (&s, middle - 1);
      push (&s, low);
      push (&s, high);
      push (&s, middle + 1);
    } else {
      push (&s, high);
      push (&s, middle + 1);
      push (&s, middle - 1);
      push (&s, low);
    }
  }
}


int
main ()
{
  int l[50];
  int size = 50;
  int c;
  for (c = 0; c < size; c++)
    l[c] = rand () % 100;

  printf ("out of order:\n");
  print_list (l, size - 1);

  printf ("in order (recursive quicksort):\n");
  quicksort (l, 0, size - 1);
  print_list (l, size - 1);

  printf ("\n\n");
  for (c = 0; c < size; c++)
    l[c] = rand () % 100;

  printf ("new out of order:\n");
  print_list (l, size - 1);

  printf ("in order (non-recursive quicksort):\n");
  quicksort_non_recursive (l, 0, size - 1);
  print_list (l, size - 1);
}
