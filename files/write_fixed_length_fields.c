#include <stdio.h>
#include <string.h>

typedef struct
{
  char last[20];
  char first[16];
  char address[32];
  char city[16];
  char zip[8];
} set_of_fields;

int
main ()
{
  char filename[20];
  FILE *fp;
  set_of_fields person;

  printf ("Enter the name of the file: ");
  scanf ("%s", filename);
  fp = fopen (filename, "wb");

  while (1) {
    printf ("Enter a new person?\n Write last name or 'q' to exit: ");
    scanf ("%s", person.last);
    if (strlen (person.last) < 2)
      break;

    printf ("First name: ");
    scanf ("%s", person.first);
    printf ("Street: ");
    scanf ("%s", person.address);
    printf ("City: ");
    scanf ("%s", person.city);
    printf ("Zipcode: ");
    scanf ("%s", person.zip);

    fwrite (&person, sizeof (set_of_fields), 1, fp);
  }

  fclose (fp);
  return 0;
}
