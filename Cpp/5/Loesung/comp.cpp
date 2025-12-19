// C++: Inventarliste
//
// Abgeleitete Klasse Comp (Computer), Implementierung
//
// Klaus Kusche, 2011

#include <iostream>
// siehe zubeh.cpp
#include <iomanip>

using namespace std;

#include "comp.h"

int Comp::MCompCount = 0;
int Comp::MTotalRamGB = 0;
int Comp::MTotalDiskGB = 0;

double Comp::MRamValPerGB = 5;
double Comp::MDiskValPerGB = 0.2;

void Comp::print()
{
  // auf mName der Basisklasse dürfen wir direkt zugreifen (protected),
  // auf die Inventarnummer nur mit get-Methode (private)
  // setw, left, right: siehe zubeh.cpp
  cout << setw(10) << getInvNr() << ": " << setw(30) << left << mName << right
       << ":" << setw(10) << getValue() << " Euro" << endl;
  cout << "           (Grundgerät " << mBaseValue << " Euro, "
       << mRamGB << " GB RAM, " << mDiskGB << " GB Disk)" << endl;
}
