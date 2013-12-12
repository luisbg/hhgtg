/* Find the minimum number of steps between point A and B */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int x, y;
  int steps;                    // Number of steps we have taken to reach this point
} node;

typedef struct queue_node
{
  node *data;
  struct queue_node *next;
} queue_node;

typedef struct queue
{
  queue_node *head;
  queue_node *last;
} queue;

typedef enum
{
  FALSE, TRUE
} bool;

static void init_queue (queue * q);
static void enqueue (queue * q, int x, int y, int steps);
static node *dequeue (queue * q);
static bool empty_queue (queue q);

int
min_steps (int w, int h, bool grid[w][h], int start_x, int start_y,
    int end_x, int end_y)
{
  int c, r;
  int x_delta, y_delta;
  bool visited[w][h];
  node *top = NULL;
  queue q;

  for (r = 0; r < h; r++) {
    for (c = 0; c < w; c++) {
      visited[c][r] = FALSE;
    }
  }

  init_queue (&q);

  // enqueue starting position with 0 steps
  enqueue (&q, start_x, start_y, 0);

  while (!empty_queue (q)) {
    top = dequeue (&q);

    // Check if out of bounds
    if (top->x < 0 || top->x >= w)
      continue;
    if (top->y < 0 || top->y >= h)
      continue;

    // Check if node blocked
    if (!grid[top->x][top->y])
      continue;

    // printf (": %d, %d\n", top->x, top->y);
    // Check if already visited
    if (visited[top->x][top->y])
      continue;
    visited[top->x][top->y] = TRUE;

    if (top->x == end_x && top->y == end_y)
      return top->steps;

    // Generate all of the transitions between nodes
    // Generate the following deltas: (-1,-1), (-1,0), (-1,1), (0,-1), (0,0),
    // (0,1), (1,-1), (1,0), (1,1)
    for (x_delta = -1; x_delta <= 1; x_delta++) {
      for (y_delta = -1; y_delta <= 1; y_delta++) {
        // Add the new node into the queue
        enqueue (&q, top->x + x_delta, top->y + y_delta, top->steps + 1);
      }
    }

    free (top);
  }

  return -1;
}

static void
init_queue (queue * q)
{
  q->head = NULL;
  q->last = NULL;
}

static void
enqueue (queue * q, int x, int y, int steps)
{
  queue_node *new_node = (queue_node *) malloc (sizeof (queue_node));
  node *pos = (node *) malloc (sizeof (node));
  pos->x = x;
  pos->y = y;
  pos->steps = steps;
  new_node->data = pos;
  new_node->next = NULL;

  if (q->head) {
    q->last->next = new_node;
    q->last = new_node;
  } else {
    q->head = new_node;
    q->last = new_node;
  }
}

static node *
dequeue (queue * q)
{
  node *dq = NULL;

  if (q->head) {
    dq = q->head->data;
    q->head = q->head->next;
  }

  return dq;
}

static bool
empty_queue (queue q)
{
  return q.head == NULL;
}

void
init_map (int w, int h, bool map[w][h])
{
  int c, r;

  for (r = 0; r < h; r++) {
    for (c = 0; c < w; c++) {
      if (rand () % 10 > 2) {
        map[c][r] = TRUE;
        printf (". ");
      } else {
        map[c][r] = FALSE;
        printf ("X ");
      }
    }
    printf ("\n");
  }
  printf ("\n");

  return;
}


int
main ()
{
  int w = 30;
  int h = 20;
  int start_x = 0, start_y = 0;
  int end_x = 29, end_y = 19;
  int steps;
  bool map[w][h];

  init_map (w, h, map);

  steps = min_steps (w, h, map, start_x, start_y, end_x, end_y);
  printf ("min number of steps between %d,%d and %d,%d: %d\n",
      start_x, start_y, end_x, end_y, steps);

  return 0;
}
