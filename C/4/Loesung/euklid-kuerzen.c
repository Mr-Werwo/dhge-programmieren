// Kürzen eines Bruches
//
// Aufruf: euklid-kuerzen zaehler nenner
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s zaehler nenner\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Wir brauchen die Variablen aus dem euklid-Beispiel und zusätzlich 2 neue,
  // in denen wir uns den ursprünglichen Zähler und Nenner merken
  // (denn wir brauchen nach der ggt-Berechnung noch die ursprünglichen Werte!).
  // Eingaben auf der Befehlszeile sind der Zähler und der Nenner
  // des zu kürzenden Bruches (jetzt dürfen wir ein "-" noch nicht weglassen)
  int zaehler = atoi(argv[1]);
  int nenner = atoi(argv[2]);
  if (nenner == 0) {
    fprintf(stderr, "%s: 0 im Nenner ist verboten!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // wir berechnen wie im Euklid-Beispiel den ggt
  // von Zähler und Nenner (mit weggelassenem Vorzeichen)
  int a = abs(zaehler);
  int b = abs(nenner);
  
  while (b > 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  // in a ist jetzt der ggT, durch den wir kürzen können

  // Die vordere Hälfte der Ausgabe: Der eingegebene Bruch
  printf("%d/%d = ", zaehler, nenner);
  
  // Das Vorzeichen eines Bruches gehört in den Zähler
  // Wenn der Nenner negativ ist,
  // drehen wir oben und unten das Vorzeichen um
  if (nenner < 0) {
    zaehler = -zaehler;
    nenner = -nenner;
  }
  
  // und jetzt kürzen wir durch den ggt: Oben und unten rausdividieren
  zaehler = zaehler / a;
  nenner = nenner / a;
  
  // Wenn der gekürzte Nenner 1 ist, ...
  if (nenner == 1) {
    // ... geben wir eine ganze Zahl aus
    printf("%d\n", zaehler);
  } else {
    // ... und sonst einen Bruch
    printf("%d/%d\n", zaehler, nenner);
  }

  exit(EXIT_SUCCESS);
}
