// Funktion strtoupper + main zum Testen
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 4096

char *strtoupper(char *str)
{
  for (int i = 0; str[i]; ++i) {
    str[i] = toupper(str[i]);
  }
  return str;
}

int main(void)
{
  char line[MAX_LEN];

  while (fgets(line, sizeof (line), stdin)) {
    fputs(strtoupper(line), stdout);
  }

  exit(EXIT_SUCCESS);
}
