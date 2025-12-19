// Ganz einfacher Taschenrechner mit Bruch-Klasse:
// + - * / von links nach rechts ohne Vorrang und ohne Klammern
// (mit x statt *)
//
// Aufruf: bruch bruch1 op1 bruch2 op2 bruch3 ...
// (ein Bruch / ein Rechenzeichen pro Wort, d.h. mit Zwischenräumen)
//
// Klaus Kusche, 2012

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Bruch
{
  friend ostream &operator<<(ostream &outFile, const Bruch &a);

  public:
    // 3 Aufrufsmöglichkeiten:
    // Standardkonstruktor: Bruch() liefert 0/1, also 0
    // Für eine ganze Zahl: Bruch(z) liefert z/1, also z
    // Für einen Bruch: Bruch(z, n) liefert z/n
    Bruch(int zaehler = 0, int nenner = 1) : z(zaehler), n(nenner) {
      Kuerze();  // kürze den soeben gespeicherten Zähler und Nenner
    }

    // Konstruktor für Bruch aus einem String
    Bruch(const char *str);

    Bruch operator+(const Bruch &r) const {
      // Ganz lange Variante:
      //Bruch ergeb;
      //ergeb.z = z * r.n + r.z * n;
      //ergeb.n = n * r.n;
      //return ergeb;
      //
      // Variante mit Konstruktor:
      //Bruch ergeb(z * r.n + r.z * n, n * r.n);
      //return ergeb;
      //
      // Variante mit Konstruktor für temporäres (namenloses) Objekt
      return Bruch(z * r.n + r.z * n, n * r.n);
    }
    
    Bruch operator-(const Bruch &r) const {
      return Bruch(z * r.n - r.z * n, n * r.n);
    }
    
    Bruch operator*(const Bruch &r) const {
      return Bruch(z * r.z, n * r.n);
    }
    
    Bruch operator/(const Bruch &r) const {
      return Bruch(z * r.n, n * r.z);
    }

    // Typumwandlungs-Operator
    // Kein Returntyp:
    // Operator-Name = Returntyp = Typ, auf den umgewandelt wird
    operator double() const {
      return double(z) / double(n);
    }
    
  private:
    int z;
    int n;

    // Liefert keinen neuen Bruch als Ergebnis,
    // sondern kürzt das Bruch-Objekt, für das "Kuerze" aufgerufen wird
    void Kuerze();  
};

Bruch::Bruch(const char *str)
{
  z = atoi(str);       // Zahl bis vor dem '/'
  const char *p = strchr(str, '/');
  if (p == nullptr) {  // kein '/' ?
    n = 1;
  } else {
    n = atoi(p + 1);   // Zahl ab 1 Zeichen hinter dem '/'
    Kuerze();          // kürze den soeben gespeicherten Zähler und Nenner
  }
}

int ggT(int a, int b);

void Bruch::Kuerze()
{
  if (n == 0) {
    cerr << "Nenner ist 0!" << endl;
    exit(EXIT_FAILURE);
  }
  
  if (n < 0) {
    // Nenner negativ ==> Vorzeichen in Zähler und Nenner umdrehen
    // ("Minus nach oben bringen")
    z = -z;
    n = -n;
  }

  int g = ggT(z, n);
  z /= g;
  n /= g;
}

int ggT(int a, int b)
{
  // ggt wird von den Zahlen ohne Vorzeichen gerechnet!
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  
  while (b > 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  
  return a;
}

ostream &operator<<(ostream &outFile, const Bruch &a)
{
  if (a.n == 1) {
    outFile << a.z;
  } else {
    outFile << a.z << '/' << a.n;
  }
  
  return outFile;
}

int main(int argc, const char *argv[])
{
  // 1, 3, 5, ... Eingabeworte (+1 für den Programmnamen) sind ok
  // ==> argc muss gerade sein
  if (argc % 2 != 0) {
    cerr << argv[0] << ": Falsche Anzahl von Eingaben!\n" << endl;
    exit(EXIT_FAILURE);
  }

  // Bisheriges Ergebnis = linker Operand für die nächste Rechnung
  // Am Anfang: Erster Bruch
  Bruch result(argv[1]);
  // "Bruch result = argv[1];" geht genauso, ruft denselben Konstruktor auf

  // Schleife in Zweierschritten ab dem ersten Rechenzeichen
  // argv[i] ist das Rechenzeichen, argv[i + 1] ist der nächste Bruch
  for (int i = 2; i < argc; i += 2) { 
    // nächster Bruch (nach dem Rechenzeichen) = rechter Operand
    Bruch input(argv[i + 1]);
    // Rechenzeichen dazwischen anschauen: 1. Zeichen von i-tem Eingabe-Wort
    // switch geht nur mit einzelnen Zeichen, nicht mit ganzen Texten!
    switch (argv[i][0]) {
      case '+':
        // wir haben nur + usw. definiert, nicht += usw.
        // daher müssen wir result += input auf result = result + input ändern.
        result = result + input;
        break;
      case '-':
        result = result - input;
        break;
      case 'x':
         result = result * input;
        break;
      case '/':
        // Division durch 0 wird beim Kürzen des Ergebnisses erkannt,
        // muss hier nicht extra geprüft werden
        result = result / input;
        break;
      default:
        cerr << argv[0] << ": " << argv[i][0] << "Kein Rechenzeichen?" << endl;
        exit(EXIT_FAILURE);
    }
  }

  cout << "Ergebnis: " << result << endl;
  // Aufruf des Typumwandlungs-Operators,
  // ... << ((double) result) << ... ginge genauso
  cout << "Als Kommazahl: " << double(result) << endl;
  
  exit(EXIT_SUCCESS);
}
