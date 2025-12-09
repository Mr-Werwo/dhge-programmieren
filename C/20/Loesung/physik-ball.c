// Kleines Grafik-Beispiel: Ballwurf
//
// Aufruf: physik-ball winkel geschwindigkeit gummifaktor
//
// Klaus Kusche, 2012

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Schrittweite beim Zeichnen (Zeit, sek)
#define STEP 0.002

// Erdbeschleunigung
#define G 9.81

int main(int argc, const char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "Aufruf: %s winkel geschwindigkeit gummifaktor\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Abwurfwinkel, Eingabe in Grad, intern in Bogenmaß
  double winkel = atof(argv[1]) * M_PI / 180;
  // Abwurfgeschwindigkeit, m/s
  double geschw = atof(argv[2]);
  // Gummi-Dämpfungsfaktor 0...1
  double faktor = atof(argv[3]);
  // aktuelle Geschwindigkeit in x- und y-Richtung
  double vx = geschw * cos(winkel);
  double vy = geschw * sin(winkel);
  if ((winkel < 0) || (winkel > 90) || (geschw <= 0) || (faktor < 0)) {
    fprintf(stderr, "%s: Unzulässiger Eingabewert\n", argv[0]);
    exit(EXIT_FAILURE);    
  }

  sdlInit();       // mach das Grafik-Fenster auf
  sdlSetBlack();   // mach alle Pixel schwarz

  // Schleife über die Zeit
  // Achtung: Die Schleifenvariablen sind Kommazahlen!
  // Wir haben 2 Zeiten:
  // tx = aktuelle Zeit in x-Richtung, wächst stetig seit initialem Wurf
  // ty = aktuelle Zeit in y-Richtung, beginnt bei jedem Aufprall wieder bei 0
  for (double tx = 0, ty = 0; ; tx += STEP, ty += STEP) {
    // aktuelle Höhe
    double h = vy * ty - (G / 2) * ty * ty;
    if ((h <= 0) && (tx > 0)) {
      // h <=0 ... Ball schlägt am Boden auf
      vy = faktor * vy; // y-Geschwindigkeit wird durch Gummi-Verluste reduziert
      h = ty = 0;       // Höhe und y-Zeit beginnen wieder bei 0
    }
    // Pixel-Koordinaten berechnen (0/0 ist links oben)
    int x = vx * tx;
    int y = (SDL_Y_SIZE - 1) - h;
    if ((x >= SDL_X_SIZE) || (y < 0)) {
      // Ball flog oben (zu hoch) oder rechts aus dem Fenster ==> fertig!
      break;  
    }
    sdlDrawPoint(x, y, 0, 255, 0); // Farbe grün
    sdlUpdate();        // zeige den gezeichneten Punkt sofort an
  }

  sdlMilliSleep(3000);  // warte vor Beenden des Programms 3 Sekunden 
  sdlExit();            // mach das Grafikfenster wieder zu

  exit(EXIT_SUCCESS);
}
