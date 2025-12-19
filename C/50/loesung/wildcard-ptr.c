// Wildcard matching, rekursiv, Version mit Pointern:
// @ steht für beliebig viele beliebige Zeichen (oder gar nichts)
// % steht für genau ein beliebiges Zeichen
//
// Aufruf: wildcard text wildcard
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool match(const char *text, const char *wildc)
{
  // vergleiche zeichenweise:
  // Setze beide Pointer in jedem Durchlauf um ein Zeichen weiter
  for ( ; ; ++text, ++wildc) {
    if (*wildc == '\0') {
      // @%-Text ist aus ==> normaler Text muss auch aus sein, sonst falsch
      if (*text == '\0') return true;
      else return false;
    } else if (*wildc == '@') {
      // Bei '@' im @%-Text muss der @%-Text hinter dem '@'
      // mit *jedem* Rest des normalen Textes (einschließlich dem leeren Rest)
      // ab der aktuellen Position verglichen werden
      for (const char *rest = text; ; ++rest) {
        // passt irgendein Rest, passt alles
        if (match(rest, wildc + 1)) return true;
        // bin ich am Ende des normalen Textes, ohne dass ein Rest gepasst hat,
        // so passt das '@' nicht
        if (*rest == '\0') return false;
      }
    } else if (*text == '\0') {
      // @%-Text ist noch nicht aus, normaler Text ist aus ==> Passt nicht
      return false;
    } else if (*wildc == '%') {
      // Jedes Zeichen im normalen Text passt auf ein '?' im @%-Text
      // ==> Nichts zu tun, mit nächstem Zeichen weitermachen
    } else {
      // Im @%-Text steht ein normales Zeichen
      // Wenn das entsprechende Zeichen im normalen Text nicht gleich ist
      // ==> passt nicht
      // Wenn es gleich ist
      // ==> nichts tun, mit mit nächstem Zeichen weitermachen
      if (*text != *wildc) return false;
    }
  }
}

int main(int argc, const char *argv[])
{  
  if (argc != 3) {
    fprintf(stderr, "Usage: %s text wildcard\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("%s\n", match(argv[1], argv[2]) ? "match" : "fail");
  exit(EXIT_SUCCESS);
}
