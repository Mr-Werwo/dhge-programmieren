// Geom. Objekte: Aufteilung auf Files, mehrere Objekte
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

const int objCnt = 100;

// Zur Wahl einer zufälligen Geschwindigkeit, die nicht 0 ist:
// Berechne eine Zufallszahl z von -n ... -1 oder 1 ... n (aber nicht 0)
inline int randPM(int n)
{
  return ((rand() % n) + 1) - ((rand() % 2) * (n + 1));
}

int main(void)
{
  srand(time(nullptr));
  sdlInit();

  // wir können zwar kein Array von Rechtecken anlegen
  // (weil Rect keinen Standard-Konstruktor hat),
  // aber ein Array von Pointern auf Rechtecke ist ok
  // (weil da entstehen ja noch keine Rechtecke)
  Rect *obj[objCnt];
  for (int i = 0; i < objCnt; ++i) {
    obj[i] = new Rect(
      // jede Farb-Komponente mindesten 64,
      // damit keine ganz dunklen Rechtecke entstehen
      Color(rand() % 192 + 64, rand() % 192 + 64, rand() % 192 + 64),
      SDL_X_SIZE / 2, SDL_Y_SIZE / 2,        // Position: Bildmitte
      rand() % 30 + 1, rand() % 30 + 1,      // Größe: 1 ... 30
      // Geschwindigkeit: -10 ... 10 außer 0
      randPM(10), randPM(10));
  }

  // n zählt die noch existierenden Objekte, Schleife bis alle Objekte weg sind
  for (int n = objCnt; n > 0; ) {
    sdlMilliSleep(20);
    sdlUpdate();
    for (int i = 0; i < objCnt; ++i) {
      if (obj[i] != nullptr) {
        // Bei jedem Richtungswechsel: Schrumpfe das Rechteck um 10 %
        if (!obj[i]->fly(true)) {
          obj[i]->scale(90, 90);
          // Wenn das Rechteck Breite oder Höhe 0 hat:
          // Objekt vernichten, Anzahl existierender Objekte runterzählen
          if ((obj[i]->getW() == 0) || (obj[i]->getH() == 0)) {
            delete obj[i];
            obj[i] = nullptr;
            --n;
          }
        }
      }
    }
  } 

  sdlExit();

  exit(EXIT_SUCCESS);
}
