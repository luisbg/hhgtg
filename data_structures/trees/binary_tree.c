#include <stdlib.h>
#include <stdio.h>

typedef enum
{
  FALSE, TRUE
} bool;

typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
} node;


void insert_node (node ** leaf, int key);
void delete_node (node ** leaf, int key);
int count (struct node *leaf);
node *search_key (node * leaf, int key);
void destroy_tree (struct node *leaf);
void traverse_in_order (struct node *leaf);
void traverse_in_postorder (struct node *leaf);
void traverse_in_preorder (struct node *leaf);

/* insert a key into the tree */
void
insert_node (node ** leaf, int key)
{
  node *run = NULL;
  if (!*leaf) {
    node *new_node = (node *) malloc (sizeof (node));
    if (!new_node)
      return;
    new_node->key = key;
    /* initialize the children to null */
    new_node->left = NULL;
    new_node->right = NULL;
    *leaf = new_node;

    return;
  }

  run = *leaf;
  if (key <= run->key) {
    /* if smaller recurse to the left branch */
    insert_node (&run->left, key);
  } else {
    /* if bigger recurse to the right branch */
    insert_node (&run->right, key);
  }
}

/* returns the address of the node to be deleted, address of its parent and */
/* whether the node is found or not                                         */
static bool
search_parent (struct node **root, int num, struct node **parent, struct
    node **x)
{
  struct node *head;

  head = *root;
  *parent = NULL;

  while (head) {
    /* if the node to be deleted is found */
    if (head->key == num) {
      *x = head;
      return TRUE;
    }

    *parent = head;

    if (head->key > num)
      head = head->left;
    else
      head = head->right;
  }

  return FALSE;
}

/* delete the specified node from the binary tree */
void
delete_node (node ** leaf, int key)
{
  node *parent, *head, *succesor = NULL;
  int found = 0;

  if (!*leaf)
    return;

  search_parent (leaf, key, &parent, &head);

  if (!search_parent (leaf, key, &parent, &head)) {
    printf ("ERROR: %d isn't in the tree", key);
    return;
  }

  if (head->right && head->left) {      //have both childs
    parent = head;              // replace with left child's tree biggest
    succesor = head->right;     // then remove the old locatoin of that value below
                                // (that location had no childs, or just left child)
    while (succesor->left) {
      parent = succesor;
      succesor = succesor->left;
    }

    head->key = succesor->key;
    head = succesor;
  }
  if (!head->right && head->left) {     // only has left child
    if (parent->left == head)   // link past the node
      parent->left = head->left;        // can also be previous case
    else                        // after we switched values
      parent->right = head->left;

    free (head);
    return;

  }
  if (head->right && !head->left) {     // only has right child
    if (parent->left == head)   // link past the node
      parent->left = head->right;
    else
      parent->right = head->right;

    free (head);
    return;

  }
  if (!head->right && !head->left) {    // no children
    if (parent->right == head)
      parent->right = NULL;
    else
      parent->left = NULL;

    free (head);
    return;
  }
}

/* count the number of nodes in the tree */
int
count (struct node *leaf)
{
  if (!leaf)
    return 0;

  return count (leaf->left) + count (leaf->right) + 1;
}

/* height of the tree */
int
height (struct node *leaf)
{
  int u, v;

  if (!leaf)
    return -1;

  u = height (leaf->left);
  v = height (leaf->right);

  if (u > v)
    return u + 1;
  else
    return v + 1;
}

/* search for a key in the tree */
node *
search_key (node * leaf, int key)
{
  if (leaf) {
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

/* destroy the tree and release all memory */
void
destroy_tree (struct node *leaf)
{
  if (leaf) {
    destroy_tree (leaf->left);
    destroy_tree (leaf->right);
    free (leaf);
  }
}

/* traverse the tree in order */
void
traverse_in_order (struct node *leaf)
{
  if (leaf) {
    traverse_in_order (leaf->left);
    printf ("%d ", leaf->key);
    traverse_in_order (leaf->right);
  }
}

/* traverse the tree in pre-order */
void
traverse_in_preorder (struct node * leaf)
{
  if (leaf) {
    printf ("%d ", leaf->key);
    traverse_in_preorder (leaf->left);
    traverse_in_preorder (leaf->right);
  }
}

/* traverse the tree in post-order */
void
traverse_in_postorder (struct node * leaf)
{
  if (leaf) {
    traverse_in_postorder (leaf->left);
    traverse_in_postorder (leaf->right);
    printf ("%d ", leaf->key);
  }
}

bool
validate_tree (struct node * leaf)
{
  if (leaf) {
    if (leaf->left)
      if (leaf->key < leaf->left->key)
        return FALSE;
    if (leaf->right)
      if (leaf->key > leaf->right->key)
        return FALSE;

    if (!validate_tree (leaf->left))
      return FALSE;
    if (!validate_tree (leaf->right))
      return FALSE;
  }

  return TRUE;
}

void
print_node (int key, int h)
{
  int i;

  for (i = 0; i < h; i++)
    printf ("    ");

  printf ("%d\n", key);
}

void
show (node * leaf, int h)
{
  if (!leaf) {
    // print_node ('*', h);
    return;
  }

  show (leaf->right, h + 1);
  print_node (leaf->key, h);
  show (leaf->left, h + 1);
}

int
main ()
{
  node *root = NULL;

  insert_node (&root, 8);
  insert_node (&root, 10);
  insert_node (&root, 4);
  insert_node (&root, 6);
  insert_node (&root, 7);
  insert_node (&root, 9);
  insert_node (&root, 5);
  insert_node (&root, 3);
  insert_node (&root, 1);
  insert_node (&root, 2);

  printf ("show tree: (rotated 90 degrees)\n");
  show (root, 0);

  printf ("search 10\n");
  search_key (root, 10);
  printf ("search 5\n");
  search_key (root, 5);
  printf ("search 2\n");
  search_key (root, 2);
  printf ("search 9\n");
  search_key (root, 9);

  printf ("\n");
  traverse_in_order (root);
  printf ("\n\n");

  printf ("deleting 5\n");
  delete_node (&root, 5);
  traverse_in_order (root);
  printf ("\n");

  printf ("deleting 4\n");
  delete_node (&root, 4);
  traverse_in_order (root);
  printf ("\n");

  printf ("validated?: %s\n", validate_tree (root) ? "yes" : "no");
  printf ("\n");

  printf ("traverse tree in order:\n");
  traverse_in_order (root);
  printf ("\n");

  printf ("traverse tree in pre-order:\n");
  traverse_in_preorder (root);
  printf ("\n");

  printf ("traverse tree in post-order:\n");
  traverse_in_postorder (root);
  printf ("\n\n");

  printf ("number of nodes in the tree: ");
  printf ("%d\n\n", count (root));

  printf ("height of the tree: ");
  printf ("%d\n", height (root));
}
