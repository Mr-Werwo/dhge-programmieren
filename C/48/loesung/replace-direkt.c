// String-Funktionen: Text ersetzen, zeichenweise ohne Stringfunktionen
//
// Aufruf: replace alt neu
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

#define LINE_LEN 4096

char *strrepl(char dest[], const char src[],
              const char oldStr[], const char newStr[])
{
  const char *srcPtr = src;    // Aktuelle Position in src
  char *destPtr = dest;        // Aktuelle Position in dest

  while (*srcPtr != '\0') {
    if (*srcPtr == oldStr[0]) {
      // aktuelles Zeichen == erstes Zeichen von oldStr
      // (dieses if vermeidet auch Treffer bei leerem oldStr)
      // ==> das könnte ein Vorkommen von oldStr sein
      // ==> vergleiche src ab srcPtr mit oldStr
      const char *oldPtr;  // Aktuelle Position in oldStr
      const char *tmpPtr;  // Hilfs-Pointer in src: Wo vergleiche ich gerade?
      for (tmpPtr = srcPtr, oldPtr = oldStr;
           (*oldPtr != '\0') && (*oldPtr == *tmpPtr);
           ++tmpPtr, ++oldPtr) {
      }
      if (*oldPtr == '\0') {
        // oldStr wurde komplett gefunden
        // tmpPtr zeigt hinter die Fundstelle in src
        // mach im nächsten Schleifendurchlauf
        // mit dem src-Zeichen hinter der Fundstelle weiter
        srcPtr = tmpPtr;
        // newStr nach dest kopieren, newPtr = Aktuelle Position in new
        for (const char *newPtr = newStr; *newPtr != '\0'; ++newPtr) {
          *(destPtr++) = *newPtr;
        }
        // Normales Kopieren eines Zeichens entfällt:
        // Gleich nächster Umlauf des while: Nächstes src-Zeichen anschauen
        continue;
      }
      // else: oldStr nicht komplett gefunden ==> Normalfall: Kopiere 1 Zeichen
    }
    // "Normalfall": Kopiere ein Zeichen von src nach dest
    *(destPtr++) = *(srcPtr++);
  }

  *destPtr = '\0';  // neuen String in dest beenden
  return dest;
}

int main(int argc, const char *argv[])
{
  char input[LINE_LEN], output[LINE_LEN];
  
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s alt neu\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  while (fgets(input, sizeof(input), stdin)) {
    fputs(strrepl(output, input, argv[1], argv[2]), stdout);
  }

  exit(EXIT_SUCCESS);
}
