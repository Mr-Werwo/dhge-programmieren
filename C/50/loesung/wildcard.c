// Wildcard matching, rekursiv, Version mit Index:
// @ steht für beliebig viele beliebige Zeichen (oder gar nichts)
// % steht für genau ein beliebiges Zeichen
//
// Aufruf: wildcard text wildcard
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool match(const char text[], const char wildc[])
{
  // vergleiche zeichenweise:
  for (int i = 0; ; ++i) {
    if (wildc[i] == '\0') {
      // @%-Text ist aus ==> normaler Text muss auch aus sein, sonst falsch
      if (text[i] == '\0') return true;
      else return false;
    } else if (wildc[i] == '@') {
      // Bei '@' im @%-Text muss der @%-Text hinter dem '@'
      // mit *jedem* Rest des normalen Textes (einschließlich dem leeren Rest)
      // ab der aktuellen Position verglichen werden
      for (int j = i; ; ++j) {
        // passt irgendein Rest, passt alles
        if (match(&(text[j]), &(wildc[i + 1]))) return true;
        // bin ich am Ende des normalen Textes, ohne dass ein Rest gepasst hat,
        // so passt das '@' nicht
        if (text[j] == '\0') return false;
      }
    } else if (text[i] == '\0') {
      // @%-Text ist noch nicht aus, normaler Text ist aus ==> Passt nicht
      return false;
    } else if (wildc[i] == '%') {
      // Jedes Zeichen im normalen Text passt auf ein '?' im @%-Text
      // ==> Nichts zu tun, mit nächstem Zeichen weitermachen
    } else {
      // Im @%-Text steht ein normales Zeichen
      // Wenn das entsprechende Zeichen im normalen Text nicht gleich ist
      // ==> passt nicht
      // Wenn es gleich ist
      // ==> nichts tun, mit mit nächstem Zeichen weitermachen
      if (text[i] != wildc[i]) return false;
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
