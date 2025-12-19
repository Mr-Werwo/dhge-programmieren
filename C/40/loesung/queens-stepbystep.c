// Acht-Damen-Problem mit SDL
// Mit Anzeige aller Zwischenschritte
//
// Aufruf: queens damen_anzahl
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sdlinterf.h"

// Maximale Anzahl der Damen (Brett- bzw. Array-Größe)
#define MAX_ANZAHL 30
// Anzeige-Verzögerung zwischen zwei Lösungen in Millisekunden
#define VERZ 2000
// Anzeige-Verzögerung zwischen zwei Zwischenschritten in Millisekunden
#define VERZ_KURZ 200

// Seitenlänge (in Feldern) des Brettes = Anzahl der zu setzenden Damen
int anzahl;

// brett[zeile] speichert die Nummer der Spalte (0...anzahl-1),
// in der die Dame in der jeweiligen Zeile (0...anzahl-1) gerade steht
// Das Brett wird von oben nach unten gefüllt (Zeile 0, Zeile 1, ...)
int brett[MAX_ANZAHL];

// Für die grafische Anzeige:
// Größe eines Feldes am Spielbrett in Pixeln
// (muss ungerade sein, damit das Feld einen Mittelpunkt hat)
int feldgr;
// x- und y-Koordinate des Mittelpunktes des linken oberen Feldes
// (zugleich Mittelpunkt der Dame dort)
int links, oben;

// Zeichne die Feld-Trennstriche, d.h. ein leeres Schachbrett
void felder(void);
// Anzeigen einer Lösung
void loesung(void);
// Darf ich auf die angegebene Position eine Dame setzen?
bool ok(int zeile, int spalte);
// Rekursive Funktion: Versuche in die angegebene Zeile eine Dame zu setzen
void setze(int zeile);

// Zeichne die Feld-Trennstriche, d.h. ein leeres Schachbrett
void felder(void)
{
  // die End-Koordinaten der Trennstriche
  int xl = links - feldgr / 2;                         // x-Koord links
  int xr = links + feldgr / 2 + feldgr * (anzahl - 1); // x-Koord rechts
  int yo = oben - feldgr / 2;                          // y-Koord oben
  int yu = oben + feldgr / 2 + feldgr * (anzahl - 1);  // y-Koord unten
  // Abstand zwischen linker / rechter und oberer / unterer Linie eines Feldes
  int abst = feldgr - 1;   

  for (int x = xl, y = yo; x < xr; x += feldgr, y += feldgr) {
    // Zeichne für jede Zeile und jede Spalte Trennstriche auf beiden Seiten
    // (d.h. die Trennstriche sind alle *doppelte* Linien,
    // außer denen am Rand des Schachbrettes)
    sdlDrawLine(xl, y, xr, y, 255, 0, 0);                // oben
    sdlDrawLine(xl, y + abst, xr, y + abst, 255, 0, 0);  // unten
    sdlDrawLine(x, yo, x, yu, 255, 0, 0);                // links
    sdlDrawLine(x + abst, yo, x + abst, yu, 255, 0, 0);  // rechts
  }
}

// Anzeigen einer Lösung
void loesung(void)
{
  sdlMilliSleep(VERZ);
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
        // Dame zeichnen
        sdlDrawCirc(// x-Wert Mittelpunkt je nach Spalte
                    links + spalte * feldgr,         
                    // y-Wert Mittelpunkt je nach Zeile
                    oben + zeile * feldgr,
                    // Radius = Halbe Feldgröße - Rand           
                    feldgr / 2 - 3, feldgr / 2 - 3,
                    // Farbe gelb
                    255, 255, 0);   
        sdlUpdate();
        sdlMilliSleep(VERZ_KURZ);
        // Versuche, die restlichen Damen zu setzen
        setze(zeile + 1);
        // Dame wieder weglöschen (Kreis wie oben, aber schwarz)
        sdlDrawCirc(links + spalte * feldgr,
                    oben + zeile * feldgr,        
                    feldgr / 2 - 3, feldgr / 2 - 3,
                    0, 0, 0);
        sdlUpdate();
        sdlMilliSleep(VERZ_KURZ);
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

  // Feldgröße und Position des Mittelpunktes des Feldes links oben ausrechnen
  // lass auf allen Seiten mindestens 4 Pixel Rand außerhalb des Schachbrettes
  feldgr = ((SDL_X_SIZE >= SDL_Y_SIZE) ? SDL_Y_SIZE : SDL_X_SIZE) - 9;
  feldgr /= anzahl;
  // mach feldgr ungerade, damit die Felder einen Mittelpunkt haben
  if (feldgr % 2 == 0) { --feldgr; }
  // Mittelpunkt-Position: Halber Rand + halbe Feldgröße  
  links = (SDL_X_SIZE - feldgr * anzahl) / 2 + feldgr / 2;
  oben = (SDL_Y_SIZE - feldgr * anzahl) / 2 + feldgr / 2;

  sdlInit();
  felder();
  sdlUpdate();
  
  setze(0);                          // Wir fangen mit Zeile 0 an
  sdlExit();
  
  exit(EXIT_SUCCESS);
}
