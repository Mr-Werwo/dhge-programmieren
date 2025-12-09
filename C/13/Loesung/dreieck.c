// Ganzzahlige rechtwinkelige Dreieck mit gegebenem maximalem Umfang
//
// Aufruf: dreieck knotenanzahl
// 
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s knotenanzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int knoten = atoi(argv[1]); // Eingabe = Anzahl der Knoten = Grenze für Umfang
  int anzahl = 0; // Anzahl der Lösungen
  
  // Probiere alle möglichen Werte für den Umfang
  // min. Umfang eines ganzzahligen Dreiecks ist 3
  // max. Umfang ist Knotenzahl-1 (zwischen n Knoten sind n-1 Abstände)
  for (int umfang = 3; umfang < knoten; ++umfang) {
    // Probiere alle möglichen Werte für die kürzeste Seite a
    // die kürzeste Seite muss weniger als ein Drittel des Umfangs sein
    for (int a = 1; a < umfang / 3; ++a) {
      // Probiere alle möglichen Werte für die mittlere Seite b
      // die mittlere Seite beginnt bei a + 1,
      // denn ganzzahlige rechtwinkelige Dreiecke mit zwei gleichen Seiten
      // kann es nicht geben
      // statt "for (...) { c = ...; if (...) break;"
      // ginge auch eine Schleife, die mit mit b und c gleichzeitig zählt
      // (b raufzählen, c runterzählen):
      //for (int b = a + 1, c = umfang - (a + b); b < c; ++b, --c) {
      for (int b = a + 1; ; ++b) {
        // berechne die längste Seite c aus dem aktuellen Umfang sowie a und b
        int c = umfang - (a + b);
        // hör mit der b-Schleife auf, sobald b größer c geworden ist
        if (c <= b) break;
        if (a * a + b * b == c * c) {
          ++anzahl;
          printf("%d = %d %d %d\n", umfang, a, b, c);
        }
      }
    }
  }
  
  printf("%d Lösungen\n", anzahl);
  
  exit(EXIT_SUCCESS);
}
