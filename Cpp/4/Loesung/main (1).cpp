// Geom. Objekte: Copy-Konstruktor, "moveOnTop"
// Hauptprogramm
//
// Aufruf: main
//
// Klaus Kusche, 2020

#include <cstdlib>
#include <ctime>

#include "sdlinterf.h"

#include "color.h"
#include "rect.h"

using namespace std;

const int objCnt = 40;

// Zur Positionierung eines Objektes:
// Berechne eine Zufallszahl z mit dist <= z <= (range - 1) - dist
// (range ... Breite bzw. Höhe des Fensters, dist ... Mindestabstand vom Rand)
inline int randPos(int range, int dist)
{
  return dist + rand() % (range - 2 * dist);
}

int main(void)
{
  srand(time(nullptr));
  sdlInit();

  Rect *obj[objCnt];

  /////////////////////////////////////////////////////////////////////////////
  // 1. Rechteck erzeugen
  obj[0] = new Rect(Color(255, 255, 0),
                    SDL_X_SIZE / 2, SDL_Y_SIZE / 2,
                    SDL_X_SIZE / 5, SDL_Y_SIZE / 5);
  sdlUpdate();
  sdlMilliSleep(100);
  
  /////////////////////////////////////////////////////////////////////////////
  // weitere Rechtecke als Kopie erzeugen und an eine zufällige Stelle legen
  for (int i = 1; i < objCnt; ++i) {
    // Ab 2. Rechteck: Kopie des vorigen Rechtecks erzeugen ...
    obj[i] = new Rect(*obj[i - 1]);
    // ... und an eine andere Stelle verschieben.
    // Das Wegschieben hinterlässt am ursprünglichen Platz ein Loch,
    // d.h. vom vorigen Rechteck, das kopiert wurde,
    // bleibt nur ein dünner Rahmen sichtbar
    obj[i]->setPos(randPos(SDL_X_SIZE, obj[i]->getW()),
                   randPos(SDL_Y_SIZE, obj[i]->getH()));
    sdlUpdate();
    sdlMilliSleep(100);
  }

  /////////////////////////////////////////////////////////////////////////////
  // Rechtecke in der linken Fensterhälfte übereinander legen,
  // letztes (kleinstes) unten, erstes (größtes) obenauf.
  obj[objCnt - 1]->setPos(SDL_X_SIZE / 4, SDL_Y_SIZE / 2);
  sdlUpdate();
  sdlMilliSleep(100);
  for (int i = objCnt - 2; i >= 0; --i) {
    obj[i]->moveOnTop(*obj[i + 1]);
    sdlUpdate();
    sdlMilliSleep(100);
  }

  /////////////////////////////////////////////////////////////////////////////
  // Rechtecke in der rechten Fensterhälfte übereinander legen,
  // erstes (größtes) unten, letztes (kleinstes) obenauf ...
  obj[0]->setPos(3 * SDL_X_SIZE / 4, SDL_Y_SIZE / 2);
  sdlUpdate();
  sdlMilliSleep(100);
  for (int i = 1; i < objCnt; ++i) {
    obj[i]->moveOnTop(*obj[i - 1]);
    sdlUpdate();
    sdlMilliSleep(100);
  }

  /////////////////////////////////////////////////////////////////////////////
  // Rechtecke von oben (kleinstes) nach unten (größtes) löschen.
  for (int i = objCnt - 1; i >= 0; --i) {
    delete obj[i];
    sdlUpdate();
    sdlMilliSleep(100);
  }

  sdlExit();

  exit(EXIT_SUCCESS);
}
