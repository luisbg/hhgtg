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


void
sort_list (node ** l)
{
  node *head = (node *) malloc (sizeof (node));
  node *move = (node *) malloc (sizeof (node));
  int tmp;
  head = *l;

  while (head->next != NULL) {
    if (head->n > head->next->n) {
      move = head->next;
      while ((head->prev != NULL) && head->prev->n > move->n) {
        head = head->prev;
      }
      tmp = head->n;
      head->n = move->n;
      move->n = tmp;
    }

    head = head->next;
  }
}

void
prepend (node ** l, int n)
{
  node *new = (node *) malloc (sizeof (node));

  new->n = n;
  new->next = *l;
  if (*l != NULL)
    (*l)->prev = new;
  new->prev = NULL;
  *l = new;
}

void
travel (node * l)
{
  printf ("\n");
  while (l != NULL) {
    printf ("%d ", l->n);
    l = l->next;
  }
  printf ("\n");
}

void
remove_duplicates (node ** l)
{
  node *head = (node *) malloc (sizeof (node));
  node *tmp = (node *) malloc (sizeof (node));
  head = *l;

  if (head == NULL) {
    printf ("list empty\n");
    return;
  }

  while (head->next != NULL) {
    if (head->next != NULL) {
      if (head->n == head->next->n) {
        tmp = head->next;
        if (head->next->next != NULL)
          head->next->next->prev = head;
        head->next = head->next->next;
        free (tmp);
      } else {
        head = head->next;
      }
    }
  }
}

bool
have_we_seen_it_before (node ** l, int n)
{
  node *head = (node *) malloc (sizeof (node));
  head = *l;
  while (head != NULL) {
    if (head->n == n)
      return TRUE;

    head = head->next;
  }

  node *new = (node *) malloc (sizeof (node));  // if we haven't seen it, add
  new->n = n;                                   // it to the buffer
  new->next = *l;
  *l = new;

  free (head);
  return FALSE;
}

void
remove_duplicates_with_buffer (node ** l)
{
  node *head = (node *) malloc (sizeof (node));
  node *buffer = (node *) malloc (sizeof (node));       // preferably a hash table
  node *tmp = (node *) malloc (sizeof (node));
  buffer = NULL;

  head = *l;
  while (head != NULL) {
    if (have_we_seen_it_before (&buffer, head->n)) {
      tmp = head;
      head->prev->next = head->next;
      head->next->prev = head->prev;
      free (tmp);
    }

    head = head->next;
  }
}

int
main ()
{
  node *l = (node *) malloc (sizeof (node));
  l = NULL;

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

  remove_duplicates (&l);
  travel (l);

  node *m = (node *) malloc (sizeof (node));
  m = NULL;

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
}
