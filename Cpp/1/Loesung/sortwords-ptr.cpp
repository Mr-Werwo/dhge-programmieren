// Sortieren mit Strukturen und Pointer-Parametern
//
// Aufruf: sortwords-ptr wort1 wort2 wort3 ...
//
// Klaus Kusche, 2011

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MAX_ELEMS = 100;

struct element {
  int nummer;
  const char *text;
};

bool verkehrt(const element *a, const element *b);
void tausche(element *a, element *b);

int main(int argc, const char *argv[])
{
  element data[MAX_ELEMS];

  int anzahl = argc - 1;  // argv[0] spielt nicht mit
  if (anzahl == 0) {
    cerr << "Aufruf: " << argv[0] << " wort1 wort2 wort3 ..." << endl;
    exit(EXIT_FAILURE);
  }
  if (anzahl > MAX_ELEMS) {
    cerr << argv[0] << ": Zu viele Worte (max. " << MAX_ELEMS << ")" << endl;
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < anzahl; ++i) {
    data[i].nummer = i + 1;
    data[i].text = argv[i + 1];
  }

  for (int i = 0; i < anzahl - 1; ++i) {
    for (int j = i + 1; j < anzahl; ++j) {
      if (verkehrt(&(data[i]), &(data[j]))) {
        tausche(&(data[i]), &(data[j]));
      }
    }
  }

  for (int i = 0; i < anzahl; ++i) {
    cout << data[i].nummer << ": " << data[i].text << endl;
  }
        
  exit(EXIT_SUCCESS);
}

void tausche(element *a, element *b)
{
  element tmp;

  tmp = *a; *a = *b; *b = tmp;
}

// stehen a und b verkehrt, d.h. ist a > b ?
bool verkehrt(const element *a, const element *b)
{
  return (strcmp(a->text, b->text) > 0);
}
