// Quersumme
//
// Aufruf: qsum n
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  // haben wir überhaupt ein argv[1], d.h. eine Zahl auf der Befehlszeile?
  if (argc != 2) {
    // Wenn nein: Fehlermeldung ausgeben, mit Fehlercode aufhören
    fprintf(stderr, "Aufruf: %s n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // die Quersumme wird immer von der Zahl ohne Vorzeichen berechnet:
  // abs liefert die Zahl, die man reinsteckt, ohne Vorzeichen
  int n = abs(atoi(argv[1]));
 
  int sum = 0;  // in s summieren wir die Ziffern auf: Bei 0 anfangen
  while (n > 0) {       // "solange von n noch etwas übrig ist"
    sum = sum + n % 10; // der Rest bei Division durch 10 ist die Einerstelle,
                        // und die zählen wir zu unserer Quersumme dazu
                        // % kommt wie * und / vor dem +
                        // das lässt sich auch kürzer schreiben: s += n % 10;
    n = n / 10;         // die Division durch 10 streicht die Einerstelle weg
                        // und das wird unser neues n für die nächste Runde
                        // das lässt sich auch kürzer schreiben: n /= 10;
  }

  // nach der Schleife kommt noch die Ausgabe ...
  printf("Quersumme von %s: %d\n", argv[1], sum);

  // ... und das Programm-Ende
  exit(EXIT_SUCCESS);
}
