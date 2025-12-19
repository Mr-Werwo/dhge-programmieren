// Geom. Objekte: Vererbung und "clone"
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
    {
      // das "draw" muss in der abgeleiteten Klasse sein!
    }
    // In diesem Beispiel reicht für GraObj der automatische Copy-Konstruktor:
    // - Die Kopie soll völlig ident zum Original sein
    // - Das "draw" passiert in der abgeleiteten Klasse

    // Destruktor:
    // - Das "undraw" muss in der abgeleiteten Klasse sein
    //   Hier: Leerer Code, nicht kein Code!
    // - Virtuell machen, damit der Destruktor der abgeleiteten Klasse
    //   auch ausgeführt wird
    virtual ~GraObj() { }

    // clone liefert einen Pointer auf eine dynamisch angelegte Kopie
    // des Objektes, für das clone aufgerufen wird
    // in der abstrakten Basisklasse sollte clone nie ausgeführt werden
    // (da es keine Objekte einer abstrakten Klasse gibt)
    // ==> rein virtuell machen
    // ==> muss in jeder abgeleiteten Klasse
    //   mit der "richtigen" Kopie (Kreis oder Rechteck) überschrieben werden
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
    
    void setPos(int x, int y);
    void move(int dx, int dy);
    void setSize(int w, int h);
    void scale(int percentX, int percentY);

    bool fly(bool bounce = false);


    // ein GraObj kann man nicht zeichnen, nur ein Rect oder Circ
    // ==> rein virtuell machen
    // ==> muss in jeder abgeleiteten Klasse
    //   mit dem "richtigen" Zeichen (Kreis oder Rechteck) überschrieben werden
    virtual void draw() = 0;
    virtual void undraw() = 0;

    // nur zum Testen: Als "zeichne Mittelpunkt" implementiert
    // void draw();
    // void undraw();
  
  protected:
    Color mRGB;
    int mX, mY;
    int mW, mH;
    int mSX, mSY;
};

#endif
