// Erstes C++: Geom. Objekte: Umbau auf Rechteck
//
// Aufruf: rect
//
// Klaus Kusche, 2020

#include <cstdlib>
// Für time(...) im srand(...)
#include <ctime>

#include "sdlinterf.h"

using namespace std;

class Color
{
  public:
    // Rect initialisiert jetzt sein Color-Member in der Init-Liste
    // ==> Color braucht keinen Standard-Konstruktor mehr
    // ==> Wir können die Defaults weglassen
    Color(int r, int g, int b)  
    : mR(r), mG(g), mB(b)  // Init-Liste: Speichere die Parameter-Werte
                           // beim Anlegen des Objektes in den Member-Variablen
    {}

    int getR() const { return mR; }
    int getG() const { return mG; }
    int getB() const { return mB; }

  private:   
    int mR, mG, mB;
};

class Rect
{
  public:
    Rect(const Color &color, int x, int y, int w, int h,
          int sx = 0, int sy = 0)
    : mRGB(color), mX(x), mY(y), mW(w), mH(h), mSX(sx), mSY(sy)
        // x, y, w, h, sx und sy werden "normal" gespeichert
        // "mRGB(color)" ist ein Konstruktor-Aufruf
        // des (automatisch erzeugten) Kopier-Konstruktors der Klasse Color
        // weil unser Member mRGB ja selbst wieder ein Objekt ist.
        // Stünde das nicht in der Init-Liste,
        // würde für mRGB der Standard-Konstruktor aufgerufen
        // (oder es käme ein Compiler-Fehler,
        // wenn Color gar keinen Standard-Konstruktor hat).
    {
      draw();
    }
    ~Rect() { undraw(); }

    Color getColor() const { return mRGB; }
    int getX() const { return mX; }
    int getY() const { return mY; }
    int getW() const { return mW; }    // get-Methoden für die neuen Member
    int getH() const { return mH; }
    int getSX() const { return mSX; }
    int getSY() const { return mSY; }

    void setColor(const Color &color)
    {
      mRGB = color;
      draw();
    }

    void setSpeed(int sx, int sy)
    {
      mSX = sx; mSY = sy;
    }
    
    void setPos(int x, int y);
    void move(int dx, int dy);

    void setSize(int w, int h);     // set-Methode für die neuen Member

    // Neue Methode:
    // vergrößere / verkleinere ein Rechteck, Parameter in Prozent:
    // 100...gleichgroß, 50...halb so groß, 200... doppelt so groß
    void scale(int percentX, int percentY);

    bool fly(bool bounce = false);

    void draw();
    void undraw();

  private:
    Color mRGB;
    int mX, mY;  // Position des Mittelpunktes des Rechtecks
    // Jedes Rechteck merkt sich intern seine Breite und Höhe
    int mW, mH;  // Width und Height (jeweils ab Mittelpunkt, d.h. halber Wert)
    int mSX, mSY;
};

// Zur Wahl einer zufälligen Geschwindigkeit, die nicht 0 ist:
// Berechne eine Zufallszahl z von -n ... -1 oder 1 ... n (aber nicht 0)
inline int randPM(int n)
{
  // die erste große Klammer liefert 1...n,
  // und die zweite große Klammer liefert 0 oder (n+1)
  return ((rand() % n) + 1) - ((rand() % 2) * (n + 1));
}

int main(void)
{
  srand(time(nullptr));

  sdlInit();

  { 
    Rect r(Color(255, 255, 255), SDL_X_SIZE / 2, SDL_Y_SIZE / 2, 10, 25, 5, 2);

    for (;;) {
      sdlMilliSleep(20);
      // Bei jedem Richtungswechsel: Schrumpfe das Rechteck um 10 %
      if (!r.fly(true)) {
        r.scale(90, 90);
        // Wenn das Rechteck Breite oder Höhe 0 hat:
        // Wieder in die Mitte setzen, zufällige Größe und Geschwindiogkeit geben
        if ((r.getW() == 0) || (r.getH() == 0)) {
          r.setPos(SDL_X_SIZE / 2, SDL_Y_SIZE / 2);
          r.setSize(rand() % 30 + 1, rand() % 30 + 1);
          r.setSpeed(randPM(10), randPM(10));
        }
      }
      sdlUpdate();
    } 
  }

  sdlExit();

  exit(EXIT_SUCCESS);
}

void Rect::setPos(int x, int y)
{
  undraw();
  mX = x;
  mY = y;
  draw();
}

void Rect::move(int dx, int dy)
{
  undraw();
  mX += dx;
  mY += dy;
  draw();
}

// analog zu setPos: Weglöschen, interne Größe ändern, neu zeichnen
void Rect::setSize(int w, int h)
{
  undraw();
  mW = w;
  mH = h;
  draw();
}

// analog zu setSize, mit anderer Größen-Rechnung
void Rect::scale(int percentX, int percentY)
{
  undraw();
  // Achtung: Zuerst multiplizieren, dann dividieren!
  // Sonst kommt auf Grund der abschneidenden int-Division
  // bei den meisten Verkleinerungen 0 heraus!
  mW = (mW * percentX) / 100;
  mH = (mH * percentY) / 100;
  draw();
}
  
bool Rect::fly(bool bounce)
{
  bool ret = true;
  // Das Rechteck darf nicht fliegen, bis der Mittelpunkt am Rand ansteht,
  // sondern steht schon an, wenn der Mittelpunkt noch mW vom Rand entfernt ist
  if (((mSX > 0) && (mX >= SDL_X_SIZE - mSX - mW)) ||
      ((mSX < 0) && (mX < -mSX + mW))) {
    if (bounce) {
      mSX = -mSX;
      ret = false;
    }
    else {
      return false;
    }
  }
  // analog für mH als Sicherheitsabstand
  if (((mSY > 0) && (mY >= SDL_Y_SIZE - mSY - mH)) ||
      ((mSY < 0) && (mY < -mSY + mH))) {
    if (bounce) {
      mSY = -mSY;
      ret = false;
    }
    else {
      return false;
    }
  }

  move(mSX, mSY);
  return ret;
}

void Rect::draw()
{
  // Rechteck statt Punkt zeichnen,
  // mit der Breite und Höhe des eigenen Objektes
  sdlDrawRect(mX, mY, mW, mH, mRGB.getR(), mRGB.getG(), mRGB.getB());
}

void Rect::undraw()
{
  sdlDrawRect(mX, mY, mW, mH, 0, 0, 0);
}
