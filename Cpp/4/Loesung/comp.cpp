// Geom. Objekte: Zusammengesetzte Objekte
// Implementierung der abgeleiteten Klasse "Comp" für zusammenges. Objekte
//
// Klaus Kusche, 2020

#include "comp.h"

// wir brauchen abs(n) aus stdlib.h
#include <cstdlib>

using namespace std;

// Copy-Konstruktor
Comp::Comp(const Comp &orig) 
  : GraObj(orig),  // Basisklassen-Copy-Konstruktor aufrufen
    mObjCnt(orig.mObjCnt), mMaxObjCnt(orig.mMaxObjCnt), // gleiche Zählerstände 
    mObjArr(new GraObj *[mMaxObjCnt])  // ... aber neues Array!!!
{
  // Neues Array mit Kopien der Subobjekte des Originals befüllen
  // (clone ruft den Copy-Konstruktor auf, der zeichnet die neuen Subobjekte)
  for (int i = 0; i < mObjCnt; ++i) {
    mObjArr[i] = orig.mObjArr[i]->clone();
  }
}

Comp::~Comp()
{
  // zuerst die Subobjekte und erst dann das Pointer-Array löschen!
  for (int i = 0; i < mObjCnt; ++i) {
    delete mObjArr[i];
  }
  delete [] mObjArr;
}

bool Comp::add(const GraObj &obj)
{
  if (mObjCnt >= mMaxObjCnt) {  // Array voll
    return false;
  }
  mObjArr[mObjCnt] = obj.clone();  // Kopie des Original-Objektes speichern
  ++mObjCnt;
  recalcSize();  // Größe des eigenen Objektes könnte sich geändert haben
  return true;
}

void Comp::setPos(int x, int y)
{
  // wie viel verschiebt sich das Objekt?
  move(x - mX, y - mY);
}

void Comp::move(int dx, int dy)
{
  // neue Pos im Haupt-Objekt speichern
  mX += dx;
  mY += dy;
  // ... und alle Sub-Objekte verschieben
  for (int i = 0; i < mObjCnt; ++i) {
    mObjArr[i]->move(dx, dy);
  }
  // die Größen bleiben gleich ==> kein recalcSize nötig
  // nochmals alles neu zeichnen, sonst gibt es "Verschiebe-Lücken"
  draw();
}

void Comp::setSize(int w, int h)
{
  // wir führen setSize auf scale zurück,
  // dann müssen wir nur eines der beiden schreiben
  // Nachteil: Durch Rundungsfehler hat das Ergebnis
  // eventuell nicht genau die gewünschte Größe
  // Wieder wichtig wegen abschneidender Division: Zuerst *, dann /
  scale ((100 * w) / mW, (100 * h) / mH);
}

void Comp::scale(int percentX, int percentY)
{
  for (int i = 0; i < mObjCnt; ++i) {
    mObjArr[i]->scale(percentX, percentY);
    // Abstand des Subobjektes vom eigenen Mittelpunkt
    // muss auch skaliert werden!
    int dX = ((mObjArr[i]->getX() - mX) * percentX) / 100;
    int dY = ((mObjArr[i]->getY() - mY) * percentY) / 100;
    // verschiebe das Subobjekt an die neue Stelle
    mObjArr[i]->setPos(mX + dX, mY + dY);
  }
  recalcSize();
  // nochmals alles neu zeichnen, sonst gibt es "Verschiebe-Lücken"
  draw();
}

void Comp::draw()
{
  for (int i = 0; i < mObjCnt; ++i) {
    mObjArr[i]->draw();
  }
}

void Comp::undraw()
{
  for (int i = 0; i < mObjCnt; ++i) {
    mObjArr[i]->undraw();
  }
}

void Comp::recalcSize()
{
  // berechne das Maximum der Ausdehnungen der Subobjekte
  // gemessen vom Mittelpunkt der Hauptobjekte
  int wMax = 0, hMax = 0;
  for (int i = 0; i < mObjCnt; ++i) {
    // Ausdehnung = Ausdehnung des Subobjektes + sein Abstand vom Mittelpunkt
    int w = mObjArr[i]->getW() + abs(mObjArr[i]->getX() - mX);
    if (w > wMax) {
      wMax = w;
    }
    int h = mObjArr[i]->getH() + abs(mObjArr[i]->getY() - mY);
    if (h > hMax) {
      hMax = h;
    }
  }
  mW = wMax; mH = hMax;
}
