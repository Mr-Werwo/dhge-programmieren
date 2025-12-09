// Primfaktorenzerlegung, ganz simpel
//
// Aufruf: primfak1 n
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

  // zum Faktorenzerlegen lässt man das Vorzeichen weg
  int n = abs(atoi(argv[1]));  

  if (n <= 1) {            // 0 und 1 haben keine Primteiler
    printf("%d\n", n);
    exit(EXIT_SUCCESS);
  }
  
  // probiere alle Zahlen ab 2 der Reihe nach als Teiler,
  // solange wir nicht alle Teiler von n gefunden und wegdividiert haben,
  // d.h. solange n noch größer als 1 ist.
  for (int teiler = 2; n > 1; ++teiler) {
    // Für jeden zu probierenden Teiler:
    // Wiederhole solange er n ohne Rest teilt
    // (oder eben gar nicht, wenn er n von Anfang an nicht teilt):
    while (n % teiler == 0) {  
      printf("%d ", teiler);  // gib ihn aus ...
      n = n / teiler;         // und dividiere ihn aus n weg
                              // (kürzer: n /= teiler; )
    }
  }

  printf("\n");

  exit(EXIT_SUCCESS);
}
