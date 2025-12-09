// Näherung der Quadratwurzel, mit Anzeige der Schritte
//
// Aufruf: root-count x
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s x\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  double x = atof(argv[1]);
  if (x < 0) {
    fprintf(stderr, "%s: Eine negative Zahl hat keine Wurzel.\n", argv[0]);
    exit(EXIT_FAILURE);
  }
 
  double w = x; // w ... Wurzel-Näherung, erster Näherungswert = x
  int schritt = 0; // zum Mitzählen der Näherungsschritte
  // statt "schritt" separat zu zählen,
  // könnte man auch ein "for" statt dem "while" verwenden:
  // for (schritt = 0; fabs(w * w - x) > x * 1e-10; ++schritt) {
  while (fabs(w * w - x) > x * 1e-10) {  
    w = (w + x / w) / 2;
    printf("%.15g\n", w);   // in jedem Schritt die neue Näherung ausgeben
    ++schritt;
  }

  printf("Wurzel von %.15g: %.15g nach %d Schritten (laut sqrt: %.15g)\n",
         x, w, schritt, sqrt(x));

  exit(EXIT_SUCCESS);
}
