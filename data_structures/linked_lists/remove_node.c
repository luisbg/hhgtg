/* Algorithm to delete a node in the middle of a single-linked list,          */
/* Given access to only that node.                                            */
/* Input: the node C from the linked list a->b->c->d->e                       */
/* Result: nothing is returned, but the new linked list looks like a->b->d->e */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int n;
  struct node *next;
} node;

void
insert (node ** l, int n)
{
  node *new = (node *) malloc (sizeof (node));
  new->n = n;
  new->next = *l;
  *l = new;
}

void
travel (node * l)
{
  node *tmp = l;

  printf ("the list contains: ");
  while (tmp != NULL) {
    printf ("%d ", tmp->n);

    tmp = tmp->next;
  }
  printf ("\n\n");
}

void
remove_node (node * n)
{
  if (n == NULL || n->next == NULL)
    return;                     // Error

  node *next;
  next = n->next;
  n->n = next->n;
  n->next = next->next;
  free (next);
}

int
main ()
{
  // start with an empty list
  node *list = NULL;

  // add a few elements to the list
  insert (&list, 5);
  insert (&list, 4);
  insert (&list, 3);
  insert (&list, 2);
  insert (&list, 1);

  // travel the list
  travel (list);

  // remove item
  printf ("remove item %d\n", 3);
  node *head = (node *) malloc (sizeof (node));
  head = list;
  while (head != NULL && head->n != 3) {
    head = head->next;
  }
  remove_node (head);

  // travel the new list
  travel (list);
}
