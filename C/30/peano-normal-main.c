// Normale Peano-Kurve (Angabe: Hauptprogramm zum Erweitern)
//
// Aufruf: peano-normal rek_tiefe
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sdlinterf.h"

int xPos, yPos; // aktuelle x- und y-Position, in Pixel (0/0 = links oben)
int richtung;   // aktuelle Richtung, wichtig ist der Rest bei Division durch 4:
                // 0 ... rechts (+x), 1 ... rauf (-y),
                // 2 ... links (-x), 3 ... runter (+y)
int schritt;    // Wie viele Pixel ist ein Teilstrich in x- und y-Richtung lang?
int verz;       // Verzögerung nach jedem Schritt, in Millisekunden

// Farb-Tabelle
const int R[] = {   0,  85, 170, 255, 170,  85,   0,   0,   0 };
const int G[] = { 255, 170,  85,   0,   0,   0,   0,  85, 170 };
const int B[] = {   0,   0,   0,   0,  85, 170, 255, 170,  85 };

// Hier fehlen die Funktionen zeichne, lr und rl
// Zeichne einfachen Strich
void strich(void);
// Links-rechts- / Rechts-links-Kombination mit Rekursion der Tiefe "tiefe" 
void lr(int tiefe);
void rl(int tiefe);

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s rekursionstiefe\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Rekursionstiefe (0 würde gar nichts zeichnen)
  int tiefe = atoi(argv[1]);
  if (tiefe <= 0) {
    fprintf(stderr, "%s: Rekursionstiefe muss > 0 sein!\n", argv[0]);
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
  seite = schritt * (potenz - 1);
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
  verz = 4000 / pow(8, tiefe);

  sdlInit();
  rl(tiefe);
  // "ewig" anzeigen, dabei alle 100 ms auf "beenden" prüfen
  for (;;) { sdlMilliSleep(100); }
  sdlExit();
  
  exit(EXIT_SUCCESS);
}
