/* Implement a single linked list */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int n;
  struct node *next;
} node;

void
insert_prepend (node ** l, int n)
{
  printf ("insert prepend %d\n", n);

  node *new_node = (node *) malloc (sizeof (node));
  new_node->n = n;
  new_node->next = *l;
  *l = new_node;
}

void
insert_append (node ** l, int n)
{
  printf ("insert append %d\n", n);

  node *new_node = (node *) malloc (sizeof (node));
  new_node->n = n;
  new_node->next = NULL;

  if (*l != NULL) {
    node *current = *l;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  } else {
    *l = new_node;
  }
}

int
dequeue (node ** l)
{                               /* retrieve and remove the first item */
  if (*l != NULL) {
    int value = (*l)->n;
    node *tmp = (node *) malloc (sizeof (node));        // pointer to first node

    tmp = *l;
    *l = tmp->next;
    free (tmp);

    return value;
  } else {
    printf ("list is empty\n");
    return 0;
  }
}

int
pop (node ** l)
{                               /* retrieve and remove the last item */
  if (*l != NULL) {
    int value;
    node *current = (node *) malloc (sizeof (node));
    node *prev = (node *) malloc (sizeof (node));
    current = *l;
    prev = *l;

    while (current->next != NULL) {
      current = current->next;
    }

    value = current->n;

    if (current != *l) {        // more than one element in the list
      while (prev->next != current) {
        prev = prev->next;
      }

      prev->next = NULL;
    } else {
      *l = NULL;
    }
    free (current);
    return value;
  } else {
    printf ("list is empty\n");
    return 0;
  }
}

void
travel (node * l)
{
  node *tmp = l;

  printf ("the list contains: ", tmp->n);
  while (tmp != NULL) {
    printf ("%d ", tmp->n);

    tmp = tmp->next;
  }
  printf ("\n");
}

int
main ()
{
  // start with an empty list
  node *list = NULL;

  // add a few elements to the list
  insert_append (&list, 2);
  insert_append (&list, 3);
  insert_prepend (&list, 1);
  insert_prepend (&list, 0);
  insert_append (&list, 4);
  insert_append (&list, 5);

  // travel the list
  travel (list);

  // remove all elements
  printf ("remove first item: %d\n", dequeue (&list));
  printf ("remove first item: %d\n", dequeue (&list));
  printf ("remove last item: %d\n", pop (&list));
  printf ("remove last item: %d\n", pop (&list));
  printf ("remove last item: %d\n", pop (&list));
  printf ("remove first item: %d\n", dequeue (&list));
  printf ("remove last item: %d\n", pop (&list));
}
