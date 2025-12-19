// Acht-Damen-Problem
//
// Aufruf: queens damen_anzahl
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// für usleep, nur Linux
#include <unistd.h>
// für Sleep, nur Windows
//#include <windows.h>

// Maximale Anzahl der Damen (Brett- bzw. Array-Größe)
#define MAX_ANZAHL 30
// Anzeige-Verzögerung zwischen zwei Lösungen in Millisekunden
#define VERZ 500

// Seitenlänge (in Feldern) des Brettes = Anzahl der zu setzenden Damen
int anzahl;

// brett[zeile] speichert die Nummer der Spalte (0...anzahl-1),
// in der die Dame in der jeweiligen Zeile (0...anzahl-1) gerade steht
// Das Brett wird von oben nach unten gefüllt (Zeile 0, Zeile 1, ...)
int brett[MAX_ANZAHL];

// Anzeigen einer Lösung
void loesung(void);
// Darf ich auf die angegebene Position eine Dame setzen?
bool ok(int zeile, int spalte);
// Rekursive Funktion: Versuche in die angegebene Zeile eine Dame zu setzen
void setze(int zeile);

// Anzeigen einer Lösung
void loesung(void)
{
  // Terminal-Fenster-Inhalt löschen
  system("clear");  // Linux
  //system("cls");    // Windows  
  putchar('\n');
  
  for (int zeile = 0; zeile < anzahl; ++zeile) {
    putchar(' ');
    for (int spalte = 0; spalte < brett[zeile]; ++spalte) {
      putchar(' ');
      putchar(' ');
    }
    putchar('(');
    putchar(')');
    putchar('\n');
  }
  
  // VERZ ms warten
  usleep(VERZ * 1000);  // Linux, aus unistd.h, Argument = Mikrosekunden
  //Sleep(VERZ);          // Windows, aus windows.h, Argument = Millisekunden
}

// Darf ich auf die angegebene Position eine Dame setzen?
// In allen Zeilen < zeile steht schon eine Dame,
// in allen Zeilen >= zeile steht noch keine Dame.
bool ok(int zeile, int spalte)
{
  for (int z = 0; z < zeile; ++z) {    // prüfe alle schon belegten Zeilen:
    int z_abstand = z - zeile;         // Abstand der Damen in Zeilen
    int s_abstand = brett[z] - spalte; // Abstand der Damen in Spalten
    if ((s_abstand == 0) ||            // gleiche Spalte?
        (z_abstand == s_abstand) ||    // gleiche \-Diagonale?
        (z_abstand == -s_abstand))     // gleiche /-Diagonale?
      return false;                    // Dame darf da nicht stehen!
  }
  
  return true;                         // alle Zeilen geprüft: Position ist ok
}

// Rekursive Funktion:
// Versuche in die angegebene Zeile eine Dame zu setzen
// In allen Zeilen < zeile steht schon eine Dame,
// in allen Zeilen >= zeile steht noch keine Dame.
void setze(int zeile)
{
  if (zeile == anzahl) {
    // Alle Damen (Zeilen) sind schon gesetzt: Lösung gefunden
    loesung();                     
  } else {
    // prüfe alle Spalten der angegebenen Zeile
    for (int spalte = 0; spalte < anzahl; ++spalte) {
      if (ok(zeile, spalte)) {     // Position erlaubt?
        brett[zeile] = spalte;     // Setze die Dame
        // Versuche, die restlichen Damen zu setzen
        setze(zeile + 1);
      }
    }
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s anzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  anzahl = atoi(argv[1]);
  if ((anzahl <= 0) || (anzahl > MAX_ANZAHL)) {
    fprintf(stderr, "%s: Damen-Anzahl muss > 0 und <= %d sein!\n",
            argv[0], MAX_ANZAHL);
    exit(EXIT_FAILURE);
  }

  setze(0);                          // Wir fangen mit Zeile 0 an

  exit(EXIT_SUCCESS);
}
