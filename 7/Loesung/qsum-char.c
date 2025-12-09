// Quersumme durch Summieren der Buchstaben
//
// Aufruf: qsum-char n
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
// für isdigit
#include <ctype.h>

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    printf("Aufruf: %s n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int sum = 0;
  char c; // das aktuelle Zeichen von argv[1]

  // Schleifenanfang:
  // Wenn das vorderste Zeichen des Wortes '-' ist, beginne bei Zeichen 1
  // sonst beginne bei Zeichen 0
  // Das ? : ist ein if innerhalb einer Rechnung: "Frage ? Ja-Wert : Nein-Wert"
  //
  // Schleifenbedingung:
  // Speichere das i-te Zeichen des ersten argv-Wortes in der Variable c
  // (hier versteckt sich wirklich eine *Zuweisung* in einer Bedingung,
  // das soll *kein* == sein!)
  // und prüfe dann, ob das gespeicherte c noch nicht die Ende-Markierung war.
  for (int i = (argv[1][0] == '-') ? 1 : 0;
       (c = argv[1][i]) != '\0';
       ++i) {
  // Weniger trickreiche und besser lesbare Alternative z.B.:
  //for (i = 0; ; ++i) { // keine Ende-Bedingung, Schleifenende unten mit break 
  //  c = argv[1][i];
  //  if (c == '\0') break;
  //  if ((i == 0) && (c == '-')) continue;  // gleich nächster Durchlauf
    if (isdigit(c)) {  // oder "if ((c >= '0') && (c <= '9')) {"
      sum += c - '0';  // Ascii-Wert von c in Ziffernwert verwandeln
    } else {
      printf("'%c' ist keine Ziffer!\n", c);
      exit(EXIT_FAILURE);
    }
  }

  printf("Quersumme von %s: %d\n", argv[1], sum);

  exit(EXIT_SUCCESS);
}
