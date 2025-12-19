// Rahmenprogramm zum grafischen Sortieren, mit Pointern statt Index
//
// Aufruf: sort-ptr anzahl
//
// Klaus Kusche, 2021

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

// Pointer auf den Anfang unseres Arrays
// Für die Funktion "balken", damit sie ausrechnen kann,
// das wievielte Element im Array sie zeichnen soll
int *arr_beg;

// Zeichne den Balken für das Array-Element, auf das p zeigt, in Farbe farbe
void balken(const int *p, const int farbe[])
{
  int xpos = xstart + (p - arr_beg) * breite;
  sdlDrawRectFromTo(xpos + 1, SDL_Y_SIZE - 1,
                    xpos + breite - 1, SDL_Y_SIZE - *p * hoehe,
                    farbe[0], farbe[1], farbe[2]);
  sdlUpdate();
}

// Vergleiche mit farbiger Anzeige und Verzögerung:
// Ist das Element, auf das p1 zeigt, kleiner als das Element, auf das p2 zeigt?
// Ergebnis: true / false
// Da wir das Array mit lauter verschiedenen Elementen initialisieren,
// kommt "gleich" nicht vor!
bool kleiner(const int *p1, const int *p2)
{
  ++vergl;

  balken(p1, farbe_vergl);
  balken(p2, farbe_vergl);
  sdlMilliSleep(VERGL_MS);
  balken(p1, farbe_normal);
  balken(p2, farbe_normal);
  
  return (*p1 < *p2);
}

// Vertausche das Element, auf das p1 zeigt, mit dem Element, auf das p2 zeigt
// mit farbiger Anzeige und Verzögerung
void tausche(int *p1, int *p2)
{
  ++vertau;

  // zeichne die zu vertauschenden Balken färbig
  balken(p1, farbe_tausch);
  balken(p2, farbe_tausch);
  sdlMilliSleep(TAUSCH_MS);

  // zeichne den längeren alten Balken schwarz,
  // weil sonst würde nach dem Tausch beim Überzeichnen mit dem kürzeren Balken
  // oben ein Rest sichtbar bleiben!
  if (*p1 > *p2) {
    balken(p1, farbe_schwarz);
  } else {
    balken(p2, farbe_schwarz);
  }

  // tausche
  int tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;

  // zeichne die vertauschten Balken normal
  balken(p1, farbe_normal);
  balken(p2, farbe_normal);
}

// Befülle das Array zufällig mit den Zahlen 1 bis anzahl
// und zeige den Anfangszustand an
void fuelle(int arr[], int anzahl)
{
  // ...
}

// sortiere das Array
// unter Verwendung von "kleiner" und "tausche"
void sort(int arr[], int anzahl)
{
  // ...
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
  arr_beg = array;

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
