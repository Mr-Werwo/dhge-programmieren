// Rekursive Quicksort-Funktion mit Pointern
//
// Aufruf: quicksort-ptr anzahl
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
  // Array aufsteigend mit den Zahlen 1 bis anzahl füllen (daher ...+1)
  for (int *p = arr; p < arr + anzahl; ++p) {
    *p = (p - arr) + 1;
  }

  // Array mischen:
  // 3000 mal zwei zufällige Positionen im Array ermitteln
  // und die Werte an diesen Positionen vertauschen
  // (es gibt bessere Verfahren, aber die sind nicht gefragt)
  for (int i = 0; i < 3000; ++i) {
    int *p1 = arr + rand() % anzahl;
    int *p2 = arr + rand() % anzahl;
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
  }  

  for (int *p = arr; p < arr + anzahl; ++p) {
    balken(p, farbe_normal);
  }
}

// Die Partitionierungs-Funktion:
// Teilt das Array von der Position links bis zur Position rechts
// (jeweils einschließlich) in einen linken und einen rechten Teil
// Returnwert: Pointer auf die Grenze (= das Element zwischen den beiden Teilen)
// Alle Elemente links vom Returnwert sind kleiner als das Teilungselement
// Alle Elemente rechts vom Returnwert sind größergleich dem Teilungselement
// partition returniert jetzt einen Pointer, keinen Index
int *partition(int *links, int *rechts)
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
  int *lp = links;    // lp wandert von links nach rechts
                      // alle Elemente links von lp sind schon <= Teilungswert
  int *rp = rechts - 1; // rp beginnt *vor* dem Teilungselement ganz rechts,
                      // wandert von rechts nach links
                      // alle Elemente rechts von rp sind schon >= Teilungswert
                      // alle Elemente zwischen lp und rp sind noch unbekannt
  for (;;) {
    // suche von links ein Element, das größer als der Teilungswert ist
    while ((lp < rechts) && !kleiner(rechts, lp)) {
      ++lp;
    }
    // suche von rechts ein Element, das kleiner als der Teilungswert ist
    while ((rp > lp) && !kleiner(rp, rechts)) {
      --rp;
    }
    if (lp >= rp) break; // lp und rp sind zusammengestoßen ==> fertig!
    // lp ist links von rp:
    // lp zeigt links auf ein zu großes Element,
    // rp zeigt rechts auf ein zu kleines Element
    // ==> vertausche die beiden Elemente
    tausche(lp, rp);
    // Nach dem Tausch: Die Elemente lp und rp stehen richtig
    // ==> Eins weitergehen und dann erneut falsche Elemente suchen
    ++lp; --rp;
  }
  // lp ist jetzt der Index des ersten Elementes,
  // das größergleich dem Teilungswert ist
  int *grenze = lp;

/*
  // Variante 2b)
  // grenze zeigt auf das erste Elementes des "größer"-Teils im Array
  // das ist zugleich die Stelle,
  // an der das nächste "kleine" Element gespeichert wird
  int *grenze = links;
  // geh alle Elemente außer dem letzten (Teilungswert, Pos. rechts) durch 
  for (int *p = links; p < rechts; ++p) { 
    // alle Elemente links von grenze sind kleiner als der Teilungswert
    // alle Elemente von grenze bis vor p sind größergleich dem Teilungswert
    // alle Elemente ab p sind noch unbekannt
    if (kleiner(p, rechts)) {
      // Element Nummer i ist kleiner als der Teilungswert
      // ==> bring es nach vor an's Ende des "kleiner"-Teils,
      // indem Du es mit dem ersten Element des "größer"-Teils tauscht
      tausche(p, grenze);
      ++grenze;                  // ... und mach den "kleiner"-Teil eins größer
    }
  }
*/

  // 3.) Speichere das Teilungselement von Position rechts
  // wieder zurück ins Array, und zwar an die Grenze:
  // Tausche es mit dem ersten Element des "größer"-Teils
  tausche(rechts, grenze);
  return grenze;
}

// Die rekursive Quicksort-Funktion:
// Sortiert das Array von der Position links bis zur Position rechts
// (jeweils einschließlich)
void quicksort(int *links, int *rechts)
{
  if (links >= rechts) {
    // Verbleibender Array-Teil hat nur 0 oder 1 Elemente
    // ==> nichts zu tun!
  } else {
    // Verbleibender Array-Teil hat mehrere Elemente
    // ==> aufteilen
    int *part = partition(links, rechts);
    // part ist der Pointer auf das Teilungs-Element,
    // das weder zum linken noch zum rechten Teil gehört
    // Alle Elemente kleiner als das Element part sind links von part,
    // Alle Elemente größergleich dem Element part sind rechts von part
    // ==> Die beiden Teile links und rechts von part rekursiv sortieren
    quicksort(links, part - 1);
    quicksort(part + 1, rechts);
  }
}

// sortiere das Array
void sort(int arr[], int anzahl)
{
  // Quicksort über das gesamte Array
  quicksort(&(arr[0]), &(arr[anzahl - 1]));
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
