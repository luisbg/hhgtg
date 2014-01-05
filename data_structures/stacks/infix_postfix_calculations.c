/* Evaluate an infix calculation with stacks by converting it to postfix
 *
 * example: ./infix_postfix_calculations "((5+7)*9)"
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct int_stack
{
  int *s;
  int n;
} int_stack_t;

typedef struct char_stack
{
  char *s;
  int n;
} char_stack_t;


int_stack_t *
int_stack_init (int size)
{
  printf ("int init: %d\n", size);

  int_stack_t *stack = malloc (sizeof (int_stack_t));;
  stack->n = -1;
  stack->s = (int *) malloc (size * sizeof (int));

  return stack;
} 

void
int_stack_push (int_stack_t *stack, int num)
{
  printf ("int push: %d\n", num);

  stack->n++;
  stack->s[stack->n] = num;
}

int
int_stack_pop (int_stack_t *stack)
{
  int r = stack->s[stack->n];
  stack->n--;

  printf ("int pop: %d\n", r);

  return r;
}

char_stack_t *
char_stack_init (int size)
{
  printf ("char init: %d\n", size);

  char_stack_t *stack = malloc (sizeof (char_stack_t));
  stack->n = -1;
  stack->s = (char *) malloc (size * sizeof (char));

  return stack;
} 

void
char_stack_push (char_stack_t * stack, char c)
{
  printf ("char push: %c\n", c);
  stack->n++;
  stack->s[stack->n] = c;
}

char
char_stack_pop (char_stack_t * stack)
{
  char r = stack->s[stack->n];
  stack->n--;

  printf ("char pop: %c\n", r);

  return r;
}

int postfix_evaluation (char *postfix)
{
  int i;
  int N = strlen (postfix);

  int_stack_t *stack = int_stack_init (N);

  for (i = 0; i < N; i++) {
    if (postfix[i] == '+')
      int_stack_push (stack, int_stack_pop (stack) + int_stack_pop (stack));
    if (postfix[i] == '*')
      int_stack_push (stack, int_stack_pop (stack) * int_stack_pop (stack));
    if ((postfix[i] >= '0') && (postfix[i] <= '9'))
      int_stack_push (stack, postfix[i++] - '0');
    while ((postfix[i] >= '0') && (postfix[i] <= '9'))
      int_stack_push (stack, 10 * int_stack_pop (stack) + (postfix[i++]-'0'));
  }

  return int_stack_pop (stack);
}

char * infix_to_postfix (int argc, char *argv[])
{
  char *a = argv[1];
  int N = strlen (a);
  char *postfix = (char *) malloc (N * sizeof (char));
  int i, p = 0;

  printf ("operation: %s\n", argv[1]);

  char_stack_t *stack = char_stack_init (N);

  for (i = 0; i < N; i++) {
    if (a[i] == ')') {
      //printf ("%c ", char_stack_pop (stack));
      postfix[p++] = char_stack_pop (stack);
      postfix[p++] = ' ';
    }
    if ((a[i] == '+') || (a[i] == '*'))
      char_stack_push (stack, a[i]);
    if ((a[i] >= '0') && (a[i] <= '9')) {
      // printf ("%c ", a[i]);
      postfix[p++] = a[i];
      postfix[p++] = ' ';
    }
  }
  postfix[++p] = '\0';

  return postfix;
}

int main (int argc, char *argv[])
{
  int result;

  char * postfix = infix_to_postfix (argc, argv);
  printf ("postfix: %s\n", postfix);

  result = postfix_evaluation (postfix);
  printf ("result: %d\n", result);

  return 0;
} 
