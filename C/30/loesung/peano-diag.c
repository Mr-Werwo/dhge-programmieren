// Diagonale Peano-Kurve
//
// Aufruf: peano-diag rek_tiefe
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sdlinterf.h"

int xPos, yPos; // aktuelle x- und y-Position, in Pixel (0/0 = links oben)
int richtung;   // aktuelle Richtung, wichtig ist der Rest bei Division durch 4:
                // 0 ... rechts runter (+x+y), 1 ... rechts rauf (+x-y),
                // 2 ... links rauf (-x-y), 3 ... links runter (-x+y)
int schritt;    // Wie viele Pixel ist ein Teilstrich in x- und y-Richtung lang?
int verz;       // Verzögerung nach jedem Schritt, in Millisekunden

// Farb-Tabelle
const int R[] = {   0,  85, 170, 255, 170,  85,   0,   0,   0 };
const int G[] = { 255, 170,  85,   0,   0,   0,   0,  85, 170 };
const int B[] = {   0,   0,   0,   0,  85, 170, 255, 170,  85 };

// Zeichne das Muster mit Rekursion der Tiefe "tiefe" für jeden Teilstrich
void zeichne(int tiefe);

void zeichne(int tiefe)
{
  if (tiefe == 0) {
    // zeichne Strich von bisheriger zu neuer Position
    // ==> bisherige Position merken, neue Position berechnen
    int xAlt = xPos;
    int yAlt = yPos;
    switch (richtung % 4) {
      case 0:
        xPos += schritt;
        yPos += schritt;
        break;
      case 1:
        xPos += schritt;
        yPos -= schritt;
        break;
      case 2:
        xPos -= schritt;
        yPos -= schritt;
        break;
      case 3:
        xPos -= schritt;
        yPos += schritt;
        break;
    }
    // Farbindex = Richtung modulo Anzahl der Farben
    int farbe = richtung % (sizeof(R) / sizeof(R[0]));
    sdlDrawLine(xAlt, yAlt, xPos, yPos, R[farbe], G[farbe], B[farbe]);
    sdlUpdate();
    sdlMilliSleep(verz);
  } else {
    zeichne(tiefe - 1);
    --richtung;
    zeichne(tiefe - 1);
    ++richtung;
    zeichne(tiefe - 1);
    ++richtung;
    zeichne(tiefe - 1);
    ++richtung;
    zeichne(tiefe - 1);
    --richtung;
    zeichne(tiefe - 1);
    --richtung;
    zeichne(tiefe - 1);
    --richtung;
    zeichne(tiefe - 1);
    ++richtung;
    zeichne(tiefe - 1);
  }
} 

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s rekursionstiefe\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Rekursionstiefe
  int tiefe = atoi(argv[1]);
  // Hier ist auch 0 erlaubt:
  // Ergibt einen geraden Strich von links oben nach rechts unten
  if (tiefe < 0) {
    fprintf(stderr, "%s: Rekursionstiefe muss >= 0 sein!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Berechne schritt = Länge eines Teilstriches
  // Entspricht kürzerer Fenster-Seite pro Rekursionsebene ein mal gedrittelt 
  int seite = ((SDL_X_SIZE >= SDL_Y_SIZE) ? SDL_Y_SIZE : SDL_X_SIZE) - 1;
  int potenz = pow(3, tiefe);
  schritt = seite / potenz;
  if (schritt == 0) {
    fprintf(stderr, "%s: Rekursionstiefe ist zu hoch!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Tatsächliche Seitenlänge der Grafik
  seite = schritt * potenz;
  // Anfangsposition = linke obere Ecke so berechnen,
  // dass die Grafik im Fenster schön zentriert ist
  xPos = (SDL_X_SIZE - seite) / 2;
  yPos = (SDL_Y_SIZE - seite) / 2;

  // absoluter Wert von richtung ist egal
  // nur Rest durch 4 ist wichtig, muss am Anfang 0 = "rechts runter" sein 
  // aber richtung darf nicht negativ werden ==> mit großer Zahl anfangen!
  richtung = 1000;
  // je größer die Tiefe, umso mehr Teilstriche
  // ==> umso kürzere Verzogerung pro einzelnem Teilstrich
  verz = 1500 / pow(5, tiefe);

  sdlInit();
  zeichne(tiefe);
  // "ewig" anzeigen, dabei alle 100 ms auf "beenden" prüfen
  for (;;) { sdlMilliSleep(100); }
  sdlExit();
  
  exit(EXIT_SUCCESS);
}
