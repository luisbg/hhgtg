/* Determine wether a given list is circular or if the list has an ending    */
/* node. Without modifying the list.                                         */

#include <stdlib.h>
#include <stdio.h>

typedef enum
{ FALSE, TRUE } bool;

typedef struct node
{
  int d;
  struct node *next;
} node;


/* Insert value at the head of the list */
static void
prepend (node ** l, int d)
{
  node *new = (node *) malloc (sizeof (node));
  new->d = d;
  new->next = *l;
  *l = new;
}

/* Turn the list circular by having tail element point to the head */
static void
make_circular (node ** l)
{
  node *first = *l;
  node *head = *l;

  while (head->next) {
    head = head->next;
  }

  head->next = first;
}

/* Check if a list is circular */
bool
find_cyclical (node * head)
{
  node *slower, *faster;
  slower = head;
  faster = head->next;          // start faster one node ahead

  while (TRUE) {
    // if the faster pointer encounters a NULL element
    if (!faster || !faster->next)
      return FALSE;

    // if faster pointer ever equals slower or faster's next
    // pointer is ever equal to slow then it's a circular list
    else if (faster == slower || faster->next == slower)
      return TRUE;

    else {
      // advance the pointers
      slower = slower->next;
      faster = faster->next->next;
    }
  }
}


int
main ()
{
  node *l = NULL;
  prepend (&l, 9);
  prepend (&l, 8);
  prepend (&l, 7);
  prepend (&l, 6);
  prepend (&l, 5);
  prepend (&l, 4);
  prepend (&l, 3);
  prepend (&l, 2);
  prepend (&l, 1);
  prepend (&l, 0);

  printf ("is it circular? %s\n", find_cyclical (l) ? "yes" : "no");

  make_circular (&l);
  printf ("is it circular? %s\n", find_cyclical (l) ? "yes" : "no");

  return 0;
}
