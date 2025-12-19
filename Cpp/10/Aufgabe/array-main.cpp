// Einfache Array-Klasse mit Operatoren (Angabe)
//
// Klaus Kusche, 2011

#include <iostream>

using namespace std;

class Array 
{
  // hier fehlt etwas
};

// hier fehlen die Methoden und eine Funktion

int main()
{
  Array a(5), b(2), c(10);

  a = 1.0;
  c = b = a;
  cout << "a == b: " << ((a == b) ? "gleich" : "ungleich") << endl;
  a.setVal(0, 10.0);
  b.setVal(1, 11.0);
  c.setVal(2, 12.0);
  a = a;
  cout << "a: " << a << ", b: " << b << ", c: " << c << endl;

  a = a + a;
  c = b + -a;
  b = b + 3.0;
  cout << "a: " << a << ", b: " << b << ", c: " << c << endl;
  cout << "a == b: " << ((a == b) ? "gleich" : "ungleich") << endl;

  Array kurz(2), lang(5), tmp(0);

  kurz = 9.9;
  lang = 9.9;
  cout << "kurz == lang: " << ((kurz == lang) ? "gleich" : "ungleich") << endl;
  kurz.setVal(0, 6.6);
  cout << "kurz + lang: " << kurz + lang << endl;
  cout << "lang + kurz: " << lang + kurz << endl;

  // auskommentieren, wenn += nicht implementiert ist!
  tmp = lang;
  tmp.setVal(1, 0.0);
  cout << "kurz: " << kurz << ", lang: " << lang << endl;
  lang += kurz;
  kurz += tmp;
  cout << "lang += kurz: " << lang << endl;
  cout << "kurz += tmp: " << kurz << endl;

  return 0;
}
