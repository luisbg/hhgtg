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


void insert (node ** leaf, int key);
void delete (node ** leaf, int key);
node *search_key (node * leaf, int key);
void destroy_tree (struct node *leaf);
void traverse (struct node *leaf);

/* insert a key into the tree */
void
insert (node ** leaf, int key)
{
  if (!*leaf) {
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
  if (!head->right && head->left) {      // only has left child
    if (parent->left == head)   // link past the node
      parent->left = head->left;        // can also be previous case
    else                        // after we switched values
      parent->right = head->left;

    free (head);
    return;

  }
  if (head->right && !head->left) {      // only has right child
    if (parent->left == head)   // link past the node
      parent->left = head->right;
    else
      parent->right = head->right;

    free (head);
    return;

  }
  if (!head->right && !head->left) {      // no children
    if (parent->right == head)
      parent->right = NULL;
    else
      parent->left = NULL;

    free (head);
    return;
  }
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
traverse (struct node *leaf)
{
  if (leaf) {
    traverse (leaf->left);
    printf ("%d ", leaf->key);
    traverse (leaf->right);
  }
}

static int
get_height (struct node *leaf)
{
  if (!leaf)
    return 0;

  int lefth = get_height (leaf->left);
  int righth = get_height (leaf->right);

  if (lefth < righth)
    return righth + 1;
  else
    return lefth + 1;
}

static int
check_balanced_height (struct node *leaf)
{
  if (!leaf)
    return 0;                   // height of 0

  /* Check if left is balanced */
  int lefth = check_balanced_height (leaf->left);
  if (lefth == -1) {
    return -1;                  // not balanced
  }
  int righth = check_balanced_height (leaf->right);
  if (righth == -1) {
    return -1;                  // not balanced
  }

  /* check if current node is balanced */
  int hdiff = lefth - righth;
  if (hdiff > 1 || hdiff < -1)
    return -1;
  else {
    if (lefth < righth)
      return righth + 1;
    else
      return lefth + 1;
  }
}

bool
is_balanced_recursive (struct node * leaf)
{
  // this function calls same nodes repeatedly, sub-optimal O(n^2)
  if (!leaf)
    return TRUE;                // Base case

  int height_diff = get_height (leaf->left) - get_height (leaf->right);
  if (height_diff > 1 || height_diff < -1)
    return FALSE;
  else
    return is_balanced_recursive (leaf->left)
        && is_balanced_recursive (leaf->right);
}

bool
is_balanced (struct node * leaf)        // O(n)
{
  if (check_balanced_height (leaf) != -1)
    return TRUE;
  else
    return FALSE;
}

int
main ()
{
  node *root = NULL;
  int nodes[10] = { 8, 9, 4, 6, 3, 10, 7, 5, 1, 2 };
  int c;

  for (c = 0; c < 6; c++) {
    printf ("inserting: %d\n", nodes[c]);
    insert (&root, nodes[c]);
  }
  printf ("max height is: %d\n", get_height (root));
  printf ("is it balanced? %s\n", is_balanced (root) ? "yes" : "no");

  for (; c < 10; c++) {
    printf ("inserting: %d\n", nodes[c]);
    insert (&root, nodes[c]);
  }
  printf ("max height is: %d\n", get_height (root));
  printf ("is it balanced? %s\n", is_balanced (root) ? "yes" : "no");
}
