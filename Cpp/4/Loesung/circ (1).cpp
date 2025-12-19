// Geom. Objekte: Zusammengesetzte Objekte
// Implementierung der abgeleiteten Klasse "Circ"
//
// Klaus Kusche, 2020

#include "circ.h"

#include "sdlinterf.h"

void Circ::draw()
{
  sdlDrawCirc(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Circ::undraw()
{
  sdlDrawCirc(mX, mY, mW, mH, 0, 0, 0);
}
