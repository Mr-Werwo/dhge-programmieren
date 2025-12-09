// Kleines Grafik-Beispiel: Stern
//
// Aufruf: weihn-stern
//
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  // Koordinaten des Fenster-Mittelpunktes
  const int mitteX = SDL_X_SIZE / 2;  
  const int mitteY = SDL_Y_SIZE / 2;

  sdlInit();
  sdlSetBlack();
  
  for (int i = 5, j = 255; i <= 255 ; i += 10, j -= 10) {
    // i zählt 5, 15, 25, ... 255
    // j läuft genau gegengleich zu i: 255, 245, 235, ... 5
    // Linie 1: Linkes oberes Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX - i, mitteY, mitteX, mitteY - j, i, 255, j);
    // Linie 2: Rechtes oberes Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX + i, mitteY, mitteX, mitteY - j, i, 255, j);
    // Linie 3: Linkes unteres Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX - i, mitteY, mitteX, mitteY + j, i, 255, j);
    // Linie 4: Rechtes unteres Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX + i, mitteY, mitteX, mitteY + j, i, 255, j);
    // und jetzt noch einmal so ähnlich für den diagonalen Stern
    sdlDrawLine(mitteX - i, mitteY - i, mitteX + j, mitteY - j, i, 0, j);
    sdlDrawLine(mitteX - i, mitteY - i, mitteX - j, mitteY + j, i, 0, j);
    sdlDrawLine(mitteX + i, mitteY + i, mitteX + j, mitteY - j, i, 0, j);
    sdlDrawLine(mitteX + i, mitteY + i, mitteX - j, mitteY + j, i, 0, j);
    // bei jedem Umlauf anzeigen, nicht erst am Schluss!
    sdlUpdate();
    // vor den nächsten Linien: 50 ms warten
    sdlMilliSleep(50);
  }

  sdlMilliSleep(1000);

  // dasselbe noch einmal, aber mit Farbe schwarz, löscht den Stern wieder 
  for (int i = 5, j = 255; i <= 255 ; i += 10, j -= 10) {
    // i zählt 5, 15, 25, ... 255
    // j läuft genau gegengleich zu i: 255, 245, 235, ... 5
    // Linie 1: Linkes oberes Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX - i, mitteY, mitteX, mitteY - j, 0, 0, 0);
    // Linie 2: Rechtes oberes Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX + i, mitteY, mitteX, mitteY - j, 0, 0, 0);
    // Linie 3: Linkes unteres Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX - i, mitteY, mitteX, mitteY + j, 0, 0, 0);
    // Linie 4: Rechtes unteres Viertel, erst fast senkrecht, dann immer mehr liegend
    sdlDrawLine(mitteX + i, mitteY, mitteX, mitteY + j, 0, 0, 0);
    // und jetzt noch einmal so ähnlich für den diagonalen Stern
    sdlDrawLine(mitteX - i, mitteY - i, mitteX + j, mitteY - j, 0, 0, 0);
    sdlDrawLine(mitteX - i, mitteY - i, mitteX - j, mitteY + j, 0, 0, 0);
    sdlDrawLine(mitteX + i, mitteY + i, mitteX + j, mitteY - j, 0, 0, 0);
    sdlDrawLine(mitteX + i, mitteY + i, mitteX - j, mitteY + j, 0, 0, 0);
    // bei jedem Umlauf anzeigen, nicht erst am Schluss!
    sdlUpdate();
    // vor den nächsten Linien: 50 ms warten
    sdlMilliSleep(50);
  }

  sdlMilliSleep(1000);
  sdlExit();

  exit(EXIT_SUCCESS);
}
