/* Bucket fill the section with the same color of a certain pixel */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int x;
  int y;
  struct node *next;
} node;

typedef struct stack
{
  node *top;
} stack;

typedef enum
{
  FALSE, TRUE
} bool;


int paint_region (int x, int y, int color);
static int do_fill_map (int x, int y, int color);
static node *pop (stack * s);
static void push (stack * s, int x, int y);
static bool empty (stack s);


bool fill[20][10];
bool visited[20][10];
int bitmap[20][10];


static node *
pop (stack * s)
{
  node *ret;

  if (s->top) {
    ret = s->top;
    s->top = s->top->next;
  }

  return ret;
}

static void
push (stack * s, int x, int y)
{
  node *new = (node *) malloc (sizeof (node));
  new->x = x;
  new->y = y;

  new->next = s->top;
  s->top = new;
}

static bool
empty (stack s)
{
  if (s.top)
    return FALSE;
  else
    return TRUE;
}

static int
do_fill_map (int x, int y, int color)
{
  int result = 0;

  // Declare our stack of nodes, and push our starting node onto the stack
  stack s;
  s.top = NULL;
  push (&s, x, y);

  while (!empty (s)) {
    node *top = pop (&s);

    // Check to ensure that we are within the bounds of the grid
    if (top->x < 0 || top->x >= 20)
      continue;
    if (top->y < 0 || top->y >= 10)
      continue;

    // Check that we haven't already visited this position
    if (visited[top->x][top->y])
      continue;

    visited[top->x][top->y] = TRUE;     // Save this position as visited
    if (bitmap[top->x][top->y] == color) {
      // This pixel has the same color and is connected, add it to results
      fill[top->x][top->y] = TRUE;
      result++;

      // Visit every node adjacent to this node.
      push (&s, top->x + 1, top->y);
      push (&s, top->x - 1, top->y);
      push (&s, top->x, top->y + 1);
      push (&s, top->x, top->y - 1);
    }

    free (top);
  }

  return result;
}


int
paint_region (int x, int y, int color)
{
  int c, r;
  int pixels;
  int old_color = bitmap[x][y];

  for (c = 0; c < 20; c++) {
    for (r = 0; r < 10; r++) {
      fill[c][r] = FALSE;
      visited[c][r] = FALSE;
    }
  }

  pixels = do_fill_map (x, y, old_color);

  for (c = 0; c < 20; c++) {
    for (r = 0; r < 10; r++) {
      if (fill[c][r])
        bitmap[c][r] = color;
    }
  }

  return pixels;
}


int
main ()
{
  int c, r;
  int pixels;

  for (c = 0; c < 20; c++) {
    for (r = 0; r < 10; r++) {
      bitmap[c][r] = rand () % 2;
      if (bitmap[c][r] == 0)
        printf (". ");
      else
        printf ("* ");
    }
    printf ("\n");
  }
  printf ("\n");

  pixels = paint_region (10, 5, 4);
  printf ("painted %d pixels: \n\n", pixels);

  for (c = 0; c < 20; c++) {
    for (r = 0; r < 10; r++) {
      if (bitmap[c][r] == 0)
        printf (". ");
      else if (bitmap[c][r] == 1)
        printf ("* ");
      else
        printf ("O ");
    }
    printf ("\n");
  }
  printf ("\n");

  return 0;
}
