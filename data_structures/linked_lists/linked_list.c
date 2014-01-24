/* Implement a single linked list */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  struct node *next;
  int n;
} node;

typedef enum
{
  FALSE, TRUE
} bool;

bool
insert_prepend (node ** l, int n)
{                               /* Insert at beginning of the list */
  printf ("insert prepend %d\n", n);

  node *new_node = (node *) malloc (sizeof (node));
  if (!new_node)
    return FALSE;

  new_node->n = n;
  new_node->next = *l;
  *l = new_node;

  return TRUE;
}

bool
insert_append (node ** l, int n)
{                               /* Insert at end of the list */
  printf ("insert append %d\n", n);

  node *new_node = (node *) malloc (sizeof (node));
  if (!new_node)
    return FALSE;

  new_node->n = n;
  new_node->next = NULL;

  if (*l) {
    node *run = *l;
    while (run->next) {         // go to last node
      run = run->next;
    }
    run->next = new_node;       // append new_node as next of last
  } else {
    *l = new_node;
  }

  return TRUE;
}

bool
dequeue (node ** l, int *value)
{                               /* retrieve and remove the first item */
  if (*l) {
    *value = (*l)->n;

    node *tmp = *l;             // pointer to first node
    *l = tmp->next;
    free (tmp);

    return TRUE;
  } else {
    printf ("list is empty\n");
    return FALSE;
  }
}

bool
pop (node ** l, int *value)
{                               /* retrieve and remove the last item */
  if (!*l) {
    printf ("list is empty\n");
    return FALSE;
  }

  node *run = *l;

  if (!run->next) {             // only one element in the list
    *value = run->n;
    free (run);
    *l = NULL;
  } else {
    while (run->next->next) {   // make runner second to last element
      run = run->next;
    }

    *value = run->next->n;      // get value of last and remove
    free (run->next);
    run->next = NULL;
  }

  return TRUE;
}

bool
travel (node * l)
{
  node *run = l;

  printf ("the list contains: ");
  while (run) {                 // run through all elements
    printf ("%d ", run->n);

    run = run->next;
  }
  printf ("\n\n");

  return TRUE;
}

bool
remove_node (node ** l, int n)
{
  if (*l) {                     // not an empty list
    node *run = *l;

    if (run->n == n) {          // if first node
      *l = run->next;           // list points to the second
      free (run);
    } else {
      while (run->next->n != n) {       // find node
        if (!run->next->next)   // node isn't in the list
          return FALSE;

        run = run->next;
      }

      node *tmp = run->next;
      run->next = run->next->next;      // make previous node point to next
      free (tmp);
    }
  }

  return TRUE;
}

bool
reverse_order (struct node ** head)
{
  struct node *new_head = NULL;

  while (*head) {
    struct node *tmp = *head;
    *head = (*head)->next;
    tmp->next = new_head;
    new_head = tmp;
  }

  *head = new_head;

  return TRUE;
}


int
main ()
{
  // start with an empty list
  node *list = NULL;
  int n;
  travel (list);

  // add a few elements to the list
  insert_append (&list, 2);
  insert_append (&list, 3);
  insert_prepend (&list, 1);
  insert_prepend (&list, 0);
  insert_append (&list, 4);
  insert_append (&list, 5);
  insert_append (&list, 6);

  // travel the list
  travel (list);

  // remove all elements
  dequeue (&list, &n);
  printf ("remove first item: %d\n", n);
  dequeue (&list, &n);
  printf ("remove first item: %d\n", n);
  travel (list);

  // reverse order of list
  printf ("reverse order of list\n");
  reverse_order (&list);
  travel (list);

  printf ("remove item with value 3\n");
  remove_node (&list, 3);
  travel (list);

  printf ("remove item with value 2\n");
  remove_node (&list, 2);
  travel (list);

  printf ("remove item with value 7\n");
  remove_node (&list, 7);
  travel (list);

  pop (&list, &n);
  printf ("remove last item: %d\n", n);
  pop (&list, &n);
  printf ("remove last item: %d\n", n);
  dequeue (&list, &n);
  printf ("remove first item: %d\n", n);

  if (pop (&list, &n))
    printf ("remove last item: %d\n", n);
}
