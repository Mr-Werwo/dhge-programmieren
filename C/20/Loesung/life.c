// Game of Life
//
// Aufruf: life geburtsfaktor
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Die beiden folgenden Arrays sind in Summe rund 4 MB groß
// (2 Arrays * 600*800 Elemente * 4 Bytes pro int)
// Unter Windows ist die Grenze für die Variablen einer Funktion aber 0.5 oder 1 MB
// ==> Das Programm stürzt wegen eventuell Stacküberlauf ab.
// Globale Variablen können hingegen in Summe zumindest 1 GB groß werden
// ==> Arrays global statt lokal machen!
// Unter Linux ist die Stack-Größe meist auf 8 MB eingestellt,
// dort könnte man die Arrays also in main deklarieren,
// solange man das Fenster nicht größer macht.
//
// Man kann auch char (1 Byte) statt int (4 Byte) verwenden:
// ein char ist ein kleiner int (je nach System 0 bis 255 oder -128 bis 127),
// und das reicht für dieses Beispiel: Wir brauchen nur 0 bis 8.
// char spart Platz und macht das Programm etwas schneller,
// weil die Arrays dann besser in den Prozessor-Cache passen!
//int leben[SDL_X_SIZE][SDL_Y_SIZE];     // Zelle lebt: 1  Zelle ist tot: 0
//int nachbarn[SDL_X_SIZE][SDL_Y_SIZE];  // Anzahl der lebenden Nachbarn
char leben[SDL_X_SIZE][SDL_Y_SIZE];     // Zelle lebt: 1  Zelle ist tot: 0
char nachbarn[SDL_X_SIZE][SDL_Y_SIZE];  // Anzahl der lebenden Nachbarn


int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s geburtsfaktor\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Im Mittel entsteht in einer toten Zelle durch Zufall
  // mit Wahrscheinlichkeit 1/gebFaktor neues Leben
  int gebFaktor = atoi(argv[1]);

  srand(time(NULL));

  // Initialisierung (1. Generation)
  for (int x = 0; x < SDL_X_SIZE; ++x) {
    for (int y = 0; y < SDL_Y_SIZE; ++y) {
      if ((x == 0) || (y == 0) ||
          (x == SDL_X_SIZE - 1) || (y == SDL_Y_SIZE - 1)) {
        // Pixel ist am Rand, Rand ist tot
        leben[x][y] = 0;
      } else {
        // Innenbereich wird zufällig zu 50 % mit Leben gefüllt
        leben[x][y] = rand() % 2;
      }
    }
  }

  sdlInit();

  for (;;) { // endlos
    sdlSetBlack();

    // 1. Schritt: Zähle die lebenden Nachbarn (nicht für Zellen am Rand!)
    for (int x = 1; x < SDL_X_SIZE - 1; ++x) {
      for (int y = 1; y < SDL_Y_SIZE - 1; ++y) {
        nachbarn[x][y] = leben[x - 1][y] + leben[x - 1][y - 1] +
                         leben[x][y - 1] + leben[x + 1][y - 1] +
                         leben[x + 1][y] + leben[x + 1][y + 1] +
                         leben[x][y + 1] + leben[x - 1][y + 1];
      }
    }

    // 2. Schritt: Zeichne die lebenden Pixel (nicht für Zellen am Rand!)
    for (int x = 1; x < SDL_X_SIZE - 1; ++x) {
      for (int y = 1; y < SDL_Y_SIZE - 1; ++y) {
        if (leben[x][y] == 1) {
          // bisher lebende Zelle
          if ((nachbarn[x][y] == 2) || (nachbarn[x][y] == 3)) {
            // 2 oder 3 Nachbarn: Die Zelle bleibt am Leben (rot)
            sdlDrawPoint(x, y, 255, 0, 0);
          } else {
            // Zelle stirbt an Einsamkeit oder Überbevölkerung
            leben[x][y] = 0;
          }
        } else {
          // bisher tote Zelle
          if ((nachbarn[x][y] == 3) ||
              ((gebFaktor > 0) && (rand() % gebFaktor == 0))) {
            // 3 Nachbarn oder Zufall: Neues Leben entsteht (gelb)
            leben[x][y] = 1;
            sdlDrawPoint(x, y, 255, 255, 0);
          }
        }
      }
    }

    // zeichne alle Pixel der neuen Generation auf einmal
    sdlUpdate();
  }

  sdlExit();

  exit(EXIT_SUCCESS);
}
