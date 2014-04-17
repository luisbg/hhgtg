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


/* Travel through the list printing the elements */
static void
travel (node * l)
{
  while (l) {
    printf ("%d ", l->d);
    l = l->next;
  }
  printf ("\n");
}

/* Insert value at the head of the list */
static void
prepend (node ** l, int d)
{
  node *new = (node *) malloc (sizeof (node));
  new->d = d;
  new->next = *l;
  *l = new;
}

/* Insert value at the tail of the list */
static void
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

/* Convert a list of digits to an integer */
static int
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

/* Convert an integer into a list of digits */
static void
number_to_list (node ** l, int n)
{
  while (n != 0) {
    append (l, n % 10);
    n = n / 10;
  }
}

/* Add the two lists converting them to numbers and back */
void
add (node * a, node * b, node ** sum)
{
  int sum_a = list_to_number (a);
  int sum_b = list_to_number (b);

  printf ("sum is %d\n", sum_a + sum_b);
  number_to_list (sum, sum_a + sum_b);
}

/* Sum two linked lists into one */
void
add_with_lists (node * a, node * b, node ** sum)
{
  node *runa, *runb;
  int lena = 0,
    lenb = 0,
    carry_over = 0,
    tmp, i;

  runa = a;
  runb = b;
  while (runa->next) {    // get number of digits in a
    runa = runa->next;
    lena++;
  }

  while (runb->next) {    // get number of digits in b
    runb = runb->next;
    lenb++;
  }

  while (lena >= 0 && lenb >= 0) {
    tmp = runa->d + runb->d;    // add elements from the tail back from both lists
    if (tmp < 10) {                         // if sum above 10, carry over
      prepend (sum, tmp + carry_over);
      carry_over = 0;
    } else {
      prepend (sum, (tmp - 10) + carry_over);
      carry_over = 1;
    }

    i = --lena;
    runa = a;
    while (i > 0) {           // decrement len to go to cycle to previous node
      runa = runa->next;
      i--;
    }

    i = --lenb;
    runb = b;
    while (i > 0) {
      runb = runb->next;
      i--;
    }
  }

  runa = a;                   // one of the lists might still have more digits
  while (lena >= 0) {         // prepend them along
    i = --lena;
    runa = a;
    while (i > 0) {
      runa = runa->next;
      i--;
    }
    prepend (sum, runa->d + carry_over);
    carry_over = 0;
  }

  runb = b;
  while (lenb >= 0) {
    i = --lenb;
    runb = b;
    while (i > 0) {
      runb = runb->next;
      i--;
    }
    prepend (sum, runb->d + carry_over);
    carry_over = 0;
  }

  if (carry_over)           // we might still have a carry over if the two
    prepend (sum, 1);       // lists have same amount of digits in MSB add > 10
}


int
main ()
{
  node *a = NULL;
  node *b = NULL;
  node *c = NULL;
  node *sum = NULL;
  node *second_sum = NULL;

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

  printf ("\n");

  prepend (&c, 3);
  prepend (&c, 5);
  prepend (&c, 8);

  travel (b);
  travel (c);

  // todo: add function to free memory to reuse first sum list
  add_with_lists (b, c, &second_sum);
  travel (second_sum);

  return 0;
}
