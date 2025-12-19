// Funktion: Minimum und Maximum eines Arrays ermitteln
//
// Aufruf: minmaxfunc z1 z2 z3 ...
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// array ist ein Pointer auf das Array, dessen min und max gesucht werden soll.
// anzahl ist die Anzahl der Elemente im Array.
// minP ist ein Pointer auf die double-Variable,
//   in der das Minimum gespeichert werden soll.
// maxP ist ein Pointer auf die double-Variable,
//   in der das Maximum gespeichert werden soll.
// Der Returnwert ist true bei Erfolg
// und false wenn das Array keine Elemente hat.
bool minMax(const double array[], int anzahl, double *minP, double *maxP)
{
  if (anzahl <= 0) return false;

  // Minimum und Maximum dort speichern, wo minP und maxP hinzeigen ==> mit *
  *minP = *maxP = array[0];

  for (int i = 1; i < anzahl; ++i) {
    if (array[i] < *minP) {
      *minP = array[i];
    }
    if (array[i] > *maxP) {
      *maxP = array[i];
    }
  }

  return true;
}

int main(int argc, const char * argv[])
{
  double z[argc];   // das letzte Element bleibt unbenutzt
  double min, max;  // in diesen Variablen soll minMax sein Ergebnis ablegen

  for (int i = 1; i < argc; ++i) {
    z[i - 1] = atof(argv[i]);
  }

  // Aus z wird automatisch ein Pointer auf den Anfang von z.
  // Von min und max müssen wir die Adresse (einen Pointer auf min bzw. max)
  //   an die Funktion übergeben.
  if (minMax(z, argc - 1, &min, &max)) {
    printf("Minumum: %g, Maximum: %g\n", min, max);
    exit(EXIT_SUCCESS);
  } else {
    fprintf(stderr, "Kein Minumum und Maximum.\n");
    exit(EXIT_FAILURE);
  }
}
