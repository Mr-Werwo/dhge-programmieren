// Rekursive Quicksort-Funktion
//
// Aufruf: quicksort-sdl anzahl
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

// Die Partitionierungs-Funktion:
// Teilt das Array arr vom Index links bis zum Index rechts
// (jeweils einschließlich) in einen linken und einen rechten Teil
// Returnwert: Index der Grenze (= des Elementes zwischen den beiden Teilen)
// Alle Elemente links vom Returnwert sind kleiner als das Teilungselement
// Alle Elemente rechts vom Returnwert sind größergleich dem Teilungselement
int partition(int arr[], int links, int rechts)
{
  // 1.) Wir müssen irgendein Element als Teilungselement wählen
  // Das Teilungselement wird dann aus dem Array genommen
  // und durch das letzte Element im aufzuteilenden Bereich des Arrays ersetzt
  // (der aufzuteilende Teil des Arrays wird 1 kürzer, er geht nur bis rechts-1)
  // Wir nehmen gleich das letzte Element im Bereich (Element "rechts")
  // als Teilungselement, dann müssen wir nichts tun.
  // In der Praxis ist das keine besonders gute Wahl,
  // man nimmt oft das mittlere Element des Array-Bereiches oder 
  // das wertmäßig mittlere von erstem, mittlerem und letztem Element
  
  // 2.) Partitioniere das um 1 verkürzte Array (von links bis rechts-1)
  // Dazu gibt es zwei übliche Algorithmen:
  // a) Den mit zwei von den Enden gegenläufigen Indices:
  //   Wo sie zusammenstoßen, ist die Teilung
  //   (schneller, schwieriger)
  // b) Den mit einem komplett von links nach rechts laufenden Index
  //   und einem ihm auch von links nachlaufenden Teilungsindex
  //   (einfacher, aber deutlich ineffizienter: Macht viel mehr Vertauschungen,
  //    weil zu große Elemente ev. mehrmals nach rechts geschoben werden)


  // Variante 2a)
  int i = links;      // i wandert von links nach rechts
                      // alle Elemente links von i sind schon <= Teilungswert
  int j = rechts - 1; // j beginnt *vor* dem Teilungselement ganz rechts,
                      // wandert von rechts nach links
                      // alle Elemente rechts von j sind schon >= Teilungswert
                      // alle Elemente zwischen i und j sind noch unbekannt
  for (;;) {
    // suche von links ein Element, das größer als der Teilungswert ist
    while ((i < rechts) && !kleiner(arr, rechts, i)) {
      ++i;
    }
    // suche von rechts ein Element, das kleiner als der Teilungswert ist
    while ((j > i) && !kleiner(arr, j, rechts)) {
      --j;
    }
    if (i >= j) break; // i und j sind zusammengestoßen ==> fertig!
    // i ist links von j:
    // i zeigt links auf ein zu großes Element,
    // j zeigt rechts auf ein zu kleines Element
    // ==> vertausche die beiden Elemente
    tausche(arr, i, j);
    // Nach dem Tausch: Element Nummer i und j stehen richtig
    // ==> Eins weitergehen und dann erneut falsche Elemente suchen
    ++i; --j;
  }
  // i ist jetzt der Index des ersten Elementes,
  // das größergleich dem Teilungswert ist
  int grenze = i;

/*
  // Variante 2b)
  // grenze ist der Index des ersten Elementes des "größer"-Teils im Array
  //   und auch der Index, an dem das nächste "kleine" Element gespeichert wird
  int grenze = links;
  // geh alle Elemente außer dem letzten (Teilungswert, Pos. rechts) durch 
  for (int i = links; i < rechts; ++i) { 
    // alle Elemente links von grenze sind kleiner als der Teilungswert
    // alle Elemente von grenze bis vor i sind größergleich dem Teilungswert
    // alle Elemente ab i sind noch unbekannt
    if (kleiner(arr, i, rechts)) {
      // Element Nummer i ist kleiner als der Teilungswert
      // ==> bring es nach vor an's Ende des "kleiner"-Teils,
      // indem Du es mit dem ersten Element des "größer"-Teils tauscht
      tausche(arr, i, grenze);
      ++grenze;                  // ... und mach den "kleiner"-Teil eins größer
    }
  }
*/

  // 3.) Speichere das Teilungselement von Position rechts
  // wieder zurück ins Array, und zwar an die Grenze:
  // Tausche es mit dem ersten Element des "größer"-Teils
  tausche(arr, rechts, grenze);
  return grenze;
}

// Die rekursive Quicksort-Funktion:
// Sortiert das Array arr vom Index links bis zum Index rechts
// (jeweils einschließlich)
void quicksort(int arr[], int links, int rechts)
{
  if (links >= rechts) {
    // Verbleibender Array-Teil hat nur 0 oder 1 Elemente
    // ==> nichts zu tun!
  } else {
    // Verbleibender Array-Teil hat mehrere Elemente
    // ==> aufteilen
    int part = partition(arr, links, rechts);
    // part ist der Index des Teilungs-Elementes,
    // das weder zum linken noch zum rechten Teil gehört
    // Alle Elemente kleiner als das Element part sind links von part,
    // Alle Elemente größergleich dem Element part sind rechts von part
    // ==> Die beiden Teile links und rechts von part rekursiv sortieren
    quicksort(arr, links, part - 1);
    quicksort(arr, part + 1, rechts);
  }
}

// sortiere das Array
void sort(int arr[], int anzahl)
{
  // Quicksort über das gesamte Array
  quicksort(arr, 0, anzahl - 1);
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
