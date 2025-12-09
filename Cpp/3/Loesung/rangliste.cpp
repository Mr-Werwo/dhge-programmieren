// Übung zu den Unterschieden C / C++: Rangliste sortieren, ausgeben
//
// Aufruf: rangliste zeit1 zeit2 ...
//
// Klaus Kusche, 2011

// C++ I/O
#include <iostream>
// die C++-Versionen von stdlib.h und ctype.h
#include <cstdlib>
#include <cctype>

using namespace std;

struct Teilnehmer {
  int startnr;
  double zeit;
};

// Referenzen statt Pointer!
void tausche(Teilnehmer &a, Teilnehmer &b);

// Default-Wert erlaubt Aufruf mit nur 2 Parametern für Gesamt-Liste
void print(Teilnehmer liste[], int anzahl, int startnr = 0);

int main(int argc, const char *argv[])
{
  int anzahl = argc - 1;
  if (anzahl == 0) {
    // cerr entspricht stderr
    cerr << "Aufruf: " << argv[0] << " zeit1 zeit2 ..." << endl;
    exit(EXIT_FAILURE);
  }

  // "Mach ein neues Array mit anzahl vielen Elementen vom Typ Teilnehmer."
  Teilnehmer *liste = new Teilnehmer[anzahl];

  ///// Einlesen
  for (int i = 0; i < anzahl; ++i) {
    liste[i].startnr = i + 1;
    liste[i].zeit = atof(argv[i + 1]);
  }

  ///// Sortieren: Bubblesort optimiert
  // ("merk dir, wo die hinterste Vertauschung war,
  // und vergleiche im nächsten Durchgang nur bis dorthin")
  int grenze, letzter;
  for (grenze = anzahl - 1; grenze > 0; grenze = letzter) {
    letzter = 0;
    for (int i = 0; i < grenze; ++i) {
      if (liste[i].zeit > liste[i + 1].zeit) {
        // Kein & vor den Argumenten bei Referenz-Parametern!
        tausche(liste[i], liste[i + 1]);
        letzter = i;
      }
    }
  }

  ///// Ausgeben
  for (;;) {
    cout << "g ... Gesamtliste, s ... eine Startnummer? ";
    char auswahl;
    cin >> auswahl;
    if (tolower(auswahl) == 'g') {
      print(liste, anzahl);   // Aufruf mit 2 Parametern ==> Alle
    } else if (tolower(auswahl) == 's') {
      cout << "Startnummer? ";
      int nr;
      cin >> nr;
      print(liste, anzahl, nr); // Aufruf mit 3 Parametern ==> Ein bestimmter
    } else {
      break;
    }
  }
  
  delete [] liste;  // "Gib das Array, auf das "liste" zeigt, wieder frei."
  
  exit(EXIT_SUCCESS);
}

void tausche(Teilnehmer &a, Teilnehmer &b)
{
  Teilnehmer tmp;
  // Strukturen kann man (wie in C) als Ganzes zuweisen.
  tmp = a;
  a = b;
  b = tmp;
}

// Default-Parameter steht *nur* im Prototyp, nicht hier
void print(Teilnehmer liste[], int anzahl, int startnr)
{
  for (int i = 0; i < anzahl; ++i) {
    // Ungültige Startnummern-Eingaben werden stillschweigend ignoriert
    // (keine Ausgabe). Man könnte ev. noch eine Fehlermeldung ausgeben.
    if ((startnr == 0) || (liste[i].startnr == startnr)) {
      cout << "Platz " << i + 1 << ": Startnummer " << liste[i].startnr
           << ", Zeit " << liste[i].zeit << endl;
    }
  }
}
