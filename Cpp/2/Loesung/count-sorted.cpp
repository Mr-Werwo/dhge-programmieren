// Zahlen auf der Befehlszeile zählen, in aufsteigender Reihenfolge
// (Find-Funktion mit Struct-Ref-Return)
//
// Aufruf: count-sorted n1 n2 n3 ...
//
// Klaus Kusche, 2012

#include <iostream>
#include <cstdlib>

using namespace std;

const int MAX_ELEMS = 100;

struct element {
  int wert;
  int anzahl;
};

struct daten {
  int elemente;
  element elem[MAX_ELEMS];
};

element &suche(daten &d, int w);
void drucke(const daten &d);

int main(int argc, const char *argv[])
{
  daten d;

  d.elemente = 0;
  
  for (int i = 1; i < argc; ++i) {
    // Einen Referenz-Returnwert kann man wie eine Variable behandeln:
    // Member mit . auswählen, darauf zuweisen, mit >> einlesen, inkrementieren, ...
    ++(suche(d, atoi(argv[i])).anzahl);
  }

  drucke(d);
  
  exit(EXIT_SUCCESS);
}

// Achtung auf das & im Returntyp!
element &suche(daten &d, int w)
{
  int i;
  
  for (i = 0; i < d.elemente; ++i) {
    if (d.elem[i].wert == w) {
      // Wert gefunden: Returniere das betreffende Element als Referenz
      return d.elem[i];
    }
    if (d.elem[i].wert > w) {
      // Wenn der aktuelle Wert schon größer ist als der Gesuchte,
      // brauchen wir nicht mehr weitersuchen: Nicht gefunden...
      break;
    }
  }

  // Alle Werte geprüft, nicht gefunden: Neues Element anhängen oder einfügen
  if (d.elemente == MAX_ELEMS) {
    cerr << "Zu viele Werte (max. " << MAX_ELEMS << ")!" << endl;
    exit(EXIT_FAILURE);
  }  

  // Wir müssen den neuen Wert an Stelle i speichern.
  // i kann das erste unbenutzte Element hinten sein,
  // oder der Index des ersten größeren bestehenden Elementes,
  // statt dem wir unseren Wert speichern müssen.
  // ==> Von hinten nach vorne bis zur Stelle i:
  // Schiebe die bestehenden Elemente eins nach hinten.
  // Andersrum ausgedrückt: Lass ein Loch (unbenutztes Element)
  // von ganz hinten bis an Stelle i nach vorne wandern.
  for (int j = d.elemente; j > i; --j) {
    d.elem[j] = d.elem[j - 1];
  }
  d.elem[i].wert = w;
  d.elem[i].anzahl = 0;
  ++d.elemente;
  return d.elem[i];
}

void drucke(const daten &d)
{
  for (int i = 0; i < d.elemente; ++i) {
    cout << "Wert " << d.elem[i].wert << ": " << d.elem[i].anzahl << " Stück" << endl;
  }
}
