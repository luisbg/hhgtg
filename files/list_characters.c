#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int
main ()
{
  char c;
  FILE *fd;
  char filename[20];

  printf ("Enter the name of the file: ");
  scanf ("%s", filename);
  fd = fopen (filename, "rb");

  while (fread (&c, sizeof (char), 1, fd) != 0)
    fwrite (&c, 1, 1, stdout);

  fclose (fd);

  return 0;
}
