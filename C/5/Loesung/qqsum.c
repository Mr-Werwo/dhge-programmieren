// Wiederholte Quersumme
//
// Aufruf: qqsum n
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int n = abs(atoi(argv[1]));

  // wiederhole die ganze Quersummenberechnung,
  // solange die Eingabe bzw. die letzte Quersumme mehrstellig ist
  while (n >= 10) {
    // jetzt kommt unsere Quersummen-Berechnung aus dem vorigen Beispiel...  
    int sum = 0;   // s muss bei jeder Quersumme frisch bei 0 beginnen!
    while (n > 0) {
      sum += n % 10;  // Abkürzung für sum = sum + n % 10;
      n /= 10;        // Abkürzung für n = n / 10;
    } // da ist das innere while (Schleife über die einzelnen Ziffern) aus
    
    // Die gerade berechnete Quersumme s wird unsere neue Eingabezahl n
    // für die nächste Quersummenberechnung
    n = sum;
  } // da ist das äußere while (Wiederholung der Quersummenberechnung) aus

  printf("Wiederholte Quersumme von %s: %d\n", argv[1], n);

  exit(EXIT_SUCCESS);
}
