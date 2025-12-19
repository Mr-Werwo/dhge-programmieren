// Zeiten zusammenzählen
//
// Aufruf: zeit z1 z2
// (mit z1 und z2 als ganze Zahl im Format hhmmss, ev. mit '-' davor)
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// berechne die Sekunden aus einer als hhmmss gespeicherten Zeit
int sekunden(int zeit);
// gib "sek" als hh:mm:ss aus
void ausgabe(int sek);


// berechne die Sekunden aus einer als hhmmss gespeicherten Zeit
int sekunden(int zeit)
{
  int orig_zeit = zeit;   // Für Fehlermeldungen
  int s = zeit % 100;     // Sekunden = letzte zwei Stellen
  zeit /= 100;            // letzte zwei Stellen wegstreichen
  int m = zeit % 100;     // Minuten = letzte zwei Stellen von dem, was überbleibt
  zeit /= 100;            // letzte zwei Stellen wegstreichen
  int h = zeit;           // Stunden = was überbleibt

  // wenn zeit negativ ist, sind auch h, m und s negativ (oder 0)
  // ==> Absolutbetrag auf Fehler prüfen!
  if ((abs(h) > 23) || (abs(m) > 59) || (abs(s) > 59)) {
    fprintf(stderr, "Ungültige Zeit %d\n", orig_zeit);
    exit(EXIT_FAILURE);
  }

  return h * 3600 + m * 60 + s;
}

// gib "sek" als hh:mm:ss aus
void ausgabe(int sek)
{
  if (sek < 0) {
    printf("-");
    sek = -sek;
  }

  int s = sek % 60;      // Sekunden = Rest bei der Umwandlung auf Minuten
  sek /= 60;             // Sekunden auf (ganze) Minuten umwandeln
  int m = sek % 60;      // Minuten = Rest bei Umwandlung auf Stunden
  sek /= 60;             // Minuten auf (ganze) Stunden umwandeln
  int h = sek % 24;      // Stunden = Rest bei Umwandlung auf Tage
  int d = sek / 24;      // Stunden auf (ganze) Tage umwandeln

  if (d > 0) {   // mehr als 1 Tag
    printf("%d:", d);
  }

  printf("%02d:%02d:%02d", h, m, s);
}  

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s z1 z2\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int z1 = sekunden(atoi(argv[1]));
  int z2 = sekunden(atoi(argv[2]));

  ausgabe(z1);
  printf(" + ");
  ausgabe(z2);
  printf(" = ");
  ausgabe(z1 + z2);
  printf("\n");

  exit(EXIT_SUCCESS);
}
