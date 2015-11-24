
/* Remove duplicates from an unsorted linked list */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int n;
  struct node *next;
  struct node *prev;
} node;

typedef enum
{ FALSE, TRUE } bool;


/* Sort the linked list */
void
sort_list (node ** l)
{
  node *curr = *l;
  node *move = NULL;
  int tmp;

  while (curr->next) {
    if (curr->n > curr->next->n) {
      move = curr->next;
      while ((curr->prev) && curr->prev->n > move->n) {
        curr = curr->prev;
      }
      tmp = curr->n;
      curr->n = move->n;
      move->n = tmp;
    }

    curr = curr->next;
  }
}

/* Insert value at the head of the list */
void
prepend (node ** l, int n)
{
  node *new = (node *) malloc (sizeof (node));

  new->n = n;
  new->next = *l;
  if (*l)
    (*l)->prev = new;
  new->prev = NULL;
  *l = new;
}

/* Travel through the list and print values */
void
travel (node * l)
{
  printf ("\n");
  while (l) {
    printf ("%d ", l->n);
    l = l->next;
  }
  printf ("\n");
}

/* remove duplicate values */
void
remove_duplicates (node ** l)
{
  node *curr = *l;
  node *tmp = NULL;

  if (!curr) {
    printf ("list empty\n");
    return;
  }

  while (curr->next) {   // loop through the list
    if (curr->n == curr->next->n) {
      // if curr and next are the same, remove next
      tmp = curr->next;
      if (curr->next->next)
        curr->next->next->prev = curr;
      curr->next = curr->next->next;
      free (tmp);
    } else {
      curr = curr->next;
    }
  }
}

/* check if the value is already contained in the list */
/* stores a singled linked list of unique values */
bool
have_we_seen_it_before (node ** l, int n)
{
  node *curr = *l;
  node *new = NULL;

  while (curr) {    // check if we have seen it
    if (curr->n == n)
      return TRUE;

    curr = curr->next;
  }

  new = (node *) malloc (sizeof (node));  // if we haven't seen it, add
  new->n = n;                             // it to the buffer
  new->next = NULL;                       // appending requires more work
  if (*l) {                               // but keeps the original order
    curr = *l;
    while (curr->next)
      curr = curr->next;
    curr->next = new;
  } else {
    *l = new;
  }

  return FALSE;
}

/* remove the duplicates by saving a buffer with seen values */
void
remove_duplicates_with_buffer (node ** l)
{
  node *curr = *l;
  node *buffer = NULL;       // preferably a hash table
  node *tmp = NULL;

  while (curr) {  // loop through the list
    if (have_we_seen_it_before (&buffer, curr->n)) {
      // if duplicate, remove current element
      tmp = curr;
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      free (tmp);
    }

    curr = curr->next;
  }
}

node *
remove_duplicates_single_linked (node * head)
{
  node *curr = head;
  node *buffer = NULL;

  // run through the list creating a unique values new one
  while (curr) {
    have_we_seen_it_before (&buffer, curr->n);
    curr = curr->next;
  }

  return buffer;
}

int
main ()
{
  node *l = NULL;
  node *m = NULL;
  node *o = NULL;

  prepend (&l, 0);
  prepend (&l, 3);
  prepend (&l, 4);
  prepend (&l, 7);
  prepend (&l, 4);
  prepend (&l, 7);
  prepend (&l, 3);
  prepend (&l, 2);
  prepend (&l, 5);
  prepend (&l, 9);
  prepend (&l, 7);
  prepend (&l, 8);
  prepend (&l, 7);
  prepend (&l, 6);
  prepend (&l, 1);
  prepend (&l, 1);
  prepend (&l, 4);
  prepend (&l, 1);
  prepend (&l, 9);

  printf ("original linked list: ");
  travel (l);

  printf ("sorted list: ");
  sort_list (&l);
  travel (l);

  printf ("remove duplicates: ");
  remove_duplicates (&l);
  travel (l);
  printf ("\n");

  prepend (&m, 1);
  prepend (&m, 4);
  prepend (&m, 5);
  prepend (&m, 8);
  prepend (&m, 5);
  prepend (&m, 8);
  prepend (&m, 4);
  prepend (&m, 3);
  prepend (&m, 6);
  prepend (&m, 10);
  prepend (&m, 8);
  prepend (&m, 9);
  prepend (&m, 8);
  prepend (&m, 7);
  prepend (&m, 2);
  prepend (&m, 2);
  prepend (&m, 5);
  prepend (&m, 2);
  prepend (&m, 10);

  printf ("new original linked list: ");
  travel (m);

  printf ("removed duplicates: ");
  remove_duplicates_with_buffer (&m);
  travel (m);
  printf ("\n");

  prepend (&o, 1);
  prepend (&o, 2);
  prepend (&o, 3);
  prepend (&o, 3);
  prepend (&o, 1);
  prepend (&o, 2);
  prepend (&o, 3);

  printf ("new original single linked list: ");
  travel (o);

  printf ("removed duplicates: ");
  o = remove_duplicates_single_linked (o);
  travel (o);

  return 0;
}
