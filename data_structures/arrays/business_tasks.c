/* 
 * Based on TopCoder's BusinessTasks - SRM 236 Div 1:
 *   http://community.topcoder.com/stat?c=problem_statement&pm=1585&rd=6535
 *
 * A busy businessman has a number of equally important tasks which he must
 * accomplish. To decide which of the tasks to perform first, he performs the
 * following operation.
 *
 * He writes down all his tasks in the form of a circular list, so the first task
 * is adjacent to the last task. He then thinks of a positive number. This number
 * is the random seed, which he calls n. Starting with the first task, he moves
 * clockwise (from element 1 in the list to element 2 in the list and so on),
 * counting from 1 to n. When his count reaches n, he removes that task from the
 * list and starts counting from the next available task. He repeats this
 * procedure until one task remains. It is this last task that he chooses to
 * execute.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum {
  FALSE, TRUE
} bool;


int cycle_next (int size, bool used[size], int run) {
  run++;

  if (run == size)  /* end of array, loop back */
    run = 0;

  while (!used[run]) {
    run++;
    if (run == size)
      run = 0;
  }

  return run;
}

char * select_task (char * tasks[], int size, int n) {
  int run = 0, i, tasks_left = size;
  bool used[size];

  for (i = 0; i < size; i++)  /* set all to used */
    used[i] = TRUE;

  while (tasks_left > 1) {
    for (i = 1; i < n; i++) {
      run = cycle_next (size, used, run);
    }

    used[run] = FALSE;
    printf ("drop %s\n", tasks[run]);
    tasks_left--;
    run = cycle_next (size, used, run);
  }

  for (i = 0; i < size; i++)
    if (used[i])
      return tasks[i];
}


int main ()
{
  int i;
  char ** tasks = (char **) malloc (10 * 16 * sizeof (char));
  for (i = 0; i < 10; i++)
    tasks[i] = (char *) malloc (16 * sizeof (char));

  strcpy (tasks[0], "a");
  strcpy (tasks[1], "b");
  strcpy (tasks[2], "c");
  strcpy (tasks[3], "d");
  strcpy (tasks[4], "e");
  strcpy (tasks[5], "f");
  strcpy (tasks[6], "g");
  strcpy (tasks[7], "h");
  strcpy (tasks[8], "i");
  strcpy (tasks[9], "j");

  printf ("%s\n", select_task (tasks, 10, 8));

  return 0;
}

