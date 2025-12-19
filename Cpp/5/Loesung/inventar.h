// C++: Inventarliste
//
// Basisklasse Inventar, Header
//
// Klaus Kusche, 2011

#ifndef _INVENTAR_H
#define _INVENTAR_H

#include <string>

using namespace std;

class Inventar
{
  public:
    Inventar(string name) :
      // im Initialwert einer Init-Liste darf man nicht nur auf Argumente zugreifen
      // sondern auch mit statischen Membern rechnen
      mName(name), mInvNr(++MLastInvNr) {}
    virtual ~Inventar() {}

    string getName() { return mName; }
    int getInvNr() { return mInvNr; }

    virtual double getValue() = 0;
    virtual void setValue(double value) = 0;
    virtual bool isComp() = 0;
    
    virtual void print() = 0;
  
  protected:
    string mName;
    
  private:
    int mInvNr;
    static int MLastInvNr;
};

#endif
