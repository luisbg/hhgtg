/* Given an array for which the ith element is the price of a given stock on
 * day i. Design an algorithm to find the maximum profit if you wereo only
 * permitted to complete at most one transaction (buy once and sell once).
 */

#include <stdio.h>

#define INT_MAX 2147483647

int
max_profit (int *prices, int pricesSize)
{
  int min_price_seen = INT_MAX;
  int max_profit = 0;

  for (int p = 0; p < pricesSize; p++) {
    if (prices[p] < min_price_seen)
      min_price_seen = prices[p];
    else if (prices[p] - min_price_seen > max_profit)
      max_profit = prices[p] - min_price_seen;
  }

  return max_profit;
}

int
main ()
{
  int stock_a[6] = { 7, 1, 5, 3, 6, 4 };
  int stock_b[5] = { 7, 6, 4, 3, 1 };
  int stock_c[7] = { 1, 3, 4, 6, 7, 9 };

  printf ("Max profit of the following stock day prices windows:\n[");
  for (int i = 0; i < 5; i++)
    printf ("%d, ", stock_a[i]);
  printf ("%d] -> %d\n[", stock_a[5], max_profit (stock_a, 6));

  for (int i = 0; i < 4; i++)
    printf ("%d, ", stock_b[i]);
  printf ("%d] -> %d\n[", stock_b[4], max_profit (stock_b, 5));

  for (int i = 0; i < 6; i++)
    printf ("%d, ", stock_c[i]);
  printf ("%d] -> %d\n", stock_c[6], max_profit (stock_c, 7));

  return 0;
}
