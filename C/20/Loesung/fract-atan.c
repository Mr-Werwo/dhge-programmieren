// Fraktale, ganz primitiv, mit Winkel-Färbung
//
// Aufruf: fract-atan xcenter ycenter xparam yparam limit type zoom zStep zEnd
// 
// Klaus Kusche, 2010

#include "sdlinterf.h"

#include <stdio.h>
#include <stdlib.h>
// Nur bei Winkel-Färbung für atan2
#include <math.h>

int main(int argc, const char *argv[])
{
  const char hilfe[] =
    "Aufruf: %s xcenter ycenter xparam yparam limit type zoom zStep zEnd\n"
    "xcenter X coordinate of screen center, -2 <= xcenter <= 2\n"
    "ycenter Y coordinate of screen center, -2 <= ycenter <= 2\n"
    "xconst  X constant value of fractal algorithm, -2 <= xconst <= 2\n"
    "yconst  Y constant value of fractal algorithm, -2 <= yconst <= 2\n"
    "limit   iteration limit for the fractal algorithm, 1 <= limit <= 10000\n"
    "type    type of algorithm: 0 ... Julia, 1 ... Mandelbrot\n"
    "zoom    initial zoom factor, >= 1\n"
    "zStep   zoom step factor, > 1\n"
    "zEnd    final zoom limit, >= 1\n";

  if (argc != 10) {
    fprintf(stderr, hilfe, argv[0]);
    exit(EXIT_FAILURE);
  }

  // siehe Hilfetext
  double xcenter = atof(argv[1]);
  double ycenter = atof(argv[2]);
  double xconst = atof(argv[3]);
  double yconst = atof(argv[4]);
  int limit = atoi(argv[5]);
  int type = atoi(argv[6]);
  double zoom = atof(argv[7]);
  double zoomStep = atof(argv[8]);
  double zoomEnd = atof(argv[9]);
  if ((xcenter < -2.0) || (xcenter > 2.0) ||
      (ycenter < -2.0) || (ycenter > 2.0) ||
      (xconst < -2.0) || (xconst > 2.0) ||
      (yconst < -2.0) || (yconst > 2.0) ||
      (limit < 1) || (limit > 10000) ||
      (type < 0) || (type > 1) ||
      (zoom < 1.0) || (zoomStep <= 1.0) || (zoomEnd < 1.0)) {
    fprintf(stderr, hilfe, argv[0]);
    exit(EXIT_FAILURE);
  }
  
  sdlInit();                    // Grafikfenster aufmachen

  // Größe des Fensters in Pixel, in der kleineren Richtung
  const int pixel = (SDL_X_SIZE < SDL_Y_SIZE) ? SDL_X_SIZE : SDL_Y_SIZE;

  // Zoom-Schleife:
  // "Haupt-Schleifen-Variable" zoom
  // "Zweit-Schleifen-Zähler" f: Für Farbänderung bei jedem Zoom-Schritt
  for (int f = 0; zoom <= zoomEnd; f += 2, zoom *= zoomStep) {
    // für jeden neuen Zoom-Faktor: Komplettes Bild neu rechnen
    sdlSetBlack();              // alle Pixel schwarz machen
    for (int x = 0; x < SDL_X_SIZE; ++x) {
      for (int y = 0; y < SDL_Y_SIZE; ++y) {
        // für alle Pixel:
        // Pixelkoordinaten auf mathematische Koordinaten umrechnen
        double xpos = xcenter + (4 * (x - SDL_X_SIZE / 2)) / (pixel * zoom);
        double ypos = ycenter + (4 * (y - SDL_Y_SIZE / 2)) / (pixel * zoom);
        double zx, zy;     // real und imag von zn aus der Folge
        double cx, cy;     // real und imag von c aus der Folge
        // bei Mandelbrot und Julia sind Anfangswert und Konstante vertauscht
        if (type == 0) {
          zx = xpos; zy = ypos; cx = xconst; cy = yconst;
        } else {
          cx = xpos; cy = ypos; zx = xconst; zy = yconst;
        }
        for (int i = 0; i < limit; ++i) {
          if (zx * zx + zy * zy >= 4) {
            // Punkt fällt nach i Schritten aus dem Kreis: Bunt machen
            // Alternative mit Winkel-Farbe:
            // atan2(y,x) liefert den Winkel des Punktes x,y von 0,0 aus
            // und zwar in Radiant (von -Pi bis +Pi) ==> umrechnen auf 0-191
            sdlDrawCyclicPoint(x, y, 
                               (int)((atan2(zy, zx) / M_PI + 1) * 96) + f);
            break;
          }
          // real und imag von zn^2 aus der Folge
          double zxpwr = zx * zx - zy * zy;
          double zypwr = 2 * zx * zy;
          // Alternativen mit höheren Potenzen:
          // hoch 3
          //double zx_2 = zx * zx;
          //double zy_2 = zy * zy;
          //double zxpwr = zx * (zx_2 - 3 * zy_2);
          //double zypwr = zy * (3 * zx_2 - zy_2);
          // hoch 5
          //double zx_2 = zx * zx;
          //double zy_2 = zy * zy;
          //double zx_4 = zx_2 * zx_2;
          //double zy_4 = zy_2 * zy_2;
          //double zxpwr = zx * (zx_4 - 10 * zx_2 * zy_2 + 5 * zy_4);
          //double zypwr = zy * (5 * zx_4 - 10 * zx_2 * zy_2 + zy_4);
          zx = zxpwr + cx; zy = zypwr + cy;
        } // Ende for für die zn-Folge 
      } // Ende y-for
    } // Ende x-for
    sdlUpdate(); // alle Pixel im Fenster aktualisieren
  } // Ende zoom-for, d.h. Ende eines ganzen Bildes

  sdlExit();

  exit(EXIT_SUCCESS);
}
