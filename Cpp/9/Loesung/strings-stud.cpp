// String-Klasse
//
// Aufruf: strings
//
// Klaus Kusche, 2012

#include <iostream>
#include <cstring>

// neu
#include <string>

using namespace std;

class String
{
  friend ostream &operator<<(ostream &outFile, const String &a);

  public:
    String(unsigned int size = 0) : txt(new char[size + 1]) {
      txt[0] = '\0';
    }

    String(const String &orig) : txt(new char[strlen(orig.txt) + 1]) {
      strcpy(txt, orig.txt);
    }
// alternativ mit strdup: Unsauber, offiziell undefiniert!
// 1.) strdup macht malloc, kein new, und wir geben das dann mit delete frei,
//     aber malloc & delete oder new & free ist offiziell undefiniert!
// 2.) new wirft bei Speichermangel eine Exception,
//     aber strdup returniert bei Speichermangel NULL (ohne Exception),
//     und wir müssten auf NULL prüfen!
//    String(const String &orig) : txt(strdup(orig.txt)) {}

    String(const char *str) : txt(new char[strlen(str) + 1]) {
      strcpy(txt, str);
    }
// alternativ mit strdup: Unsauber, offiziell undefiniert!
//    String(const char *str) : txt(strdup(str)) {}
    
    ~String() {
      delete [] txt;
    }
    
    String operator+(const String &b) const;
    bool operator==(const String &b) const;
    bool operator<(const String &b) const;
    bool operator!() const;
    String &operator=(const String &b);
    String &operator+=(const String &b);

    // neu
    char &operator[](int i);
    operator string() const;
    
  private:
    char *txt;
};

String String::operator+(const String &b) const
{
  String result(strlen(txt) + strlen(b.txt));
  strcpy(result.txt, txt);
  strcat(result.txt, b.txt);
  return result;
}

bool String::operator==(const String &b) const
{
  return (strcmp(txt, b.txt) == 0);
}

bool String::operator<(const String &b) const
{
  return (strcmp(txt, b.txt) < 0);
}

bool String::operator!() const
{
  return (txt[0] == '\0');
}

String &String::operator=(const String &b)
{
  if (this != &b) {
    delete [] txt;
    txt = new char[strlen(b.txt) + 1];
    strcpy(txt, b.txt);
// alternativ mit strdup: Unsauber, offiziell undefiniert!
//    txt = strdup(b.txt);  
  }
  return *this;
}

String &String::operator+=(const String &b)
{
  char *newtxt = new char[strlen(txt) + strlen(b.txt) + 1];
  strcpy(newtxt, txt);
  strcat(newtxt, b.txt);
  delete [] txt;
  txt = newtxt;
  return *this;
}

// neu
char &String::operator[](int i)
{
  static char dummy;  // static ist ganz wichtig, damit die Referenz
                      // nach dem return nicht ins Leere zeigt!
  if ((i < 0) || (i >= strlen(txt))) {
    dummy = '\0';
    return dummy;
  }
  return txt[i];
}

// neu
String::operator string() const
{
  return string(txt);
}

ostream &operator<<(ostream &outFile, const String &a)
{
  outFile << a.txt;
  return outFile;
}

int main()
{
  String nix;
  String a = "Äpfel";
  String aa = a;
  String b = "Birnen";
  String bb;
  String k = "Kompott";
  String ab = "ÄpfelBirnen";
  String res;

  bb = b;
  res = aa + String("") + bb;

  cout << "Ist 'nix' leer? " << (!nix ? "Ja!" : "Nein???") << endl;
  cout << "'" << bb << "' sind " << (!bb ? "auch" : "nicht") << " leer." << endl;
  cout << "'" << a << "' und '" << b << "' sind " <<
      ((a == b) ? "gleich" : "verschieden") << "." << endl;
  cout << "'" << bb << "' sind " << (bb < k ? "kleiner" : "größer") <<
      " als '" << k << "'" << endl;
  cout << "'" << k << "' ist " << (k < b ? "kleiner" : "größer") <<
      " als '" << b << "'" << endl;
  cout << "'" << aa << "' plus '" << bb << "' sind '" << res << "'." << endl;
  cout << "Sind es wirklich 'ÄpfelBirnen'? " <<
      ((ab == res) ? "Ja!" : "Nein???") << endl;

  // ab hier auskommentieren, solange du noch kein += hast
  a += bb;
  a += k;
  cout << "Und jetzt gibt es '" << a << "'." << endl;

  // ab hier auskommentieren, solange Index- und Typumwandlungsoperator fehlen
  cout << "'" << res << "[5]' ist ein '" << res[5] << "'." << endl;
  res[5] = 'H';
  cout << "Und jetzt machen wir ein 'H' daraus: '" << res << "'." << endl;
  cout << "Ausgabe als C++ string: '" << string(res) << "'." << endl;
  cout << "Wird '" << b << "[6]' richtig abgefangen? ";
  b[6] = 'x';
  cout << ((b == bb) ?  "Ja!" : "Nein???") << endl;
  

  return 0;
}
