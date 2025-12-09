// Summe / Mittelwert der eingegebenen Zahlen
//
// Aufruf: mittelw x1 x2 ...
//
// Klaus Kusche, 2011

#include <stdio.h>
// für atof
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {   // keine Zahlen angegeben
    fprintf(stderr, "Aufruf: %s x1 x2 ...\n", argv[0]);
    // Programm gleich mit Status "Fehler" beenden
    // sonst müsste der gesamte Rest des Programms in einem "else" stehen
    return 1;
  }

  // = 0 nicht vergessen, sonst hat summe einen zufälligen Anfangswert!
  double summe = 0;  
  
  for (int i = 1; i < argc; ++i) { // geh alle Worte auf der Befehlszeile durch
    summe = summe + atof(argv[i]); // verwandle das i-te Wort in eine Zahl
                                   // und zähl sie zur Summe dazu
  }
  
  // %16g heißt
  // "setze eine Kommazahl ein, und gib der Zahl insgesamt 16 Zeichen Platz"
  // (die Zahl steht rechtsbündig in den 16 Zeichen),
  // damit die beiden Zahlen schön untereinander stehen
  // man kann auch beide Ausgaben in ein printf schreiben
  printf("Summe:      %16g\n", summe);
  printf("Mittelwert: %16g\n", summe / (argc - 1)); // argc-1: Anzahl der Zahlen

  return 0;
}
