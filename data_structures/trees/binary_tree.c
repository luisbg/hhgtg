#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
} node;


void insert (node ** leaf, int key);
void delete (node ** leaf, int key);
node *search_key (node * leaf, int key);
void destroy_tree (struct node *leaf);
void traverse (struct node *leaf);

void
insert (node ** leaf, int key)
{
  if (*leaf == NULL) {
    *leaf = (node *) malloc (sizeof (node));
    (*leaf)->key = key;

    /* initialize the children to null */
    (*leaf)->left = NULL;
    (*leaf)->right = NULL;

  } else if (key <= (*leaf)->key) {
    /* if smaller recurse to the left branch */
    insert (&(*leaf)->left, key);

  } else if (key > (*leaf)->key) {
    /* if bigger recurse to the right branch */
    insert (&(*leaf)->right, key);
  }
}

/* returns the address of the node to be deleted, address of its parent and */
/* whether the node is found or not                                         */
void
search_parent (struct node **root, int num, struct node **parent, struct
    node **x, int *found)
{
  struct node *q;

  q = *root;
  *found = FALSE;
  *parent = NULL;

  while (q != NULL) {
    /* if the node to be deleted is found */
    if (q->key == num) {
      *x = q;
      *found = TRUE;
      return;
    }

    *parent = q;

    if (q->key > num)
      q = q->left;
    else
      q = q->right;
  }
}

void
delete_node (node ** leaf, int key)
{
  node *root, *parent, *head, *succesor = NULL;
  int found = 0;
  root = *leaf;

  if (*leaf == NULL)
    return;

  search_parent (&root, key, &parent, &head, &found);

  if (found == FALSE)
    return;

  if (head->right && head->left) {  //have both childs
    parent = head;           // replace with left child's tree biggest
    succesor = head->right;  // then remove the old locatoin of that value below
                             // (that location had no childs, or just left child)
    while (succesor->left != NULL) {
      parent = succesor;
      succesor = succesor->left;
    }

    head->key = succesor->key;
    head = succesor;
  }
  if (head->left == NULL && head->left != NULL) {  // only has left child
    if (parent->left == head)                      // link past the node
      parent->left = head->left;                   // can also be previous case
    else                                           // after we switched values
      parent->right = head->left;

    free (head);
    return;

  }
  if (head->right != NULL && head->left == NULL) {  // only has right child
    if (parent->left == head)                       // link past the node
      parent->left = head->right;
    else
      parent->right = head->right;

    free (head);
    return;

  }
  if (head->right == NULL && head->left == NULL) {  // no children
    if (parent->right == head)
      parent->right = NULL;
    else
      parent->left = NULL;

    free (head);
    return;
  }
}

node *
search_key (node * leaf, int key)
{
  if (leaf != NULL) {
    printf ("%d ->", leaf->key);

    if (key == leaf->key) {
      printf ("\n");
      return leaf;
    } else if (key < leaf->key) {
      return search_key (leaf->left, key);
    } else {
      return search_key (leaf->right, key);
    }
  } else {
    return NULL;
  }
}

void
destroy_tree (struct node *leaf)
{
  if (leaf != NULL) {
    destroy_tree (leaf->left);
    destroy_tree (leaf->right);
    free (leaf);
  }
}

void
traverse (struct node *leaf)
{
  if (leaf != NULL) {
    traverse (leaf->left);
    printf ("%d ", leaf->key);
    traverse (leaf->right);
  }
}

int
main ()
{
  node *root = NULL;

  insert (&root, 8);
  insert (&root, 10);
  insert (&root, 4);
  insert (&root, 6);
  insert (&root, 7);
  insert (&root, 9);
  insert (&root, 5);
  insert (&root, 3);
  insert (&root, 1);
  insert (&root, 2);

  printf ("search 10\n");
  search_key (root, 10);
  printf ("search 5\n");
  search_key (root, 5);
  printf ("search 2\n");
  search_key (root, 2);
  printf ("search 9\n");
  search_key (root, 9);

  printf ("\n");
  traverse (root);
  printf ("\n\n");

  printf ("deleting 5\n");
  delete_node (&root, 5);
  traverse (root);
  printf ("\n");

  printf ("deleting 4\n");
  delete_node (&root, 4);
  traverse (root);
  printf ("\n");
}
