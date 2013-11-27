/* You have two numbers represented by a linked list, where each node         */
/* contains a single digit. The digits are stored in reverse order, such that */
/* the 1's digit is at the head of the list. Write a function that adds the   */
/* two numbers and returns the sum as a linked list.                          */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int d;
  struct node *next;
} node;

void
travel (node * l)
{
  while (l) {
    printf ("%d ", l->d);
    l = l->next;
  }
  printf ("\n");
}

void
prepend (node ** l, int d)
{
  node *new = (node *) malloc (sizeof (node));
  new->d = d;
  new->next = *l;
  *l = new;
}

void
append (node ** l, int d)
{
  node *new = (node *) malloc (sizeof (node));
  node *head = *l;

  new->d = d;

  if (!head)
    *l = new;
  else {
    while (head->next) {
      head = head->next;
    }
    head->next = new;
  }
}

int
list_to_number (node * l)
{
  int base = 1;
  int sum = 0;
  while (l) {
    sum += l->d * base;
    l = l->next;
    base *= 10;
  }

  return sum;
}

void
number_to_list (node ** l, int n)
{
  while (n != 0) {
    append (l, n % 10);
    n = n / 10;
  }
}

void
add (node * a, node * b, node ** sum)
{
  int sum_a = list_to_number (a);
  int sum_b = list_to_number (b);

  printf ("sum is %d\n", sum_a + sum_b);
  number_to_list (sum, sum_a + sum_b);
}

int
main ()
{
  node *a = NULL;
  node *b = NULL;
  node *sum = NULL;

  prepend (&a, 6);
  prepend (&a, 1);
  prepend (&a, 7);

  prepend (&b, 2);
  prepend (&b, 9);
  prepend (&b, 5);

  travel (a);
  travel (b);

  add (a, b, &sum);
  travel (sum);
}
