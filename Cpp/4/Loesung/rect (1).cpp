// Geom. Objekte: Aufteilung auf Files, mehrere Objekte
// Implementierung der Klasse "Rect"
//
// Klaus Kusche, 2020

#include "sdlinterf.h"

// Der .cpp-File einer Klasse inkludiert immer seinen eigenen .h-File
#include "rect.h"
// Wir verwenden auch Dinge aus color.h, aber rect.h inkludiert color.h schon

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

void Rect::draw()
{
  sdlDrawRect(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw()
{
  sdlDrawRect(mX, mY, mW, mH, 0, 0, 0);
}
