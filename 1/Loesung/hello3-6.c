// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
// Erweiterung 6
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
    // mit i von (argc-1) bis 1 runterzählen
    for (int i = argc - 1; i > 0; --i) { 
      // Alternative Möglichkeit: Mit i normal von 1 bis argc-1 raufzählen,
      // aber in der nächsten Zeile Name+Platz (argc - i) statt i ausgeben
      printf("Hallo, %s, %d. Platz!\n", argv[i], i);
    }
  }

  return 0;
}
