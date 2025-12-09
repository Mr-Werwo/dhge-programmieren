// Kleines Grafik-Demo-Beispiel: Diagonale Linien, Ellipsen...
//
// Aufruf: demo2
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  // SDL_X_SIZE ist die horizontale Fenstergröße in Pixeln
  // SDL_Y_SIZE ist die vertikale Fenstergröße in Pixeln
  const int mitteX = SDL_X_SIZE / 2;  
  const int mitteY = SDL_Y_SIZE / 2;  

  sdlInit();       // mach das Grafik-Fenster auf
  sdlSetBlack();   // mach alle Pixel schwarz

  for (int i = 0; i <= 255 ; ++i) {
    // wir zeichnen pro Durchlauf 4 diagonale Linien rund um die Mitte,
    // die sich immer weiter vom Bildmittelpunkt entfernen
    // Linie 1: Von Mitte oben nach links, am Anfang lila, am Ende rot
    sdlDrawLine(mitteX, mitteY - i, mitteX - i, mitteY, 255, 0, 255 - i);
    // Linie 2: Von Mitte oben nach rechts, am Anfang gelb, am Ende rot
    sdlDrawLine(mitteX, mitteY - i, mitteX + i, mitteY, 255, 255 - i, 0);
    // Linie 3: Von Mitte unten nach links, am Anfang gelb, am Ende rot
    sdlDrawLine(mitteX, mitteY + i, mitteX - i, mitteY, 255, 255 - i, 0);
    // Linie 4: Von Mitte unten nach rechts, am Anfang lila, am Ende rot
    sdlDrawLine(mitteX, mitteY + i, mitteX + i, mitteY, 255, 0, 255 - i);
    // bei jedem Umlauf anzeigen, nicht erst am Schluss!
    sdlUpdate();
    // vor den nächsten Linien: 50 ms warten
    sdlMilliSleep(50);
  }

  // fertiges Bild 3 Sekunden anzeigen, dann wieder alles löschen
  sdlMilliSleep(3000);
  sdlSetBlack();   
  
  for (int i = 0; i <= (mitteY - 10) ; ++i) {
    // wir beginnen mit einer großen roten Ellipse in Bildmitte,
    // und zeichnen bei jedem Schleifendurchlauf
    // eine neue Ellipse auf die schon gezeichneten Ellipsen drauf.
    // Die neue Ellipse is genauso breit, immer weniger hoch,
    // und immer mehr gelb.
    sdlDrawCirc(mitteX, mitteY, mitteX - 10, mitteY - 10 - i, 255, i, 0);
    sdlUpdate();
    sdlMilliSleep(50);
  }

  sdlMilliSleep(3000);   // warte wieder 3 Sekunden
  sdlExit();             // mach das Grafikfenster wieder zu

  exit(EXIT_SUCCESS);
}
