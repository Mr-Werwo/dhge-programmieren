// Primfaktorenzerlegung mit schönerer Ausgabe
//
// Aufruf: primfak1+ausg n
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

  if (n <= 1) {
    printf("%d\n", n);
    exit(EXIT_SUCCESS);
  }
  
  for (int teiler = 2; n > 1; ++teiler) {
    // Bis hierher ist alles gleich zu primfak1,
    // und jetzt nehmen wir statt der while-Schleife
    // eine for-Schleife mit derselben Bedingung,
    // die zusätzlich in "anzahl" mitzählt,
    // wie oft sich teiler aus n wegdividieren lässt
    // anzahl muss vor dem for deklariert werden (nicht im for),
    // weil wir es nach dem for noch brauchen
    int anzahl;    // Wie oft teilt der aktuelle Teiler?
    for (anzahl = 0; n % teiler == 0; ++anzahl) {  
      // in der Schleife geben wir noch nichts aus, zählen nur mit ... 
      n = n / teiler;   // kürzer: n /= teiler;
    }
    // aber nach der Schleife: 
    if (anzahl > 0) {
      // wenn teiler mindestens 1 Mal in n enthalten war,
      // geben wir ihn aus, sonst machen wir nichts
      if (anzahl > 1) {         // wenn es öfter als 1 Mal war ... 
        printf("%d^%d ", teiler, anzahl);  // ... schreiben wir die Anzahl dazu
      } else {                  // ... und sonst ...
        printf("%d ", teiler);  // ... geben wir nur den teiler aus
      }
    }
  }

  printf("\n");

  exit(EXIT_SUCCESS);
}
