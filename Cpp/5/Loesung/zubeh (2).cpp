// C++: Inventarliste, mit zusammengesetztem Objekt
//
// Abgeleitete Klasse Zubeh (Zubehör), Implementierung
//
// Klaus Kusche, 2011

#include <iostream>
// iomanip enthält die Funktionen zur schönen Formatierung der Ausgabe
#include <iomanip>

using namespace std;

#include "zubeh.h"

void Zubeh::print()
{
  // auf mName der Basisklasse dürfen wir direkt zugreifen (protected),
  // auf die Inventarnummer nur mit get-Methode (private)
  // setw(n) ... setze die Spaltenbreite der nächsten Ausgabe auf n
  // left ... gib die folgenden Werte linksbündig in der Spalte aus
  // right ... stell wieder zurück auf rechtsbündige Ausgabe
  cout << setw(10) << getInvNr() << ": " << setw(30) << left << mName << right
      << ":" << setw(10) << mValue << " Euro" << endl;
}
