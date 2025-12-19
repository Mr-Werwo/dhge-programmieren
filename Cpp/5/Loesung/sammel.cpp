// C++: Inventarliste, mit zusammengesetztem Objekt
//
// Abgeleitete Klasse Sammel (Sammelobjekte), Implementierung
//
// Klaus Kusche, 2011

#include <iostream>
#include <iomanip>

using namespace std;

#include "sammel.h"

void Sammel::addItem(Inventar *item)
{
  if (mItemCnt == MAX_ITEMS) {
    cout << "Dieses Sammelobjekt enthält bereits die max. Anzahl von Gegenständen!" << endl;
  } else {
    mItem[mItemCnt++] = item;
  }
}

double Sammel::getValue()
{
  double sum = 0;
  for (int i = 0; i < mItemCnt; ++i) {
    sum += mItem[i]->getValue();
  }
  return sum;
}

void Sammel::setValue(double /*value*/)
{
  cout << "Der Wert eines zusammengesetzen Inventars kann nicht geändert werden!" << endl;
}

void Sammel::print()
{
  cout << setw(10) << getInvNr() << ": " << setw(30) << left << mName << right
      << ":" << setw(10) << getValue() << " Euro" << endl;
  cout << "Bestandteile Sammelobjekt:" << endl;
  for (int i = 0; i < mItemCnt; ++i) {
    mItem[i]->print();
  }
  cout << "Ende Bestandteile Sammelobjekt." << endl;
}
