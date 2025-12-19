// Geom. Objekte: Zusammengesetzte Objekte
// Header für abstrakte Basisklasse "GraObj"
//
// Klaus Kusche, 2020

#ifndef _GRAOBJ_H
#define _GRAOBJ_H

#include "color.h"

class GraObj
{
  public:
    GraObj(const Color &color, int x, int y, int w, int h,
          int sx = 0, int sy = 0)
    : mRGB(color), mX(x), mY(y), mW(w), mH(h), mSX(sx), mSY(sy)
    { }
    // In diesem Beispiel reicht für GraObj der automatische Copy-Konstruktor:
    // - Die Kopie soll völlig ident zum Original sein
    // - Das "draw" passiert in der abgeleiteten Klasse

    // wir verbieten die normale Zuweisung von Objekten
    // (denn sonst müssten wir sie für zusammengesetze Objekte
    // recht aufwendig explizit implementieren)
    GraObj &operator=(const GraObj &r) = delete;

    virtual ~GraObj() { }

    virtual GraObj *clone() const = 0;

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

    // die folgenden Methoden werden in comp.cpp überschrieben
    // ==> virtuell machen!
    // (aber nicht rein virtuell,
    // denn sie behalten ja ihre "normale" Implementierung in GraObj)
    virtual void setPos(int x, int y);
    virtual void move(int dx, int dy);
    virtual void setSize(int w, int h);
    virtual void scale(int percentX, int percentY);

    bool fly(bool bounce = false);

    virtual void draw() = 0;
    virtual void undraw() = 0;
  
  protected:
    Color mRGB;
    int mX, mY;
    int mW, mH;
    int mSX, mSY;
};

#endif
