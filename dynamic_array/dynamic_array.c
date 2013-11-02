#include <stdlib.h>
#include <stdio.h>

typedef enum
{ FALSE, TRUE } bool;

typedef struct
{
  int *array;
  int size;
  int len;
} dyn_arr;


void
push (dyn_arr * da, int i)
{
  printf ("push: %d\n", i);

  if (da->len < da->size) {
    da->array[da->len] = i;
    da->len++;
  } else {
    int new_size = da->size * 2;
    int *new_s = (int *) malloc (new_size * sizeof (int));
    int c;
    for (c = 0; c < new_size; c++) {
      if (c < da->len)
        new_s[c] = da->array[c];
      else
        new_s[c] = 0;
    }

    da->array = new_s;
    da->size = new_size;

    push (da, i);
  }

/*    printf("current state ");
    int a;
    for (a = 0; a < da->size; a++) {
        printf("%d ", da->array[a]);
    }
    printf("\n"); */
}

bool
stack_pop (dyn_arr * da, int *ret)
{
  if (da->len == 0)
    return FALSE;

  *ret = da->array[da->len - 1];
  da->array[da->len - 1] = 0;
  da->len = da->len - 1;

  if (da->size >= (da->len * 2)) {
    int new_size = da->size / 2;
    int *new_s = (int *) malloc (new_size * sizeof (int));
    int c;
    for (c = 0; c < new_size; c++) {
      new_s[c] = da->array[c];
    }

    da->array = new_s;
    da->size = new_size;
  }

  return TRUE;
}

void
init_dyn_arr (dyn_arr * new, int i)
{
  new->array = (int *) malloc (sizeof (int));
  new->array[0] = i;
  new->size = 1;
  new->len = 1;
}


int
main ()
{
  dyn_arr a;
  printf ("initialize with 1\n");
  init_dyn_arr (&a, 1);

  int c;
  for (c = 2; c <= 37; c++) {
    push (&a, c);
  }

  int t;
  for (c = 0; c <= 40; c++) {
    if (stack_pop (&a, &t))
      printf ("pop: %d\n", t);
    else
      printf ("stack empty\n");
  }
}
