/* Bucket fill the section with the same color of a certain pixel */

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 30
#define ROWS 20


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


int paint_region (int col, int row, int bitmap[col][row], int x, int y,
    int color);
static int do_fill_map (int col, int row, int bitmap[col][row],
    bool fill[col][row], int x, int y, int color);
static node *pop (stack * s);
static void push (stack * s, int x, int y);
static bool empty (stack s);


int
paint_region (int col, int row, int bitmap[col][row], int x, int y, int color)
{
  int c, r;
  int pixels;
  int old_color = bitmap[x][y];
  bool fill[col][row];

  pixels = do_fill_map (col, row, bitmap, fill, x, y, old_color);

  for (r = 0; r < row; r++) {
    for (c = 0; c < col; c++) {
      if (fill[c][r])
        bitmap[c][r] = color;
    }
  }

  return pixels;
}

static int
do_fill_map (int col, int row, int bitmap[col][row], bool fill[col][row], int x,
    int y, int color)
{
  int c, r;
  int result = 0;
  bool visited[col][row];

  for (r = 0; r < row; r++) {
    for (c = 0; c < col; c++) {
      fill[c][r] = FALSE;
      visited[c][r] = FALSE;
    }
  }

  // Declare our stack of nodes, and push our starting node onto the stack
  stack s;
  s.top = NULL;
  push (&s, x, y);

  while (!empty (s)) {
    node *top = pop (&s);

    // Check to ensure that we are within the bounds of the grid
    if (top->x < 0 || top->x >= col)
      continue;
    if (top->y < 0 || top->y >= row)
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

void
init_bitmap (int col, int row, int bitmap[col][row])
{
  int c, r;;

  // initialize bitmap
  for (r = 0; r < row; r++) {
    for (c = 0; c < col; c++) {
      bitmap[c][r] = rand () % 2;
      if (bitmap[c][r] == 0)
        printf (". ");
      else
        printf ("* ");
    }
    printf ("\n");
  }
  printf ("\n");

  return;
}


int
main ()
{
  int col = COLUMNS;
  int row = ROWS;

  int c, r;
  int pixels;
  int bitmap[col][row];
  int x = 16, y = 12, color = 4;        // pixel to bucket fill and color

  init_bitmap (col, row, bitmap);

  // paint region connected to pixel
  pixels = paint_region (col, row, bitmap, x, y, color);
  printf ("painted %d pixels: \n\n", pixels);

  for (r = 0; r < row; r++) {
    for (c = 0; c < col; c++) {
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
