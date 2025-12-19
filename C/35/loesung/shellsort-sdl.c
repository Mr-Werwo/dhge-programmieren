// Shellsort (= Sortieren durch Einfügen mit kleiner werdenden Abständen)
//
// Aufruf: shellsort-sdl anzahl
//
// Klaus Kusche, 2020

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "sdlinterf.h"

// Verzögerungen (in Millisekunden) für die Grafik-Anzeige
// ... beim Start
#define START_MS 200
// ... am Ende (bevor das Fenster verschwindet)
#define ENDE_MS 3000
// ... bei jedem Vergleich
#define VERGL_MS 50
// ... bei jeder Vertauschung
#define TAUSCH_MS 100

// die Farbwwerte
const int farbe_normal[] = { 0, 255, 0 };     // normaler Balken
const int farbe_vergl[] = { 255, 255, 0 };    // zu vergleichender Balken
const int farbe_tausch[] = { 255, 0, 255 };   // zu vertauschender Balken
const int farbe_schwarz[] = { 0, 0, 0 };      // schwarz (zum Weglöschen)

// Konstanten (in Pixeln) für das Grafik-Layout
// initialisiert in "main", benutzt in "balken"
// Breite eines Balkens
int breite;
// Eine Höhen-Einheit
int hoehe;
// Linker Rand = Startposition des ersten Balkens in X-Richtung
// (gleicher Rand links & rechts,
// damit die Balken im Fenster schön in der Mitte stehen)
int xstart;

// Zähler für die Vergleiche und Vertauschungen
int vergl = 0;
int vertau = 0;

// Zeichne den Balken Nummer i in Farbe farbe
void balken(const int arr[], int i, const int farbe[])
{
  int xpos = xstart + i * breite;
  sdlDrawRectFromTo(xpos + 1, SDL_Y_SIZE - 1,
                    xpos + breite - 1, SDL_Y_SIZE - arr[i] * hoehe,
                    farbe[0], farbe[1], farbe[2]);
  sdlUpdate();
}

// Vergleiche mit farbiger Anzeige und Verzögerung:
// Ist das Element an pos1 kleiner als das Element an pos2? (true / false)
// Da wir das Array mit lauter verschiedenen Elementen initialisieren,
// kommt "gleich" nicht vor!
bool kleiner(const int arr[], int pos1, int pos2)
{
  ++vergl;

  balken(arr, pos1, farbe_vergl);
  balken(arr, pos2, farbe_vergl);
  sdlMilliSleep(VERGL_MS);
  balken(arr, pos1, farbe_normal);
  balken(arr, pos2, farbe_normal);
  
  return (arr[pos1] < arr[pos2]);
}

// Vertausche die Elemente an pos1 und pos2 mit farbiger Anzeige und Verzögerung
void tausche(int arr[], int pos1, int pos2)
{
  ++vertau;

  // zeichne die zu vertauschenden Balken färbig
  balken(arr, pos1, farbe_tausch);
  balken(arr, pos2, farbe_tausch);
  sdlMilliSleep(TAUSCH_MS);

  // zeichne den längeren alten Balken schwarz,
  // weil sonst würde nach dem Tausch beim Überzeichnen mit dem kürzeren Balken
  // oben ein Rest sichtbar bleiben!
  if (arr[pos1] > arr[pos2]) {
    balken(arr, pos1, farbe_schwarz);
  } else {
    balken(arr, pos2, farbe_schwarz);
  }

  // tausche
  int tmp = arr[pos1];
  arr[pos1] = arr[pos2];
  arr[pos2] = tmp;

  // zeichne die vertauschten Balken normal
  balken(arr, pos1, farbe_normal);
  balken(arr, pos2, farbe_normal);
}

// Befülle das Array zufällig mit den Zahlen 1 bis anzahl
// und zeige den Anfangszustand an
void fuelle(int arr[], int anzahl)
{
  // Array aufsteigend mit den Zahlen 1 bis anzahl füllen (daher i+1)
  for (int i = 0; i < anzahl; ++i) {
    arr[i] = i + 1;
  }

  // Array mischen:
  // 3000 mal zwei zufällige Positionen im Array ermitteln
  // und die Werte an diesen Positionen vertauschen
  // (es gibt bessere Verfahren, aber die sind nicht gefragt)
  for (int i = 0; i < 3000; ++i) {
    int x = rand() % anzahl;
    int y = rand() % anzahl;
    int tmp = arr[x];
    arr[x] = arr[y];
    arr[y] = tmp;
  }  

  for (int i = 0; i < anzahl; ++i) {
    balken(arr, i, farbe_normal);
  }
}

// sortiere das Array
void sort(int arr[], int anzahl)
{
  // Die Abstände zwischen zwei zu vergleichenden Elementen
  // Diese Zahlen kommen aus der wissenschaftlichen Literatur
  // und beeinflussen, wie schnell der Shellsort sortiert
  //int schrittweite[] = { 385, 124, 40, 13, 4, 1 };
  //int schrittweite[] = { 336, 112, 48, 21, 7, 3, 1 };
  int schrittweite[] = { 301, 132, 57, 23, 10, 4, 1 };

  // Hol dir der Reihe nach die Schrittweiten aus dem Array schrittweite
  for (int j = 0; j < sizeof(schrittweite)/sizeof(schrittweite[0]); ++j) {
    // Der Vergleichs- und Vertausch-Abstand: aktuelles Element aus schrittweite
    int abst = schrittweite[j];
    // Für jede Position pos beginnend bei abst bis zur letzten ...
    for (int pos = abst; pos < anzahl; ++pos) {
      // ... vergleiche und vertausche den Wert von der Stelle pos
      // der Reihe nach (von rechts nach links) immer wieder mit den Werten
      // 1*abst, 2*abst, 3*abst, ... Positionen davor, bis der Wert von pos
      // entweder keinen Vorgänger abst Positionen davor hat
      // oder dieser Vorgänger kleiner ist
      for (int i = pos; (i >= abst) && kleiner(arr, i, i - abst); i -= abst) {
        tausche(arr, i, i - abst);
      }
    }
  }
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s anzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int anzahl = atoi(argv[1]);
  int max = SDL_X_SIZE / 2;
  if (max > SDL_Y_SIZE) { max = SDL_Y_SIZE; }
  if ((anzahl <= 0) || (anzahl > max)) {
    fprintf(stderr, "%s: Die Anzahl muss größer 0 und kleinergleich %d sein\n",
            argv[0], max);
    exit(EXIT_FAILURE);
  }
  // Geometrie aus der Anzahl berechnen
  breite = SDL_X_SIZE / anzahl;
  hoehe = SDL_Y_SIZE / anzahl;
  xstart = (SDL_X_SIZE % anzahl) / 2;

  int array[anzahl];

  srand(time(NULL));

  sdlInit();
  sdlSetBlack();

  fuelle(array, anzahl);
  
  sdlMilliSleep(START_MS);  

  sort(array, anzahl);

  printf("%d Vergleiche\n%d Vertauschungen\n", vergl, vertau);

  sdlMilliSleep(ENDE_MS);
  sdlExit();
  
  exit(EXIT_SUCCESS);
}
