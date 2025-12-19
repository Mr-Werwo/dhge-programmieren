// Geom. Objekte: Zusammengesetzte Objekte
// Hauptprogramm
//
// Aufruf: main
//
// Klaus Kusche, 2020

#include <cstdlib>
#include <ctime>

#include "sdlinterf.h"

#include "color.h"
#include "graobj.h"
#include "rect.h"
#include "circ.h"
#include "comp.h"

using namespace std;

const int objCnt = 10;  // Gesamtzahl der Objekte

// erzeuge ein Gesicht als zusammengesetzes Objekt 
Comp *makeFace(void);

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

  // die Array-Elemente müssen wahlweise auf Rect's oder Circ's zeigen können
  // ==> mit der gemeinsamen Basisklasse deklarieren
  GraObj *obj[objCnt];

  obj[0] = makeFace();
  for (int i = 1; i < objCnt; ++i) {
    obj[i] = obj[i - 1]->clone();
  }
  
  for (int i = 0; i < objCnt; ++i) {
    obj[i]->scale(rand() % 100 + 33, rand() % 100 + 33);
    obj[i]->setSpeed(randPM(7), randPM(7));
  }

  // Objekte endlos herumfliegen lassen
  for (;;) {
    sdlUpdate();
    sdlMilliSleep(20);
    for (int i = 0; i < objCnt; ++i) {
      obj[i]->fly(true);
    }
  }

  sdlExit();

  exit(EXIT_SUCCESS);
}

// Mittelpunkt des ursprünglichen zusammengesetzten Objektes
const int face_x = SDL_X_SIZE / 2;
const int face_y = SDL_Y_SIZE / 2;

const GraObj *parts[] = {
  new Circ(Color(255, 255, 0), face_x, face_y, 80, 100),
  new Circ(Color(200, 100, 0), face_x, face_y, 10, 30),
  new Circ(Color(0, 0, 0), face_x - 40, face_y - 20, 25, 25),
  new Circ(Color(0, 0, 0), face_x + 40, face_y - 20, 25, 25),
  new Circ(Color(255, 0, 255), face_x - 38, face_y - 16, 10, 15),
  new Circ(Color(255, 0, 255), face_x + 38, face_y - 16, 10, 15),
  new Circ(Color(255, 0, 0), face_x, face_y + 50, 40, 10),
  new Circ(Color(255, 200, 0), face_x - 90, face_y - 10, 10, 40),
  new Circ(Color(255, 200, 0), face_x + 90, face_y - 10, 10, 40)
};

const int partAnz = sizeof(parts) / sizeof(parts[0]);

Comp *makeFace(void)
{
  Comp *face = new Comp(face_x, face_y, 0, 0, partAnz);
  for (int i = 0; i < partAnz; ++i) {
    face->add(*parts[i]);
  }

  return face;
}
