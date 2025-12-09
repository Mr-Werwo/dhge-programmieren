// Kleines Grafik-Beispiel: Gedämpfte Schwingung
//
// Aufruf: schwingung anzahl phase bremsfaktor
//
// Klaus Kusche, 2012

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Schrittweite (Winkel im Bogenmaß) beim Zeichnen
#define STEP 0.002

int main(int argc, const char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "Aufruf: %s anzahl phase dämpfungsfaktor\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Anzahl der zu zeichnenden Schwingungen, 1 ... eine Sinuswelle
  double anzahl = atof(argv[1]);
  // Phasenlage, Eingabe in Grad, intern in Bogenmaß
  double phase = atof(argv[2]) * M_PI / 180;
  // Dämpfungsfaktor, 0 ... ungedämpft, >0 ... gedämpft
  double faktor = atof(argv[3]);
  if ((anzahl < 0) || (faktor < 0)) {
    fprintf(stderr, "%s: Unzulässiger Eingabewert\n", argv[0]);
    exit(EXIT_FAILURE);    
  }

  sdlInit();       // mach das Grafik-Fenster auf
  sdlSetBlack();   // mach alle Pixel schwarz

  // Schreife erhöht den aktuellen Winkel (in Bogenmaß!) schrittweise
  for (double winkel = 0; ; winkel += STEP) {
    // aktueller Funktionswert (zwischen -1 und 1)
    double fwert = exp(- winkel * faktor) * sin(winkel + phase);
    // Pixelkoordinaten berechnen
    int x = SDL_X_SIZE * winkel / (2 * M_PI * anzahl);
    int y = SDL_Y_SIZE / 2 - fwert * (SDL_Y_SIZE / 2 - 1);
    // Wenn rechts aus dem Fenster draußen: Fertig
    if (x >= SDL_X_SIZE) break;
    sdlDrawPoint(x, y, 0, 255, 0); // Farbe grün
  }

  sdlUpdate();          // zeige die gezeichneten Striche wirklich an
  sdlMilliSleep(3000);  // warte vor Beenden des Programms 3 Sekunden 
  sdlExit();            // mach das Grafikfenster wieder zu

  exit(EXIT_SUCCESS);
}
