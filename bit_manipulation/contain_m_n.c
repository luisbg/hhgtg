#include <stdio.h>
//#include <stdint.h>

typedef enum
{
  FALSE, TRUE
} bool;

bool
getbit (int num, int i)
{
  return ((num & (1 << i)) != 0);
}

void
update_bit (int *num, int i, int v)
{
  if (v)
    *num = *num |= (1 << i);    // set
  else
    *num = *num &= ~(1 << i);   // clear
}

int
contain_m_in_n (int m, int *n, int j, int i)
{
  int c;
  int s = j - i;

  for (c = j; c >= i; c--) {
    update_bit (n, c, getbit (m, s));
    --s;
  }
}

int
main ()
{
  int c;
  unsigned int n = 1024;
  unsigned int m = 16 + 2 + 1;
  int j = 6;
  int i = 2;

  printf ("n: ");
  for (c = 31; c >= 0; c--) {
    printf ("%d", getbit (n, c));
  }
  printf ("\nm: ");
  for (c = 31; c >= 0; c--) {
    printf ("%d", getbit (m, c));
  }
  printf ("\nj: %d", j);
  printf ("\ni: %d", i);

  contain_m_in_n (m, &n, j, i);

  printf ("\nresult: ");
  for (c = 31; c >= 0; c--) {
    printf ("%d", getbit (n, c));
  }

  printf ("\n");
}
