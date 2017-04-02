#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int
main ()
{
  char c;
  FILE *fp;
  char filename[20];

  printf ("Enter the name of the file: ");
  scanf ("%s", filename);
  fp = fopen (filename, "rb");

  while (fread (&c, sizeof (char), 1, fp) != 0)
    fwrite (&c, 1, 1, stdout);

  fclose (fp);

  return 0;
}
