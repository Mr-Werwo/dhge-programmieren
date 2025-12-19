// C++: Inventarliste, mit zusammengesetztem Objekt
//
// Abgeleitete Klasse Zubeh (Zubehör), Header
//
// Klaus Kusche, 2011

#ifndef _ZUBEH_H
#define _ZUBEH_H

#include <string>

using namespace std;

#include "inventar.h"

class Zubeh : public Inventar
{
  public:
    Zubeh(string name, double value) :
      Inventar(name), mValue(value) {}
    Zubeh(const Zubeh &orig) :
      Inventar(orig), mValue(orig.mValue) {}
    virtual ~Zubeh() {}

    virtual double getValue() { return mValue; }
    virtual void setValue(double value) { mValue = value; }
    virtual void print();

    virtual Zubeh* clone() const { return new Zubeh(*this); }

  protected:
    double mValue;    
};

#endif
