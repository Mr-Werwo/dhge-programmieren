// Kleines Grafik-Demo-Beispiel: Zufällige Sterne
//
// Aufruf: weihn-schnee
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  srand(time(NULL));

  sdlInit();
  sdlSetBlack();

  for (int r = 10; r <= 100; ++r) {  // r = Radius (Armlänge) des Sterns
    // wir müssen auf jeder Seite r Sicherheitsabstand vom Rand haben,
    // daher haben wir nur "Gesamtgröße - 2*r" Spielraum für den Mittelpunkt
    // bzw. müssen eine Zufallszahl zwischen r und Rand-1-r erzeugen
    int x = rand() % (SDL_X_SIZE - 2 * r) + r;
    int y = rand() % (SDL_Y_SIZE - 2 * r) + r;
    sdlDrawCirc(x, y, r, r / 10, r, r, 2 * r + 55);
    sdlDrawCirc(x, y, r / 10, r, r, r, 2 * r + 55);
    // bei jedem Umlauf anzeigen, nicht erst am Schluss!
    sdlUpdate();
    // vor dem nächsten Stern: 50 ms warten
    sdlMilliSleep(50);
  }

  sdlMilliSleep(3000);
  sdlExit();

  exit(EXIT_SUCCESS);
}
