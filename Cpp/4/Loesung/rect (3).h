// Geom. Objekte: Zusammengesetzte Objekte
// Header für abgeleitete Klasse "Rect"
//
// Klaus Kusche, 2020

#ifndef _RECT_H
#define _RECT_H

#include "graobj.h"

class Rect : public GraObj
{
  public:
    Rect(const Color &color, int x, int y, int w, int h,
         int sx = 0, int sy = 0)
    : GraObj(color, x, y, w, h, sx, sy)  
    {
      draw();
    }
    Rect(const Rect &orig) : GraObj(orig)
    {
      draw();
    }

    Rect &operator=(const Rect &r) = delete;

    virtual ~Rect() { undraw(); }

    virtual Rect *clone() const override {
      return new Rect(*this);
    }
    
    virtual void draw() override;
    virtual void undraw() override;
};

#endif
