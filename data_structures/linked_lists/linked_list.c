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


/* Insert at the head of the list */
bool
insert_prepend (node ** l, int n)
{
  printf ("insert prepend %d\n", n);

  node *new_node = (node *) malloc (sizeof (node));
  if (!new_node)
    return FALSE;

  new_node->n = n;
  new_node->next = *l;
  *l = new_node;

  return TRUE;
}

/* Insert at the tail of the list */
bool
insert_append (node ** l, int n)
{
  printf ("insert append %d\n", n);

  node *run;
  node *new_node = (node *) malloc (sizeof (node));
  if (!new_node)
    return FALSE;

  new_node->n = n;
  new_node->next = NULL;

  if (*l) {
    run = *l;
    while (run->next) {         // go to last node
      run = run->next;
    }
    run->next = new_node;       // append new_node as next of last
  } else {
    *l = new_node;
  }

  return TRUE;
}

/* Retrieve and remove the first item */
bool
dequeue (node ** l, int *value)
{
  node *tmp;

  if (*l) {
    *value = (*l)->n;

    tmp = *l;             // pointer to first node
    *l = tmp->next;
    free (tmp);

    return TRUE;
  } else {
    printf ("list is empty\n");
    return FALSE;
  }
}

/* Retrieve and remove the last item */
bool
pop (node ** l, int *value)
{
  node *run;

  if (!*l) {
    printf ("list is empty\n");
    return FALSE;
  }

  run = *l;

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

/* Travel through list printing the elements */
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

/* Remove the node with the value n */
bool
remove_node (node ** l, int n)
{
  node *run, *tmp;

  if (*l) {                     // not an empty list
    run = *l;

    if (run->n == n) {          // if first node
      *l = run->next;           // list points to the second
      free (run);
    } else {
      while (run->next->n != n) {       // find node
        if (!run->next->next)   // node isn't in the list
          return FALSE;

        run = run->next;
      }

      tmp = run->next;
      run->next = run->next->next;      // make previous node point to next
      free (tmp);
    }
  }

  return TRUE;
}

/* Reverse the order of the list */
bool
reverse_order (node ** l)
{
  node *tmp,
    *new_head = NULL;

  while (*l) {
    tmp = *l;
    *l = (*l)->next;
    tmp->next = new_head;
    new_head = tmp;
  }

  *l = new_head;

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

  return 0;
}
