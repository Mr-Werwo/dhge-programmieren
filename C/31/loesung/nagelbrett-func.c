// Nagelbrett-Simulation mit Balkendiagramm, Version mit Funktionen
//
// Aufruf: nagelbrett-func reihen kugeln
//
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// maximale Länge der Balken (DOS-Fenster = 80, davor steht noch eine Zahl)
#define MAX_BALKEN 68

// Lass "kugeln" Kugeln auf ein Nagelbrett mit "reihen" Reihen fallen
// und speichere das Ergebnis in "topf"
void simul(int topf[], int reihen, int kugeln)
{
  // Kugeln einzeln fallen lassen
  for (int k = 1; k <= kugeln; ++k) {
    // für jede Kugel:
    // Berechne t = Nummer des Topfes, in den die Kugel fällt
    //            = "wie oft ist die Kugel nach rechts gefallen?"
    // (Topf ganz links: Nummer 0, Topf ganz rechts: Nummer "reihen")
    // nicht vergessen:
    // Anzahl der "rechts" beginnt bei jeder Kugel wieder bei 0!
    int t = 0; 
    // lass die Kugel nacheinander auf jede Reihe fallen                
    for (int r = 1; r <= reihen; ++r) {  
      // ... und zähle, wie oft sie zufällig nach rechts fällt:
      // rechts wenn rand()%2 gleich 1 ist, links wenn es 0 ist
      t += rand() % 2;               
                                     
    }
    ++(topf[t]);  // Kugel fiel t Mal rechts ==> sie kommt zu Topf t dazu
  }
}

// gib anz viele zahlen in arr als Histogramm aus
void ausgabe(int arr[], int anz)
{
  // wir müssen zuerst die größte Zahl im Array finden,
  // damit wir wissen, wie wir die Balken skalieren müssen
  int max = arr[0];
  for (int i = 1; i < anz; ++i) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  
  // gib die einzelnen Werte aus
  for (int i = 0; i < anz; ++i) {
    printf("%10d ", arr[i]);
    // len: Länge des Balkens, Anzahl der noch auszugebenden Zeichen
    // eine Abwärts-Schleife spart eine zusätzliche Zähl-Variable
    for (int len = (arr[i] * MAX_BALKEN) / max; len > 0; --len) {
      putchar('#');
    }
    putchar('\n');
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    fprintf(stderr, "Aufruf: %s reihen kugeln\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int reihen = atoi(argv[1]);
  int kugeln = atoi(argv[2]);
  if ((reihen <= 0) || (kugeln <= 0)) {
    fprintf(stderr, "%s: Falsche Eingabe!\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  srand((unsigned int)(time(NULL)));

  // reihen+1 Zähler für die Anzahl der Kugeln in jedem Topf
  // (denn bei "reihen" vielen Nagelreihen gibt es
  // "reihen+1" viele Möglichkeiten bzw. Töpfe unter den Nägeln)
  int topf[reihen + 1];  
  // alle Töpfe auf "leer" setzen
  for (int t = 0; t <= reihen; ++t) {
    topf[t] = 0;
  }

  simul(topf, reihen, kugeln);
  ausgabe(topf, reihen + 1);
  
  exit(EXIT_SUCCESS);
}
