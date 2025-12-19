// String-Klasse
//
// Aufruf: strings
//
// Klaus Kusche, 2012

#include <iostream>
#include <cstring>

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

  return 0;
}
