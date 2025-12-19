// Beispiel für ein dynamisch großes zweidimensionales Array (n * n)
// gespeichert als n einzelne, eindimensionale Zeilen-Arrays
// und einem eindimensionalen Array von Pointern auf die Zeilen
//
// Magisches Quadrat mit Rösslsprung-Methode berechnen
//
// Aufruf: magic-dyn seitenlänge
//
// Klaus Kusche, 2020

#include <stdio.h>
#include <stdlib.h>

int **anlegen(int groesse);
void fill(int groesse, int *arr[], int val);
void print(int groesse, int *arr[]);
void magic(int groesse, int *arr[]);
void check_magic(int groesse, int *arr[], int soll);

// leg die dynamischen Arrays an
int **anlegen(int groesse)
{
  // 1. Schritt: Lege das Array an,
  // in dem die Pointer auf die einzelnen Zeilen gespeichert werden
  // Das ist ein Array von Pointern
  // Der Pointer auf den Anfang des Arrays
  // ist daher ein Pointer auf einen Pointer
  int **ptr_arr = (int **) (malloc(groesse * sizeof(int *)));
  if (ptr_arr == NULL) {
    fprintf(stderr, "Anlegen von %lu Bytes schlug fehl\n",
            groesse * sizeof(int *));
    exit(EXIT_FAILURE);
  }

  // 2. Schritt: Lege pro Zeile ein Array an und trage es in ptr_arr ein
  for (int zeile = 0; zeile < groesse; ++zeile) {
    ptr_arr[zeile] = (int *) (malloc(groesse * sizeof(int)));
    if (ptr_arr[zeile] == NULL) {
      fprintf(stderr, "Anlegen von %lu Bytes schlug fehl\n",
              groesse * sizeof(int));
      exit(EXIT_FAILURE);
    }
  }

  return ptr_arr;
}

// befülle alle Elemente von arr mit val
void fill(int groesse, int *arr[], int val)
{
  for (int zeile = 0; zeile < groesse; ++zeile) {
    for (int spalte = 0; spalte < groesse; ++spalte) {
      arr[zeile][spalte] = val;
    }
  }
}

// gib das Array arr aus
void print(int groesse, int *arr[])
{
  for (int zeile = 0; zeile < groesse; ++zeile) {
    for (int spalte = 0; spalte < groesse; ++spalte) {
      printf("%4d", arr[zeile][spalte]);
    }
    putchar('\n');
  }
}

// befülle arr so, dass sich ein magisches Quadrat ergibt
void magic(int groesse, int *arr[])
{
  // Ausgangsposition: Erste Zeile, ganz rechts
  int zeile = 0;
  int spalte = groesse - 1;
  // Felder belegen
  for (int zahl = 1; zahl <= groesse * groesse; ++zahl) {
    arr[zeile][spalte] = zahl;
    // nächste Position berechnen
    if (zahl % groesse == 0) {
      // das war die n-te, (2*n)-te, ... Zahl ==> 2 Felder nach links
      spalte -= 2;
      if (spalte < 0) spalte += groesse;
      // Trickreicher: spalte = (spalte - 2 + groesse) % groesse;
    } else {
      // sonst: 2 Felder runter, 1 Feld nach links
      zeile += 2;
      if (zeile >= groesse) zeile -= groesse;
      // Trickreicher: zeile = (zeile + 2) % groesse;
      --spalte;
      if (spalte < 0) spalte += groesse;
      // Trickreicher: spalte = (spalte - 1 + groesse) % groesse;
    }
  }
}

// prüfe, ob arr ein magisches Quadrat mit Summe sum enthält
void check_magic(int groesse, int *arr[], int soll)
{
  int summe;

  summe = 0;
  for (int zeile = 0; zeile < groesse; ++zeile) {
    summe += arr[zeile][zeile];          // \-Diagonale
  }
  if (summe != soll) {
    fprintf(stderr, "Hauptdiagonale falsch (soll: %d, ist: %d)\n", soll, summe);
    exit(EXIT_FAILURE);
  }
  
  summe = 0;
  for (int zeile = 0; zeile < groesse; ++zeile) {
    summe += arr[zeile][(groesse - 1) - zeile]; // /-Diagonale
  }
  if (summe != soll) {
    fprintf(stderr, "Nebendiagonale falsch (soll: %d, ist: %d)\n", soll, summe);
    exit(EXIT_FAILURE);
  }
  
  for (int zeile = 0; zeile < groesse; ++zeile) {
    summe = 0;
    for (int spalte = 0; spalte < groesse; ++spalte) {
      summe += arr[zeile][spalte];
    }
    if (summe != soll) {
      fprintf(stderr, "Zeile %d falsch (soll: %d, ist: %d)\n",
              zeile, soll, summe);
      exit(EXIT_FAILURE);
    }
  }
  for (int spalte = 0; spalte < groesse; ++spalte) {
    summe = 0;
    for (int zeile = 0; zeile < groesse; ++zeile) {
      summe += arr[zeile][spalte];
    }
    if (summe != soll) {
      fprintf(stderr, "Spalte %d falsch (soll: %d, ist: %d)\n",
              spalte, soll, summe);
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s seitenlaenge\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int groesse = atoi(argv[1]);
  if ((groesse <= 0) || (groesse % 2 == 0) || (groesse % 3 == 0)) {
    fprintf(stderr, "%s: Die Seitenlänge muss positiv "
            "und nicht durch 2 oder 3 teilbar sein\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  int **a = anlegen(groesse);

  fill(groesse, a, -9999);
  magic(groesse, a);
  print(groesse, a);

  // Prüfung
  // Wert der Summe laut klugen Mathematikern...
  int summe = groesse * (groesse * groesse + 1) / 2;
  printf("Magische Zahl %d\n", summe);
  check_magic(groesse, a, summe);

  exit(EXIT_SUCCESS);
}
