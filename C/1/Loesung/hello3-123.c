// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
// Erweiterung 1, 2 und 3
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    // argv[0] ist der Programmname
    printf("Hallo, ich bin %s, wer bist du?\n", argv[0]);
  } else {
    for (int i = 1; i < argc; ++i) {
      // es müssen hinten so viele Werte wie vorne im Text % sein,
      // und die Reihenfolge muss stimmen:
      // erstes % wird durch ersten Wert ersetzt,
      // zweites % durch zweiten Wert usw.
      printf("Hallo, %s, %d. Platz!\n", argv[i], i);
    }
    printf("Ihr seid %d Leute.\n", argc - 1);  // - 1 wegen Programmnamen
  }
  // Wenn man auch bei 0 Leuten "Ihr seid 0 Leute." ausgeben will,
  // gehört das vorige printf hierher statt in das else {...}

  return 0;
}
