// Kleines Grafik-Demo-Beispiel: Zufällige Linien
//
// Aufruf: demo1 anzahl
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s anzahl\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int anzahl = atoi(argv[1]);

  srand(time(NULL));

  sdlInit();       // mach das Grafik-Fenster auf
  sdlSetBlack();   // mach alle Pixel schwarz

  for (; anzahl > 0; --anzahl) {
    sdlDrawLine(
      rand() % SDL_X_SIZE,  // Anfangs-X-Koordinate, 0 ... SDL_X_SIZE - 1
      rand() % SDL_Y_SIZE,  // Anfangs-Y-Koordinate, 0 ... SDL_Y_SIZE - 1
      rand() % SDL_X_SIZE,  // End-X-Koordinate, 0 ... SDL_X_SIZE - 1
      rand() % SDL_Y_SIZE,  // End-Y-Koordinate, 0 ... SDL_Y_SIZE - 1
      rand() % 256,         // Farb-Rot-Anteil, 0 ... 255
      rand() % 256,         // Farb-Grün-Anteil, 0 ... 255
      rand() % 256);        // Farb-Blau-Anteil, 0 ... 255
  }

  sdlUpdate();          // zeige die gezeichneten Striche wirklich an
  sdlMilliSleep(3000);  // warte vor Beenden des Programms 3 Sekunden 
  sdlExit();            // mach das Grafikfenster wieder zu

  exit(EXIT_SUCCESS);
}
