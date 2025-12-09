// Primfaktorenzerlegung, ganz simpel, andere Variante
//
// Aufruf: primfak2+ausg n
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
  
  int teiler = 2;       // wir beginnen mit 2 als Teiler zu probieren
  int anzahl = 0;       // ... und bisher hat 2 null Mal geteilt
  
  while (1) {       // der Schleifen-"Ausgang" ist jetzt unten nach der Ausgabe,
                    // denn nach der letzten Division müssen wir noch ausgeben!
    if (n % teiler == 0) { // teilt teiler unser n ohne Rest?
      // Ja, "teiler" teilt: Zählen, wegdividieren, und
      // denselben Teiler im nächsten Schleifendurchlauf nochmal probieren.
      ++anzahl;
      n = n / teiler;   // kürzer: n /= teiler;
    } else {
      // teiler teilt kein weiteres Mal
      // Wenn der aktuelle teiler n mindestens 1 Mal geteilt hat: Ausgeben!
      if (anzahl > 0) {
        if (anzahl > 1) {         // wenn es öfter als 1 Mal war ... 
          printf("%d^%d ", teiler, anzahl); // ... schreiben wir die Anzahl dazu
        } else {                  // ... und sonst ...
          printf("%d ", teiler);  // ... geben wir nur den teiler aus
        }
        // wenn n dadurch 1 geworden ist, sind wir fertig: Schleife beenden
        if (n == 1) break;
        // Sonst: Fang beim neuen Teiler wieder bei 0 zu zählen an
        anzahl = 0;
      }
      // im nächsten Schleifenumlauf die nächsthöhere Zahl als Teiler probieren!
      ++teiler;
    }
  }

  printf("\n");

  exit(EXIT_SUCCESS);
}
