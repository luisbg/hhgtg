/* Remove duplicates from an unsorted linked list */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int n;
  struct node *next;
  struct node *prev;
} node;


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

// void remove_duplicates (node **l) {
// }

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
}
