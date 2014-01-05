/* Evaluate an infix calculation with stacks by converting it to postfix
 *
 * example: ./infix_postfix_calculations "((5+7)*9)"
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct stack
{
  int *s;
  int n;
} stack_t;


/* Initialize stack type */
stack_t *
stack_init (int size)
{
  // printf ("int init: %d\n", size);

  stack_t *stack = malloc (sizeof (stack_t));;
  stack->n = -1;
  stack->s = (int *) malloc (size * sizeof (int));

  return stack;
} 

/* Push num to last element of the stack */
void
stack_push (stack_t *stack, int num)
{
  // printf ("int push: %d\n", num);

  stack->n++;
  stack->s[stack->n] = num;
}

/* Pop the last element of the stack */
int
stack_pop (stack_t *stack)
{
  int r = stack->s[stack->n];
  stack->n--;

  // printf ("int pop: %d\n", r);

  return r;
}

/* Evaluate the postfix expression */
int postfix_evaluation (char *postfix)
{
  int i;
  int N = strlen (postfix);

  stack_t *stack = stack_init (N);

  for (i = 0; i < N; i++) {
    if (postfix[i] == '+')
      stack_push (stack, stack_pop (stack) + stack_pop (stack));
    if (postfix[i] == '*')
      stack_push (stack, stack_pop (stack) * stack_pop (stack));
    if ((postfix[i] >= '0') && (postfix[i] <= '9'))
      stack_push (stack, postfix[i++] - '0');
    while ((postfix[i] >= '0') && (postfix[i] <= '9'))
      stack_push (stack, 10 * stack_pop (stack) + (postfix[i++]-'0'));
  }

  return stack_pop (stack);
}

/* Convert the infix expression into a postfix expression */
char * infix_to_postfix (int argc, char *argv[])
{
  char *a = argv[1];
  int N = strlen (a);
  char *postfix = (char *) malloc (N * sizeof (char));
  int i, p = 0;

  printf ("operation: %s\n", argv[1]);

  stack_t *stack = stack_init (N);

  for (i = 0; i < N; i++) {
    if (a[i] == ')') {
      postfix[p++] = stack_pop (stack);
      postfix[p++] = ' ';
    }
    if ((a[i] == '+') || (a[i] == '*'))
      stack_push (stack, a[i]);
    if ((a[i] >= '0') && (a[i] <= '9')) {
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
