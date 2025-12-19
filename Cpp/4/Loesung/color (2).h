// Geom. Objekte: Vererbung und "clone"
// Header für Klasse "Color"
// (.cpp-File für "Color" gibt es keinen,
// da es keinen Code außerhalb von "class" gibt)
//
// Klaus Kusche, 2020

#ifndef _COLOR_H
#define _COLOR_H

class Color
{
  public:
    Color(int r, int g, int b)  
    : mR(r), mG(g), mB(b)
    {}

    int getR() const { return mR; }
    int getG() const { return mG; }
    int getB() const { return mB; }

  private:   
    int mR, mG, mB;
};

#endif
