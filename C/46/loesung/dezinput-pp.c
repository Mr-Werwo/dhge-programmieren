// Einlesen von Dezimalzahlen
// (wie strtol mit Pointer-auf-Pointer-Parameter)
//
// Aufruf: dezinput zahl1 zahl2 ...
// 
// Klaus Kusche, 2017

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// endp ist ein "by Reference" übergebener char-Pointer
// also ein Pointer auf eine char*-Variable im Aufrufer, daher **
// die Funktion soll in diesem Parameter einen Pointer speichern,
// der auf das erste Zeichen *hinter* der gelesenen Zahl in str zeigt
// (also auf die Ende-Markierung, wenn str nur die Zahl enthält)
int unser_strtol(const char str[], char **endp)
{
  int z = 0;     // der bisher eingelesene Wert der Zahl
  int vorz = 1;  // Vorzeichen (+1 oder -1)

  // Vorzeichen am Anfang speichern, am Ende zur Zahl dazumultiplizieren
  if (*str == '-') {
    vorz = -1;
    str++;     // Stelle den String-Pointer auf das Zeichen hinter dem '-'
  }

  // Schleife über die Zeichen von str, solange es Ziffern sind
  for ( ; isdigit(*str); ++str) {  
    // ASCII-Code c in Zahl umrechnen und hinten an z anhängen
    // Wenn c ein Ziffern-Zeichen ist, liefert c - '0' den Ziffernwert von c
    z = (10 * z) + (*str - '0'); 
  }

  // jetzt zeigt str auf das erste nicht-Ziffern-Zeichen
  // ==> im Ausgabe-Parameter speichern, falls nicht NULL angegeben wurde
  if (endp != NULL) {
    *endp = str;
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
    char *ende;
    // unser_strtol bekommt die Adresse von ende übergeben
    printf("%s = %d", argv[i], unser_strtol(argv[i], &ende));
    if (*ende != '\0') {  // zeigt ende nicht auf die Ende-Markierung?
      printf(", Rest des Wortes: \"%s\"\n", ende);
    } else {
      printf("\n");
    }
  }
  
  exit(EXIT_SUCCESS);
}
