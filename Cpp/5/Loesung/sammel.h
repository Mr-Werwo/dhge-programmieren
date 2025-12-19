// C++: Inventarliste, mit zusammengesetztem Objekt
//
// Abgeleitete Klasse Sammel (Sammelobjekte), Header
//
// Klaus Kusche, 2011

#ifndef _SAMMEL_H
#define _SAMMEL_H

// Max. Anzahl von Gegenständen,
// die zu einem Sammelobjekt zusammengefasst werden können
#define MAX_ITEMS 10

#include <string>

using namespace std;

#include "inventar.h"

class Sammel : public Inventar
{
  public:
    Sammel(string name) :
      Inventar(name), mItemCnt(0) {}
    Sammel(const Sammel &orig) :
      Inventar(orig), mItemCnt(orig.mItemCnt) {
        for (int i = 0; i < mItemCnt; ++i) {
          mItem[i] = orig.mItem[i]->clone();
        }
      }
    virtual ~Sammel() {
      for (int i = 0; i < mItemCnt; ++i) {
        delete mItem[i];
      }
    }

    void addItem(Inventar *item);

    virtual double getValue();
    virtual void setValue(double value);
    virtual void print();

    virtual Sammel* clone() const { return new Sammel(*this); }

    // Zuweisung muss implementiert oder verboten werden!
    Sammel &operator=(const Sammel &orig) = delete;

  protected:
    int mItemCnt;
    Inventar *mItem[MAX_ITEMS];
};

#endif
