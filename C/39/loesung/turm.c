// Turmrechnen
//
// Aufruf: turm n
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // für strlen
#include <ctype.h>   // für isdigit
#include <stdbool.h>

// Array dynamisch anlegen und mit der Zahl in "in" befüllen
int *readNum(const char *in);
// Array als Zahl ausgeben
void writeNum(const int *z);
// Array mit einstelliger Zahl multiplizieren
void multiply(int *z, int n);
// Array durch einstellige Zahl dividieren
void divide(int *z, int n);

// Array dynamisch anlegen und mit der Zahl in "in" befüllen
int *readNum(const char *in)
{
  const int leadingZeroes = 8;  // Anzahl der 0-Elemente vorne dran

  // Gesamte Länge des Arrays:
  // 1 für das Längen-Element ganz vorne
  // + leadingZeroes viele führende Nullen
  // + so viele Elemente, wie die Eingabe Ziffern hat
  int len = 1 + leadingZeroes + strlen(in);
  // calloc setzt das Array gleich auf 0 ==> spart uns eine Schleife
  int *result = calloc(len, sizeof(int));
  if (result == NULL) {
    fprintf(stderr, "calloc failed!\n");
    exit(EXIT_FAILURE);
  }
  result[0] = len; // vorderstes Element soll die Länge enthalten
  // die führenden Nullen sind durch calloc schon auf 0 initialisiert
  
  for (int i = 0; in[i] != '\0'; ++i) {
    if (!isdigit(in[i])) {
      fprintf(stderr, "Ungültiges Zeichen '%c', bitte eine Zahl eingeben.\n",
              in[i]);
      exit(EXIT_FAILURE);
    }
    // ...-'0' verwandelt eine einzelne ASCII-Ziffer in den Ziffernwert
    // dieser wird um 1+leadingZeroes Elemente verschoben in result gespeichert
    result[i + 1 + leadingZeroes] = in[i] - '0';  
  }

  return result;
}

// Array als Zahl ausgeben
void writeNum(const int *z)
{
  bool zeroes = true;  // Bisher nur 0-Elemente?

  // ab z[1], denn z[0] ist die Länge
  for (int i = 1; i < z[0]; ++i) {
    // ' ' statt '0' wenn:
    // - bisher nur 0-Elemente
    // - Wert der aktuellen Ziffer ist 0
    // - wir sind noch nicht bei der hintersten Stelle der gesamten Zahl
    if (zeroes && (z[i] == 0) && (i < z[0] - 1)) {
      putchar(' ');
    } else {
      zeroes = false;
      putchar(z[i] + '0');
    }
  }

  putchar('\n');
}

// Array mit einstelliger Zahl multiplizieren
void multiply(int *z, int n)
{
  int carry = 0;  // der Übertrag
  // von hinten nach vorne (außer Element 0),
  // ziffernweise, wie man händisch multipliziert
  for (int i = z[0] - 1; i > 0; --i) {
    int prod = n * z[i] + carry;
    z[i] = prod % 10;
    carry = prod / 10;
  }

  // Am Ende darf kein Übertrag vor die erste Ziffer bleiben!
  if (carry > 0) {
    fprintf(stderr, "overflow!\n");
    exit(EXIT_FAILURE);
  }
}

// Array durch einstellige Zahl dividieren
void divide(int *z, int n)
{
  int rem = 0;  // der Rest
  // von vorne nach hinten, ziffernweise, wie man händisch dividiert
  for (int i = 1; i < z[0]; ++i) {
    int val = rem * 10 + z[i];
    z[i] = val / n;
    rem = val % n;
  }

  // Nach der letzten Ziffer darf kein Rest bleiben!
  if (rem > 0) {
    fprintf(stderr, "remainder in division!\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s zahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int *zahl = readNum(argv[1]);
  printf("input ");
  writeNum(zahl);

  for (int i = 2; i <= 9; ++i) {
    multiply(zahl, i);
    printf("* %d = ", i);
    writeNum(zahl);
  }
  for (int i = 2; i <= 9; ++i) {
    divide(zahl, i);
    printf("/ %d = ", i);
    writeNum(zahl);
  }

  free(zahl);
  
  exit(EXIT_SUCCESS);
}
