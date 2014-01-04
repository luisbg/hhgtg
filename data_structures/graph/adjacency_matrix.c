/* Adjacency Matrix by storing a bi-dimensional array of where each row is a
 * Vertex and each Column is an edge */

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  DISCONNECTED, CONNECTED
} bool;

#define V 7

bool **
create_graph (int vertices)
{
  int i, j;

  //int graph[V][V];
  bool ** adj = malloc (V * sizeof (bool *));
  for (i = 0; i < V; i++)
    adj[i] = malloc (V * sizeof(bool));

  // Set all edges to disconnected
  for (i = 0; i < vertices; i++)
    for (j = 0; j < vertices; j++)
      adj[i][j] = 0;

  // All vertixes are connected with themselves
  for (i = 0; i < vertices; i++)
    adj[i][i] = 1;

  return adj;
}

void
add_edge (bool **graph, int src, int dest)
{
  graph[src][dest] = CONNECTED;
}

void
remove_edge (bool **graph, int src, int dest)
{
  graph[src][dest] = DISCONNECTED;
}

void
display_graph (bool **graph, int vertices)
{
  int v, e;
  for (v = 0; v < vertices; v++) {
    printf ("%d: ", v);
    for (e = 0; e < vertices; e++)
      if (graph[v][e])
        printf ("%d ", e);

    printf ("\n");
  }
}


int
main ()
{
  printf ("Creating a directed graph: \n");
  bool ** graph = create_graph (V);

  add_edge (graph, 0, 1);
  add_edge (graph, 0, 4);
  add_edge (graph, 1, 2);
  add_edge (graph, 1, 3);
  add_edge (graph, 1, 4);
  add_edge (graph, 2, 3);
  add_edge (graph, 3, 4);

  display_graph (graph, V);

  printf ("Removing edges from vertix 1:\n");
  remove_edge (graph, 1, 2);
  remove_edge (graph, 1, 3);
  remove_edge (graph, 1, 4);

  display_graph (graph, V);

  return 0;
}
