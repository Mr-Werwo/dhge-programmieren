// Primfaktorenzerlegung, ganz simpel, andere Variante
//
// Aufruf: primfak2 n
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

  if (n <= 1) {         // 0 und 1 haben keine Primteiler
    printf("%d\n", n);
    exit(EXIT_SUCCESS);
  }
  
  int teiler = 2;       // wir beginnen mit 2 als Teiler zu probieren
  
  while (n > 1) {   // solange von unserer Zahl n noch etwas übrig ist...
    if (n % teiler == 0) { // ... schauen wir, ob teiler unser n ohne Rest teilt
      // Ja, "teiler" teilt: Ausgeben, wegdividieren, und
      // denselben Teiler im nächsten Schleifendurchlauf nochmal probieren.
      printf("%d ", teiler);
      n = n / teiler;   // kürzer: n /= teiler;
    } else {
      // Nein, "teiler" teilt nicht (mehr):
      // Im nächsten Schleifenumlauf die nächsthöhere Zahl als Teiler probieren!
      ++teiler;
    }
  }

  printf("\n");

  exit(EXIT_SUCCESS);
}
