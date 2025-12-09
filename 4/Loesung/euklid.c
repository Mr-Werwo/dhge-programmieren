// ggT zweier ganzer Zahlen
//
// Aufruf: euklid a b
//
// Klaus Kusche, 2010

#include <stdio.h>
// atoi und abs kommen aus stdlib.h
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  // Wurde das Programm mit 2 Zahlen auf der Befehlszeile aufgerufen?
  if (argc != 3) {
    // Fehlermeldung (mit richtigem Programmnamen eingesetzt)
    fprintf(stderr, "Aufruf: %s a b\n", argv[0]);
    // Aufhören; EXIT_FAILURE sagt dem DOS-Fenster, dass irgendein Fehler war
    exit(EXIT_FAILURE);
  }

  // Wir brauchen 2 ganzzahlige Variablen
  // für die zwei Zahlen, von denen wir den ggt berechnen,
  // Der ggt wird immer von den positiven Werten gerechnet,
  // auch wenn negative Zahlen eingegeben werden
  // ==> Wir streichen mit "abs" das Vorzeichen weg
  // (abs ... "Absolutbetrag").
  // das wird von innen nach außen ausgerechnet:
  // - stecke den Text argv[1] in die Funktion "atoi" hinein,
  //   damit er in eine Zahl (einen int) verwandelt wird
  // - nimm die Zahl, die aus dem atoi herauskommt 
  //   und stecke sie gleich wieder in die Funktion "abs" hinein
  // - nimm die Zahl, die aus dem abs herauskommt
  //   (das ist die hineingesteckte Zahl ohne Vorzeichen)
  //   und speichere sie in a
  // ... und dasselbe nochmal für argv[2] und b
  int a = abs(atoi(argv[1]));
  int b = abs(atoi(argv[2]));

  // Wie in der Angabe beschrieben:
  while (b > 0) {  // solange b nicht 0 ist...
    int r = a % b; // ... berechne den Rest von a / b" ("%" macht genau das)
                   // ... und merk ihn dir in einer neuen Hilfsvariable r
    a = b;         // ... das alte b wird unser neues a ...
    b = r;         // ... und der Rest wird unser neues b für die nächste Runde
  }

  // an diese Stelle des Programms kommen wir erst, wenn b == 0 ist

  // Ausgabe der beiden Eingaben und des Ergebnisses in a:
  // Laut Angabe: "Wenn b 0 geworden ist, steht in a der ggt"
  printf("ggT(%s, %s) = %d\n", argv[1], argv[2], a);

  // Programmende, "alles ok"
  exit(EXIT_SUCCESS);
}
