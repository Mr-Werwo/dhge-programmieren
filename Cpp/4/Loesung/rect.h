// Geom. Objekte: Aufteilung auf Files, mehrere Objekte
// Header für Klasse "Rect"
//
// Klaus Kusche, 2020

#ifndef _RECT_H
#define _RECT_H

#include "color.h"
// sdlinterf.h brauchen wir nur in der Implementierung, nicht im Header

class Rect
{
  public:
    Rect(const Color &color, int x, int y, int w, int h,
          int sx = 0, int sy = 0)
    : mRGB(color), mX(x), mY(y), mW(w), mH(h), mSX(sx), mSY(sy)
    {
      draw();
    }
    ~Rect() { undraw(); }

    Color getColor() const { return mRGB; }
    int getX() const { return mX; }
    int getY() const { return mY; }
    int getW() const { return mW; }
    int getH() const { return mH; }
    int getSX() const { return mSX; }
    int getSY() const { return mSY; }

    void setColor(const Color &color)
    {
      mRGB = color;
      draw();
    }

    void setSpeed(int sx, int sy)
    {
      mSX = sx; mSY = sy;
    }
    
    void setPos(int x, int y);
    void move(int dx, int dy);
    void setSize(int w, int h);
    void scale(int percentX, int percentY);

    bool fly(bool bounce = false);

    void draw();
    void undraw();

  private:
    Color mRGB;
    int mX, mY;
    int mW, mH;
    int mSX, mSY;
};

#endif
