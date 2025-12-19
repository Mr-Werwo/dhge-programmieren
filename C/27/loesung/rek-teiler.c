// Rekursive Ermittlung der Primfaktoren
//
// Aufruf: rek-teiler n
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// Suche und drucke die Teiler von zahl, die größergleich teiler sind
// (wenn alle kleineren Teiler schon herausdividiert sind,
// sind das die verbleibenden Primteiler)
void primfak(int zahl, int teiler)
{
  if (zahl < 0) zahl = -zahl;
  if (teiler < 2) teiler = 2;
  if (teiler > zahl) return;   // Keine Teiler mehr!
  
  if ((zahl % teiler) == 0) {
    // teiler teilt ==> Einmal ausgeben, aus zahl herausdividieren,
    // und *denselben* Teiler in der verbleibenden Zahl nochmals probieren!
    printf("%d\n", teiler);
    primfak(zahl / teiler, teiler);
  } else {
    // teiler teilt nicht ==> ab nächstem teiler weiterprobieren!
    primfak(zahl, teiler + 1);
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int n = atoi(argv[1]);
  printf("Primteiler von %d:\n", n);
  primfak(n, 2);

  exit(EXIT_SUCCESS);
}
