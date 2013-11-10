/* Find the kth to last element of a singly linked list */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int n;
  struct node *next;
} node;


void
prepend (node ** l, int n)
{
  node *new = (node *) malloc (sizeof (node));
  new->n = n;
  new->next = *l;
  *l = new;
}


int
find_kth_element_brute (node ** l, int pos)
{
  node *head = (node *) malloc (sizeof (node));
  int c = 0;
  head = *l;
  while (head != NULL) {
    c++;
    head = head->next;
  }

  head = *l;
  for (c -= pos; c > 0; c--) {
    head = head->next;
  }

  return head->n;
}

int
find_kth_element_iteratively (node ** l, int pos)
{
  node *p1 = (node *) malloc (sizeof (node));
  node *p2 = (node *) malloc (sizeof (node));

  // move p2 forward pos times
  p2 = *l;
  int c;
  for (c = 0; c < pos; c++) {
    if (p2 == NULL)
      return 0;                 // error check
    p2 = p2->next;
  }

  // now have p1 moving behind
  p1 = *l;
  while (p2 != NULL) {
    p1 = p1->next;
    p2 = p2->next;
  }

  return p1->n;
}

int
main ()
{
  node *l = (node *) malloc (sizeof (node));
  l = NULL;

  prepend (&l, 10);
  prepend (&l, 9);
  prepend (&l, 8);
  prepend (&l, 7);
  prepend (&l, 6);
  prepend (&l, 5);
  prepend (&l, 4);
  prepend (&l, 3);
  prepend (&l, 2);
  prepend (&l, 1);

  // brute force
  printf ("%d th last element: %d\n", 1, find_kth_element_brute (&l, 1));
  printf ("%d th last element: %d\n", 2, find_kth_element_brute (&l, 2));
  printf ("%d th last element: %d\n", 3, find_kth_element_brute (&l, 3));

  // iteratively
  printf ("%d th last element: %d\n", 4, find_kth_element_iteratively (&l, 4));
  printf ("%d th last element: %d\n", 5, find_kth_element_iteratively (&l, 5));
  printf ("%d th last element: %d\n", 6, find_kth_element_iteratively (&l, 6));
}
