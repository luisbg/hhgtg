/*
 * Merge two sorted lists A and B as one linked list
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
  int data;
  struct Node *next;
} Node;

typedef enum
{
  FALSE, TRUE
} bool;


/* Append data to tail of list */
static void
Append (Node ** head, int data)
{
  // printf ("Append: %d\n", data);
  Node *new_node = (Node *) malloc (sizeof (Node));
  new_node->data = data;
  new_node->next = NULL;

  Node *run = *head;
  if (run) {                    // go to last element and insert after it
    while (run->next)
      run = run->next;

    run->next = new_node;
  } else {                      // empty list, new node is head
    *head = new_node;
  }
}

/* Print the list */
static void
Print (Node * head)
{
  while (head != NULL) {
    printf ("%d ", head->data);
    head = head->next;
  }
  printf ("\n");
}

/* Merge the two sorted lists into one */
Node *
MergeLists (Node * headA, Node * headB)
{
  Node *tmp = NULL;

  while (headA && headB) {      // run through both lists until one is empty
    if (headA->data < headB->data) {    // appending the smallest new head
      Append (&tmp, headA->data);
      headA = headA->next;
    } else {
      Append (&tmp, headB->data);
      headB = headB->next;
    }
  }

  while (headA) {               // one of the two lists isn't empty yet
    Append (&tmp, headA->data);
    headA = headA->next;
  }
  while (headB) {
    Append (&tmp, headB->data);
    headB = headB->next;
  }

  return tmp;
}


int
main ()
{
  Node *A = NULL;
  Node *B = NULL;

  Append (&A, 0);
  Append (&A, 3);
  Append (&A, 5);
  Append (&A, 6);
  Append (&A, 7);
  Append (&A, 8);

  Append (&B, 1);
  Append (&B, 2);
  Append (&B, 3);
  Append (&B, 4);
  Append (&B, 5);
  Append (&B, 6);
  Append (&B, 7);
  Append (&B, 8);
  Append (&B, 9);

  Print (A);
  Print (B);

  // Merge the lists
  A = MergeLists (A, B);
  Print (A);

  return 0;
}
