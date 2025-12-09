// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
// Erweiterung 7
// Eine von vielen möglichen Varianten
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
  } else if (argc == 2) { // genau 1 Name
    printf("Hallo, %s!\n", argv[1]);
  } else {                // mindestens 2 Namen
    printf("Hallo");      // Zeilenanfang
    // Schleife vom Ersten bis zum Vorletzten!
    for (int i = 1; i < argc - 1; ++i) {
      printf(", %s", argv[i]);
    }
    printf(" und %s!\n", argv[argc - 1]); // der Letzte incl. "!" und neue Zeile
  }

  return 0;
}
