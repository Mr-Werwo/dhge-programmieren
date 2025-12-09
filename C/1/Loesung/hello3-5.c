// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
// Erweiterung 5
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    printf("Hallo, wer bist du?\n");
  } else {
    printf("Hallo, %s, du bist Erster!\n", argv[1]);
    // Schleife beginnt erst beim Zweiten!
    for (int i = 2; i < argc; ++i) {  
      // Alternative Möglichkeit:
      // Schleife wie bisher beim Ersten beginnen lassen,
      // aber in der Schleife mit if (i == 1) {...} else {...}
      // zwischen dem Ersten und den anderen unterscheiden
      printf("Hallo, %s, %d. Platz!\n", argv[i], i);
    }
  }

  return 0;
}
