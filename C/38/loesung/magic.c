// Magisches Quadrat mit Rösslsprung-Methode berechnen
//
// Aufruf: magic seitenlänge
//
// Klaus Kusche, 2020

#include <stdio.h>
#include <stdlib.h>

void fill(int groesse, int arr[groesse][groesse], int val);
void print(int groesse, int arr[groesse][groesse]);
void magic(int groesse, int arr[groesse][groesse]);
void check_magic(int groesse, int arr[groesse][groesse], int soll);

// befülle alle Elemente von arr mit val
void fill(int groesse, int arr[groesse][groesse], int val)
{
  for (int zeile = 0; zeile < groesse; ++zeile) {
    for (int spalte = 0; spalte < groesse; ++spalte) {
      arr[zeile][spalte] = val;
    }
  }
}

// gib das Array arr aus
void print(int groesse, int arr[groesse][groesse])
{
  for (int zeile = 0; zeile < groesse; ++zeile) {
    for (int spalte = 0; spalte < groesse; ++spalte) {
      printf("%4d", arr[zeile][spalte]);
    }
    putchar('\n');
  }
}

// befülle arr so, dass sich ein magisches Quadrat ergibt
void magic(int groesse, int arr[groesse][groesse])
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
void check_magic(int groesse, int arr[groesse][groesse], int soll)
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

  int a[groesse][groesse];

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
