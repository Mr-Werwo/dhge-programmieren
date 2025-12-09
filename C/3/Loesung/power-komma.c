// Potenz mit Komma-Zahl als Basis und ganzer Zahl als Exponent
//
// Aufruf: power basis expon
//
// Klaus Kusche, 2010/2011

#include <stdio.h>
// Für atoi und atof brauchen wir laut Angabe stdlib.h
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  // hat der Aufrufer überhaupt genau zwei Zahlen angegeben?
  // (damit argv[1] und argv[2] nicht "ins Leere greift")
  if (argc != 3) {
    // Wenn nein: Fehlermeldung ausgeben, mit Fehlercode aufhören
    fprintf(stderr, "Aufruf: %s basis expon\n", argv[0]);
    exit(EXIT_FAILURE);  // oder "return 1;" : bewirkt dasselbe
  }

  // argv[1] und argv[2] mittels atoi / atof von Text in Zahlen verwandeln
  // (den Text (einen "char *") steckt man in atoi / atof hinein,
  // die Zahl (ein "int" bzw. ein "double") kommt als Ergebnis zurück:
  // atoi ... "ascii to int", atof ... "ascii to float")
  // und in zwei dafür angelegten Variablen speichern
  double basis = atof(argv[1]);  // Kommazahl!
  int expon = atoi(argv[2]);

  // "Irgendetwas hoch negative Zahl" mit Kommazahlen ist dasselbe wie
  // "Kehrwert von irgendetwas hoch entsprechender positiver Zahl"
  if (expon < 0) {
    // hier sollte man eigentlich zuerst prüfen, ob a == 0 ist!
    // aber bei double wird bei 1/0 einfach mit "infinity" weitergerechnet,
    // was für uns vorerst einmal eine akzeptable Lösung ist.
    basis = 1 / basis;
    expon = -expon;
  }
  // ab hier gilt immer expon >= 0, beide Fälle werden gleich berechnet

  // Wir brauchen eine Variable für das Ergebnis (auch Kommazahl!)
  // im Ergebnis speichern wir als Anfangswert einmal 1,
  // damit wir weiter unten etwas dazumultiplizieren können
  double ergeb = 1;

  // und dann kommt eine Schleife,
  // die von 1 bis zur zweiten Eingabe expon (einschließlich) zählt
  for (int i = 1; i <= expon; ++i) {
    // in der Schleife multiplizieren wir jedesmal
    // die erste Eingabe zum Ergebnis dazu
    // und speichern das wieder im Ergebnis
    ergeb = ergeb * basis;
  }

  // nach der Schleife kommt noch die Ausgabe ...
  // wir müssen die Original-Texte aus der Eingabezeile ausgeben,
  // da basis und expon ja bei negativem expon geändert wurden
  printf("%s hoch %s = %g\n", argv[1], argv[2], ergeb);

  // ... und das Programm-Ende
  exit(EXIT_SUCCESS);  // oder "return 0;" : bewirkt dasselbe
}
