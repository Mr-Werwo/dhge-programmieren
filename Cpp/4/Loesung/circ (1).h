// Geom. Objekte: Zusammengesetzte Objekte
// Header für abgeleitete Klasse "Circ"
//
// Klaus Kusche, 2020

#ifndef _CIRC_H
#define _CIRC_H

#include "graobj.h"

class Circ : public GraObj
{
  public:
    Circ(const Color &color, int x, int y, int w, int h,
         int sx = 0, int sy = 0)
    : GraObj(color, x, y, w, h, sx, sy)  
    {
      draw();
    }
    Circ(const Circ &orig) : GraObj(orig)
    {
      draw();
    }

    // wir verbieten die normale Zuweisung von Objekten
    Circ &operator=(const Circ &r) = delete;

    virtual ~Circ() { undraw(); }

    virtual Circ *clone() const override {
      return new Circ(*this);
    }
    
    virtual void draw() override;
    virtual void undraw() override;
};

#endif
