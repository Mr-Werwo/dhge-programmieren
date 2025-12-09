// Sieb des Eratosthenes:
// Berechne alle Primzahlen kleiner limit
// (ganz primitiv und ohne Optimierungen)
//
// Aufruf: erat limit
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Grenze für Max. Primzahl = Array-Größe
#define MAX 1000000000

bool prim[MAX];  // wegen Speicherlimit für lokale Variablen:
                 // Global, d.h. *vor* main deklarieren!

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s limit\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int limit = atoi(argv[1]);
  if (limit < 3) {
    fprintf(stderr, "%s: Es gibt keine Primzahlen < %d\n", argv[0], limit);
    exit(EXIT_FAILURE);
  }
  if (limit > MAX) {
    fprintf(stderr, "%s: Ich kann nur bis %d rechnen\n", argv[0], MAX);
    exit(EXIT_FAILURE);
  }

  // nicht vergessen: Zuerst alle auf "true" setzen!
  for (int i = 0; i < limit; ++i) {
    prim[i] = true;
  }  

  for (int i = 2; i < limit; ++i) {
    if (prim[i]) {  // dasselbe wie (prim[i] == true)
      // die i-te Zahl ist noch nicht gestrichen, also eine Primzahl
      printf("%d ", i);
      // streiche alle Vielfachen:
      // zähle ab dem Doppelten der Primzahl i mit Schrittweite i
      // (ab i * i würde auch reichen, denn alle davor sind schon weggestrichen,
      // aber i * i läuft bei rund 45000 über!)
      for (int v = i + i; v < limit; v += i) {
        prim[v] = false;  // v ist sicher nicht prim ==> streichen
      }
    }
  }

  printf("\n");
  
  exit(EXIT_SUCCESS);
}
