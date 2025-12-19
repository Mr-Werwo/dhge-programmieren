// String-Funktionen: Text ersetzen, mit String-Funktionen
//
// Aufruf: replace alt neu
//
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 4096

char *strrepl(char dest[], const char src[],
              const char oldStr[], const char newStr[])
{
  int oldStrLen = strlen(oldStr);
  if (oldStrLen == 0) {
    // Suchstring ist leer ==> Ergebnis ist unverändert kopierte Eingabe src
    strcpy(dest, src);
  } else {
    // damit strcat / strncat anhängen kann,
    // muss der Zielstring eine gültige Ende-Markierung haben
    dest[0] = '\0';
    
    // aktuelle Position in src, ab der oldStr gesucht wird
    // (alles davor ist schon verarbeitet)
    const char *curPos = src;  // beginne ganz vorne ...
    for (;;) {
      // ... suche das nächste Vorkommen von oldStr in src ab Position curPos 
      const char *wordPos = strstr(curPos, oldStr);
      // ... wenn nicht gefunden: Schleife fertig!
      if (wordPos == NULL) break;
      // Hänge zuerst alles zwischen alter und neuer Fundstelle an dest an ...
      // (Differenz der Pointer = Anzahl der Zeichen zwischen den Pointern)
      strncat(dest, curPos, wordPos - curPos);
      // ... und dann das neue Wort
      strcat(dest, newStr);
      // suche in src unmittelbar nach dem gefundenen oldStr weiter
      curPos = wordPos + oldStrLen;
    }
    // hänge alles hinter der letzten Fundstelle in src an dest an
    // (wenn oldStr nie gefunden wurde: alles ab Beginn von src)
    strcat(dest, curPos);
  }

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
