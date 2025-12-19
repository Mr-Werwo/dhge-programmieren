// Geom. Objekte: Zusammengesetzte Objekte
// Header der abgeleiteten Klasse "Comp" für zusammengesetzte Objekte
//
// Klaus Kusche, 2020

#ifndef _COMP_H
#define _COMP_H

#include "graobj.h"

class Comp : public GraObj
{
  public:
    Comp(int x, int y, int sx, int sy, int maxObjCnt) :
      // Basisklassen-Konstruktor aufrufen:
      // Farbe ist irrelevant (wir speichern scharz im Objekt)
      // Position und Geschwindigkeit wie angegeben, Breite und Höhe noch 0 
      GraObj(Color(0, 0, 0), x, y, 0, 0, sx, sy),
      // dyn. Array für Subobjekt-Pointer gleich in Init-Liste anlegen  
      mObjCnt(0), mMaxObjCnt(maxObjCnt), mObjArr(new GraObj *[maxObjCnt])
      {}  // noch keine Objekte vorhanden ==> kein draw notwendig
    
    Comp(const Comp &orig);   // Implementierung im .cpp
    
    Comp &operator=(const Comp &r) = delete;
    
    virtual ~Comp();          // Implementierung im .cpp

    virtual Comp *clone() const override {
      return new Comp(*this);
    }

    // füge ein Objekt (bzw. einen Klon davon) zum eigenen Objekt hinzu
    // Ergebnis: Erfolg (false, wenn das Objekt schon voll ist)
    bool add(const GraObj &obj);

    virtual void setPos(int x, int y) override;
    virtual void move(int dx, int dy) override;
    virtual void setSize(int w, int h) override;
    virtual void scale(int percentX, int percentY) override;

    virtual void draw() override;
    virtual void undraw() override;

  protected:
    int mObjCnt;        // aktuelle Anzahl von Subobjekten
    int mMaxObjCnt;     // maximale Anzahl von Subobjekten (Array-Größe)
    // Pointer auf dynamisch angelegtes Array von Pointern auf die Subobjekte
    GraObj **mObjArr;

    // nichtöffentliche Methode:
    // Nur zur internen Verwendung in dieser und davon abgeleiteten Klassen
    void recalcSize();  // berechnet und setzt eigenes mW und mH neu
};

#endif
