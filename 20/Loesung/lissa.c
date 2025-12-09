// Lissajou'sche Kurven
//
// Aufruf: lissa xfaktor yfaktor phasenversch
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "Aufruf: %s xfaktor yfaktor phasenversch\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Multiplikationsfaktoren der x- und y-Frequenz
  int xfaktor = atoi(argv[1]);
  int yfaktor = atoi(argv[2]);
  // Bewegungseffekt: Um welchen Winkel (Radiant) ‰ndert sich
  // die Phasenverschiebung zwischen x- und y-Schwingung pro Bild?
  double phasenSchritt = atof(argv[3]);
  // winkelSchritt bestimmt die "Dichte" der Linie
  // (die Schrittweite der Zeichen-Schleife)
  // So berechnen, dass keine Lˆcher zwischen den Pixeln bleiben!
  // Je hˆher ein faktor, umso l‰nger die Kurve, umso mehr Pixel sind nˆtig,
  // umso kleiner muss die Schrittweite sein
  double winkelSchritt;
  if (xfaktor >= yfaktor) {
    winkelSchritt = 1 / (500.0 * xfaktor);
  } else {
    winkelSchritt = 1 / (500.0 * yfaktor);
  }

  // Mitte des Fensters in x- und y-Richtung
  // SDL_X_SIZE ist die horizontale Fenstergrˆﬂe in Pixeln
  const int mitteX = SDL_X_SIZE / 2;
  // SDL_Y_SIZE ist die vertikale Fenstergrˆﬂe in Pixeln
  const int mitteY = SDL_Y_SIZE / 2;  
  
  sdlInit();

  // 1 Durchl‰uf der ‰uﬂeren Schleife = ein komplettes Bild
  // Z‰hlvariable der ‰uﬂeren Schleife
  //  = Phasenverschiebung zwischen den beiden Sinuskurven
  // Schrittweite der ‰uﬂeren Schleife = phasenSchritt (eingegeben)
  //  = Ver‰nderung der Kurvenform zwischen zwei Bildern
  for (double phase = 0.0; ; phase += phasenSchritt) {  // endlos!
    sdlSetBlack();
    // Z‰hlvariable der inneren Schleife: Aktueller Winkel der Grundschwingung
    // Eine Periode (360 Grad = 2 Pi Radiant) der Grundschwingung = ganze Kurve
    // Schrittweite der inneren Schleife = winkelSchritt (oben berechnet)
    for (double winkel = 0; winkel < 2 * M_PI; winkel += winkelSchritt) {
      // Berechnung der Pixelkoordinaten des aktuellen Punktes
      int x = mitteX + ((int) (sin(winkel * xfaktor) * (mitteX - 10)));
      int y = mitteY + ((int) (sin(winkel * yfaktor + phase) * (mitteY - 10)));
      sdlDrawPoint(x, y, 0, 255, 0);
    }
    sdlUpdate();
  }

  sdlExit();

  exit(EXIT_SUCCESS);
}
