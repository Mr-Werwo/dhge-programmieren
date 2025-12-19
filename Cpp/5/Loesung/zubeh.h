// C++: Inventarliste
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
    virtual ~Zubeh() {}

    virtual double getValue() { return mValue; }
    virtual void setValue(double value) { mValue = value; }
    virtual bool isComp() { return false; }
    
    virtual void print();

  protected:
    double mValue;    
};

#endif
