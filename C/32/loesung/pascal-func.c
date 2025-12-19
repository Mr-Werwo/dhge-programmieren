// Pascal'sches Dreieck, diesmal mit eindimensionalem Array und Funktionen
//
// Aufruf: pascal-func lines
// 
// Klaus Kusche, 2010
 
#include <stdio.h>
#include <stdlib.h>

// gib die ersten cnt Elemente von array aus
void output(int array[], int cnt);
// berechne und drucke ein Pascal'sches Dreieck mit lines Zeilen
void pascal(int lines);

// gib die ersten cnt Elemente von array aus
void output(int array[], int cnt)
{
  for (int i = 0; i < cnt; ++i) {
    printf("%d ", array[i]);
  }
  putchar('\n');
}

// berechne und drucke ein Pascal'sches Dreieck mit lines Zeilen
void pascal(int lines)
{
  // Die aktuelle Zeile des Dreiecks
  // Spaltenanzahl der letzten Zeile = Zeilenanzahl, daher Größe = Zeilenanzahl
  int p[lines];

  // Initialisierung bzw. erste Zeile: Alle 0, nur p[0] ist 1
  p[0] = 1;
  for (int i = 1; i < lines; ++i) {
    p[i] = 0;
  }

  output(p, 1);

  for (int line = 2; line <= lines; ++line) {
    // wenn man von rechts nach links rechnet,
    // überschreibt man keine alten Werte, die man noch braucht,
    // mit neuen Werten
    // Hinterste Spalte in Zeile line ist line-1
    // Spalte 0 ist immer 1, braucht nicht neu berechnet werden
    for (int i = line - 1; i > 0; --i) {
      p[i] = p[i - 1] + p[i];
    }
    output(p, line);
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s lines\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int lines = atoi(argv[1]);
  if (lines < 1) {
    fprintf(stderr, "Lines <= 0?\n");
    exit(EXIT_FAILURE);
  }
  
  pascal(lines);
  
  exit(EXIT_SUCCESS);
}
