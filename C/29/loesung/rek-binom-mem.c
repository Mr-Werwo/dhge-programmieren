// Rekursiver Binomialkoeffizient mit Merken der Ergebnisse
//
// Aufruf: rek-binom-mem n k
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// rekursiv klappt's bis 34 ohne Überlauf
// (Achtung: Der Aufruf-Zähler läuft bei 34 schon über!)
#define MAX_VAL 34

// Der Aufrufzähler muss für main und für binom gemeinsam sichtbar sein
// ==> global machen!
unsigned int callCnt = 0;

unsigned int binom(unsigned int n, unsigned int k)
{
  // Im Element [n][k] merken wir uns beim ersten Mal Ausrechnen
  // das Ergebnis von binom(n, k) .
  // n und k können bis MAX_VAL gehen ==> + 1 nicht vergessen!!!
  static unsigned int result[MAX_VAL + 1][MAX_VAL + 1];
  
  ++callCnt;  // zähle jeden Aufruf

  // unser n und k sind unsigned ==> Prüfungen auf <0 sind unnötig!
  if (k > n) return 0;

  // Ende der Rekursion (nichtrekursiver Fall) =
  // Der Rand des Pascal'schen Dreiecks:
  // Für diese Zahlen gibt es keine zwei Zahlen schräg darüber,
  // die addiert werden könnten
  if ((k == 0) || (k == n)) return 1;

  if (n > MAX_VAL) {
    fprintf(stderr, "%u über %u ist zu groß (max. %d)\n", n, k, MAX_VAL);
    exit(EXIT_FAILURE);
  }

  // Statische Variablen und Arrays werden automatisch auf 0 initialisiert
  // ==> ist das Array-Element noch 0, wurde binom(n, k) noch nie berechnet,
  // also berechnen und speichern wir es.
  // Rekursion: Berechne die Zahlen links und rechts in der Zeile drüber
  // und speichere deren Summe als n über k.
  if (result[n][k] == 0) {
    result[n][k] = binom(n - 1, k - 1) + binom(n - 1, k);
  }

  return result[n][k];
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s n k\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s über %s = %u\n", argv[1], argv[2],
         binom(atoi(argv[1]),atoi(argv[2])));
  // Das müssen zwei getrennte printf sein:
  // Macht man nur eines, ist undefiniert,
  // ob callCnt vor oder nach binom ausgerechnet wird
  // (davor liefert es 0!).
  printf("Funktionsaufrufe: %u\n", callCnt);

  exit(EXIT_SUCCESS);
}
