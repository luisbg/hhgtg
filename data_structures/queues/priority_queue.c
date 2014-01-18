#include <stdlib.h>
#include <stdio.h>


typedef struct Item
{
  int priority;
  char label[32];
} Item_t;

typedef struct PQ
{
  Item_t *q;
  int N;
} PQ_t;


PQ_t *
pq_init (int maxN)
{
  PQ_t * pq = (PQ_t *) malloc (sizeof (PQ_t));
  pq->q  = malloc (maxN * sizeof (Item_t));
  pq->N = 0;
}

int
pq_empty (PQ_t * pq)
{
  return pq->N == 0;
}

void
pq_insert (PQ_t * pq, Item_t v)
{
  printf ("Insert: %d :: %s\n", v.priority, v.label);

  pq->N++;
  pq->q[pq->N] = v;
}

Item_t
pq_del_max (PQ_t * pq)
{
  int j, max = 0;
  Item_t tmp;

  for (j = 1; j < pq->N; j++)
    if (pq->q[max].priority < pq->q[j].priority)
      max = j;

  tmp = pq->q[max];
  pq->q[max] = pq->q[pq->N - 1];
  pq->q[pq->N - 1] = tmp;

  return pq->q[--pq->N];
}


int main ()
{
  int i, p;
  Item_t v[12];
  Item_t w;

  PQ_t *pq = pq_init (12);

  for (i = 0; i < 12; i++) {
    p = rand() % 100;
    v[i].priority = p;
    sprintf (v[i].label, "word %d", p);

    pq_insert (pq, v[i]);
  }

  printf ("\nGet priorities:\n");
  for (i = 0; i < 4; i++) {
    w = pq_del_max (pq);
    printf ("%s\n", w.label);
  }

  for (i = 0; i < 4; i++) {
    p = rand() % 100;
    v[i].priority = p;
    sprintf (v[i].label, "word %d", p);

    pq_insert (pq, v[i]);
  }

  printf ("\nGet priorities:\n");
  while (!pq_empty (pq)) {
    w = pq_del_max (pq);
    printf ("%s\n", w.label);
  }

  return 0;
}
