// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
// Erweiterung 7
// Eine weitere von vielen möglichen Varianten
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    printf("Hallo, wer bist du?\n");
  // für dieses Beispiel gibt es sehr viele Lösungsmöglichkeiten!
  } else {
    printf("Hallo, %s", argv[1]);  // der Erste
    // Schleife erst ab dem Zweiten!
    for (int i = 2; i < argc ; ++i) {  
      if (i == (argc - 1)) {       // der Letzte: Mit "und" anhängen, kein \n
        printf(" und %s", argv[i]);
      } else {                     // die Mittleren: Mit ", " anhängen, kein \n
        printf(", %s", argv[i]);
      }
    }
    printf("!\n");                 // nach dem Letzten: "!" und neue Zeile
  }

  return 0;
}
