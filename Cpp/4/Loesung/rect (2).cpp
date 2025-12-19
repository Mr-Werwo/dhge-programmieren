// Geom. Objekte: Copy-Konstruktor, "moveOnTop"
// Implementierung der Klasse "Rect"
//
// Klaus Kusche, 2020

// für max(a, b)
#include <algorithm>

using namespace std;

#include "sdlinterf.h"

#include "rect.h"

// Copy-Konstruktor, Implementierung
Rect::Rect(const Rect &orig)
  // Normalerweise: Initialisiere die eigenen Member
  // mit den entsprechenden Membern des Originals orig (unverändert)
  // Hier: Verändere sie dabei etwas (kleiner und dunkler)
  // Prüfe dabei, dass die Farbe und Größe nicht <0 bzw. <1 wird
  // Alternative zu ?: wäre max(...), entweder selbstgebaut oder aus <algorithm>
  : mRGB(max(0, orig.mRGB.getR() - 5),
         max(0, orig.mRGB.getG() - 5),
         max(0, orig.mRGB.getB() - 5)),
  mX(orig.mX), mY(orig.mY),
  mW(max(1, orig.mW - 3)), mH(max(1, orig.mH - 3)),
  mSX(orig.mSX), mSY(orig.mSY)
{
  draw();  // wie beim normalen Konstruktor: Objekt gleich zeichnen
}

void Rect::setPos(int x, int y)
{
  undraw();
  mX = x;
  mY = y;
  draw();
}

void Rect::move(int dx, int dy)
{
  undraw();
  mX += dx;
  mY += dy;
  draw();
}

void Rect::setSize(int w, int h)
{
  undraw();
  mW = w;
  mH = h;
  draw();
}

void Rect::scale(int percentX, int percentY)
{
  undraw();
  mW = (mW * percentX) / 100;
  mH = (mH * percentY) / 100;
  draw();
}
  
bool Rect::fly(bool bounce)
{
  bool ret = true;
  if (((mSX > 0) && (mX >= SDL_X_SIZE - mSX - mW)) ||
      ((mSX < 0) && (mX < -mSX + mW))) {
    if (bounce) {
      mSX = -mSX;
      ret = false;
    }
    else {
      return false;
    }
  }
  if (((mSY > 0) && (mY >= SDL_Y_SIZE - mSY - mH)) ||
      ((mSY < 0) && (mY < -mSY + mH))) {
    if (bounce) {
      mSY = -mSY;
      ret = false;
    }
    else {
      return false;
    }
  }

  move(mSX, mSY);
  return ret;
}

void Rect::moveOnTop(const Rect &r)
//void Rect::moveOnTop(const Rect r)
{
  undraw();
  mX = r.mX;
  mY = r.mY;
  draw();
// Übergibt man das Rechteck r als Referenz, funktioniert alles.
//
// Übergibt man das Rechteck r by Value, wird eine lokale Kopie gemacht.
// Die lokale Kopie wird an dieser Stelle wieder vernichtet.
// (nach dem "draw();", vor dem Return zum Aufrufer).
// Dabei wird der Destruktor und damit ein "undraw" aufgerufen
// ==> Über das Original und das frisch gezeichnete darübergelegte Rechteck
// wird ein störendes schwarzes Rechteck in der Größe des Originals gezeichnet!
}

void Rect::draw()
{
  sdlDrawRect(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw()
{
  sdlDrawRect(mX, mY, mW, mH, 0, 0, 0);
}
