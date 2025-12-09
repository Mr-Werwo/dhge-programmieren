// Zahlen auf der Befehlszeile zählen
// (Find-Funktion mit Struct-Ref-Return)
// Variante unter Verwendung des map-Templates
//
// Aufruf: count n1 n2 n3 ...
//
// Klaus Kusche, 2014

#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

// Die einzelnen Elemente einer map sind immer vom vordefinierten Typ pair
// Ein pair hat die Member first und second
// Bei uns ist first die zu zählende Zahl und second der Zähler dazu
// Für den Typ des ersten Wertes braucht er in diesem Beispiel das const,
// weil der erste Wert im Paar ist der Sortierschlüssel, und den darf man
// nach dem Einfügen eines Knotens in den Baum nicht mehr ändern
typedef pair<const int, int> element;

// Eine map ist eine Ansammlung von pair-Werten,
// die schnell nach dem ersten Wert im Paar suchen kann
// und sortiert nach dem ersten Wert im Paar durchlaufen werden kann
// (intern ein Baum sortiert nach dem ersten Wert der Paare)
typedef map<const int, int> daten;

element &suche(daten &d, int w);
void drucke(const daten &d);

int main(int argc, const char *argv[])
{
  daten d;

  for (int i = 1; i < argc; ++i) {
    // Einen Referenz-Returnwert kann man wie eine Variable behandeln:
    // Member mit . auswählen, darauf zuweisen, mit >> einlesen, inkrementieren, ...
    ++(suche(d, atoi(argv[i])).second);
  }

  drucke(d);
  
  exit(EXIT_SUCCESS);
}

// Achtung auf das & im Returntyp!
element &suche(daten &d, int w)
{
  // Die insert-Methode liefert als Returnwert ein Paar,
  // aber kein pair<int, int> aus unserer Map,
  // sondern ein pair<daten::iterator, bool> :
  // * Der erste Wert .first des Paares ist ein Iterator,
  //   der auf das neu eingefügte Element zeigt,
  //   oder auf das schon bestehende Element,
  //   wenn es schon ein Paar mit demselben ersten Wert in der Map gibt
  // * Der zweite Wert des Paares ist ein bool, der den Erfolg anzeigt
  //   true  ... neues Element eingefügt
  //   false ... den Wert gibt's schon
  //
  // Man braucht also nicht zuerst suchen und wenn nicht gefunden einfügen,
  // denn insert macht beides in einem
  // und liefert in beiden Fällen einen Iterator auf das richtige Element
  // Mit * bekommt man das Element, auf das der Iterator zeigt
  return *(d.insert(element(w, 0)).first);
}

void drucke(const daten &d)
{
  // Variante für "altes" C++
  // Schleife mit Iterator als Schleifenvariable
  //for (daten::iterator i = d.begin(); i != d.end(); ++i) {
  //  cout << "Wert " << i->first << ": " << i->second << " Stück" << endl;
  //}

  // Erste C++ 11 Verbesserung: "auto"-Typ für den Iterator
  //for (auto i = d.begin(); i != d.end(); ++i) {
  //  cout << "Wert " << i->first << ": " << i->second << " Stück" << endl;
  //}

  // Zweite C++ 11 Verbesserung: "for :"-Schleife
  // In i wird der Reihe nach eine Referenz (kein Pointer oder Iterator!)
  // auf jedes Element in der Map gespeichert
  for (auto &i : d) {
    cout << "Wert " << i.first << ": " << i.second << " Stück" << endl;
  }  
}
