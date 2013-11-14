#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int key;
  struct node *left;
  struct node *right;
} node;


void insert (node **leaf, int key)
{
  if( *leaf == NULL ) {
    *leaf = (node *) malloc (sizeof (node));
    (*leaf)->key = key;

    /* initialize the children to null */
    (*leaf)->left = NULL;    
    (*leaf)->right = NULL;  

  } else if(key <= (*leaf)->key) {
    /* if smaller recurse to the left branch */
    insert (&(*leaf)->left, key);

  } else if(key > (*leaf)->key) {
    /* if bigger recurse to the right branch */
    insert (&(*leaf)->right, key);
  }
}

node *search (node *leaf, int key)
{
  if( leaf != NULL ) {
    printf ("%d ->", leaf->key);

    if(key==leaf->key) {
      printf ("\n");
      return leaf;
    } else if(key < leaf->key) {
      return search (leaf->left, key);
    } else {
      return search (leaf->right, key);
    }
  }
  else {
    return NULL;
  }
}

void destroy_tree(struct node *leaf)
{
  if( leaf != NULL )
  {
    destroy_tree (leaf->left);
    destroy_tree (leaf->right);
    free (leaf);
  }
}


int main () {
  node * root = NULL;

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

  search (root, 10);
  search (root, 5);
  search (root, 2);
  search (root, 9);
}
