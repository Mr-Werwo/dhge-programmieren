// Minimum und Maximum von Zahlen, mit Position
//
// Aufruf: minmaxpos zahl1 zahl2 zahl3 ...
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    fprintf(stderr, "Aufruf: %s zahl1 zahl2 zahl3 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int min, max;
  min = max = atoi(argv[1]);
  // Wir brauchen 2 neue Variablen:
  // In minpos merken wir uns die Position der Zahl,
  //    die wir zuletzt in min gespeichert haben,
  // und in maxpos merken wir uns die Position der Zahl,
  //    die wir zuletzt in max gespeichert haben.
  // Jedesmal, wenn wir eine neue Zahl in min oder max speichern,
  // speichern wir auch in minpos oder maxpos, die wievielte Zahl das war.
  // Sonst ist alles gleich wie in der alten Lösung.
  // Am Anfang ist die Zahl an Position 1 unser Minimum und Maximum!
  int minpos = 1, maxpos = 1;
  
  for (int i = 2; i < argc; ++i) {
    int z = atoi(argv[i]);
    if (z < min) {
      min = z;    // wenn man die i-te Zahl als neues min speichert
      minpos = i; // merkt man sich auch i als ihre Position
    }
    if (z > max) {
      max = z;    // und bei max genauso
      maxpos = i;
    }
  }

  if (min == max) {
    printf("Alle Zahlen sind gleich %d\n", min);
  } else {
    printf("Minimum: %d (%d. Zahl), Maximum: %d (%d. Zahl)\n",
           min, minpos, max, maxpos);
  }

  exit(EXIT_SUCCESS);
}
