// Einlesen Hexzahlen
//
// Aufruf: hex zahl ...
//
// Klaus Kusche, 2011

#include <stdio.h>
//#include <string.h>

int main(int argc, const char *argv[])
{
  // Schleife über alle Zahlen
  for (int i = 1; i < argc; ++i) {  
    int zahl = 0;
    // Schleife über die Ziffern der Zahl Nummer i
    // bis man bei der Endemarkierung '\0' des Wortes ist
    // Alternativ, aber langsamer bzw. unüblich:
    //int len = strlen(argv[i]);
    //for (pos = 0; pos < len; ++pos) {
    for (int pos = 0; argv[i][pos] != '\0'; ++pos) {
      // c = Zeichen an Stelle pos im i-ten Wort
      char c = argv[i][pos];
      // schieb das bisherige Zwischenergebnis um eine Hex-Stelle nach links
      // zahl = zahl * 16
      // verwandle das Zeichen c in den entsprechenden Ziffern-Wert
      // und zähle diesen als hinterste Ziffer zum Zwischenergebnis dazu
      // + (c - '0') usw.
      if ((c >= '0') && (c <= '9')) {
        zahl = zahl * 16 + (c - '0');
      } else if  ((c >= 'A') && (c <= 'F')) {
        // analog zu (c - '0'):
        // 'A' - 'A' + 10 = 10, 'B' - 'A' + 10 = 11, 'C' - 'A' + 10 = 12, ...
        zahl = zahl * 16 + (c - 'A' + 10);
      } else if  ((c >= 'a') && (c <= 'f')) {
        zahl = zahl * 16 + (c - 'a' + 10);
      } else {
        fprintf(stderr, "%s: Ungültiges Zeichen %c\n", argv[0], c);
        return 1;
      }
    }

    printf("%s = %d\n", argv[i], zahl);
  }
  
  return 0;
}
