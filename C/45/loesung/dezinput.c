// Einlesen von Dezimalzahlen
//
// Aufruf: dezinput zahl1 zahl2 ...
// 
// Klaus Kusche, 2017

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int unser_atoi(const char str[])
{
  int i = 0;     // Position der nächsten Ziffer in str
  int vorz = 1;  // Vorzeichen (+1 oder -1)

  // Vorzeichen am Anfang speichern, am Ende zur Zahl dazumultiplizieren
  if (str[0] == '-') {
    vorz = -1;
    ++i;     // Ziffern-Schleife fängt erst beim 2. Zeichen an
  }
  
  int z = 0;     // der bisher eingelesene Wert der Zahl
  for ( ; str[i] != '\0'; ++i) {  // Schleife über alle Zeichen von str
    char c = str[i];   // das i-te Zeichen von str
    if (isdigit(c)) {
      // ASCII-Code c in Zahl umrechnen und hinten an z anhängen
      // (d.h. den bisherigen Wert von z um eine Stelle nach links schieben)
      // Wenn c ein Ziffern-Zeichen ist, liefert c - '0' den Ziffernwert von c
      z = (10 * z) + (c - '0'); 
    } else {
      printf("'%c' ist keine Ziffer\n", c);
      break;
    }
  }
  
  return z * vorz;
}

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    fprintf(stderr, "Aufruf: %s zahl1 zahl2 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; ++i) {    
    printf("%s = %d\n", argv[i], unser_atoi(argv[i]));
  }
  
  exit(EXIT_SUCCESS);
}
