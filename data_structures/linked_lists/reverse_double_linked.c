#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node *next;
  struct Node *prev;
} Node;


Node *
reverse_list (Node * head)
{
  Node *run = head;
  Node *tmp, *next, *last;
  while (run) {
    next = run->next;           // save next before changing the pointer

    tmp = run->prev;            // swap next and prev pointers
    run->prev = run->next;
    run->next = tmp;

    if (!next)                  // if next is NULL, we are at the last node
      last = run;               // which is going to be the new head
    run = next;
  }

  return last;                  // return new head
}

Node *
insert_node (Node * head, int data)
{
  Node *tmp = (Node *) malloc (sizeof (Node));;
  tmp->data = data;
  tmp->prev = NULL;
  tmp->next = NULL;

  if (!head)
    return tmp;

  head->prev = tmp;
  tmp->next = head;

  return tmp;
}

void
print_list (Node * head)
{
  if (head == NULL)
    return;

  printf ("> ");
  while (head->next) {
    printf ("%d ", head->data);
    head = head->next;
  }
  printf ("%d ", head->data);

  printf ("< ");
  while (head->prev) {
    printf ("%d ", head->data);
    head = head->prev;
  }
  printf ("%d\n", head->data);
}


int
main ()
{
  Node *head = NULL;
  int c = 0;
  int set[9] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };

  print_list (head);
  reverse_list (head);
  print_list (head);
  printf ("\n");

  head = insert_node (head, 0);
  print_list (head);
  reverse_list (head);
  print_list (head);
  printf ("\n");

  while (c < 9) {
    head = insert_node (head, set[c]);
    c++;
  }

  print_list (head);

  head = reverse_list (head);
  print_list (head);
}
