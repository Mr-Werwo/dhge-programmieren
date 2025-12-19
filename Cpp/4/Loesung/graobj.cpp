// Geom. Objekte: Vererbung und "clone"
// Implementierung der abstrakten Basisklasse "GraObj"
//
// Klaus Kusche, 2020

#include "graobj.h"

// wir brauchen zwar keine Zeichen-Funktionen mehr
// aber trotzdem SDL_X_SIZE und SDL_Y_SIZE für den Rand-Test in "fly"
#include "sdlinterf.h"

void GraObj::setPos(int x, int y)
{
  undraw();
  mX = x;
  mY = y;
  draw();
}

void GraObj::move(int dx, int dy)
{
  undraw();
  mX += dx;
  mY += dy;
  draw();
}

void GraObj::setSize(int w, int h)
{
  undraw();
  mW = w;
  mH = h;
  draw();
}

void GraObj::scale(int percentX, int percentY)
{
  undraw();
  mW = (mW * percentX) / 100;
  mH = (mH * percentY) / 100;
  draw();
}
  
bool GraObj::fly(bool bounce)
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

// nur zum Testen
//void GraObj::draw()
//{
//  // Nur Mittelpunkt statt Objekt zeichnen
//  sdlDrawPoint(mX, mY, mRGB.getR(), mRGB.getG(), mRGB.getB());
//}

//void GraObj::undraw()
//{
//  sdlDrawPoint(mX, mY, 0, 0, 0);
//}
