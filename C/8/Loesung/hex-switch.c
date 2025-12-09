// Einlesen Hexzahlen, mit "switch"
//
// Aufruf: hex-switch zahl ...
// 
// Klaus Kusche, 2011

#include <stdio.h>

int main(int argc, const char *argv[])
{
  // Schleife über alle Zahlen 
  for (int i = 1; i < argc; ++i) {  
    int zahl = 0;
    // Schleife über die Ziffern der Zahl Nummer i
    // bis man bei der Endemarkierung '\0' des Wortes ist
    for (int pos = 0; argv[i][pos] != '\0'; ++pos) {
      // c = Zeichen an Stelle pos im i-ten Wort
      char c = argv[i][pos];
      switch (c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        // unser Compiler versteht auch Folgendes,
        // aber der C-Standard erlaubt das nicht!
        //case '0' ... '9':
          // schieb das bisherige Zwischenergebnis um eine Hex-Stelle nach links
          // ... verwandle das Zeichen c in den entsprechenden Ziffern-Wert
          // und zähle diesen als hinterste Ziffer zum Zwischenergebnis dazu
          zahl = zahl * 16 + (c - '0');
          break;
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
          // analog zu (c - '0'):
          // 'A' - 'A' + 10 = 10, 'B' - 'A' + 10 = 11, 'C' - 'A' + 10 = 12, ...
          zahl = zahl * 16 + (c - 'A' + 10);
          break;
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
          zahl = zahl * 16 + (c - 'a' + 10);
          break;
        default:
          fprintf(stderr, "%s: Ungültiges Zeichen %c\n", argv[0], c);
          return 1;
      }
    }

    printf("%s = %d\n", argv[i], zahl);
  }
  
  return 0;
}
