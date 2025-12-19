// Geom. Objekte: Vererbung und "clone"
// Header für abgeleitete Klasse "Circ"
//
// Klaus Kusche, 2020

#ifndef _CIRC_H
#define _CIRC_H

// Header der Basisklasse inkludieren (der inkludiert auch color.h)
#include "graobj.h"

class Circ : public GraObj
{
  public:
    Circ(const Color &color, int x, int y, int w, int h,
         int sx = 0, int sy = 0)
    // Konstruktor der Basisklasse aufrufen
    // Alle Member sind in der Basisklasse
    // ==> Müssen vom Konstruktor der Basisklasse initialisiert werden
    : GraObj(color, x, y, w, h, sx, sy)  
    {
      draw();
    }
    // analog: Copy-Konstruktor ruft Copy-Konstruktor der Basisklasse auf
    // (in diesem Fall den impliziten)
    Circ(const Circ &orig) : GraObj(orig)
    {
      draw();
    }

    virtual ~Circ() { undraw(); }

    // nur die in dieser Klasse überschriebenen Methoden angeben!
    // Der Returntyp von clone ist Circ* statt GraObj*
    // da wir ja in dieser Klasse immer ein Circ kopieren
    // "override" (seit C++11) ist optional und heißt
    // "Diese Methode muss eine Methode der Basisklasse überschreiben"
    // (gib einen Fehler aus, wenn es eine "neue" Methode ist)
    virtual Circ *clone() const override {
      // Standard-Implementierung, immer gleich
      // ein neues Objekt anlegen mittels Copy-Konstruktor des eigenen Objektes
      // this ist ein Pointer auf das eigene Objekt, *this ist das Objekt selbst
      return new Circ(*this);
    }
    
    virtual void draw() override;
    virtual void undraw() override;
};

#endif
