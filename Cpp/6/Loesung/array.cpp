// Einfache Array-Klasse, Array-Klasse mit Zugriffszähler
//
// Klaus Kusche, 2011

#include <iostream>
// wir verwenden pow
#include <cmath>

using namespace std;

class Array
{
  public:
    Array(unsigned int sz) : size(sz), data(new double[sz]) {}
    Array(const Array &a);

    virtual ~Array() {
      delete[] data;
    }

    virtual unsigned int getSize() { return size; }
    virtual double getVal(unsigned int index);
    virtual bool setVal(unsigned int index, double val);
    virtual void setAll(double val);
    virtual void print();
    
    // Zuweisung von Array-Objekten verhindern
    Array &operator= (const Array &a) = delete;
  
  private:
    unsigned int size;
    double *data;
};

Array::Array(const Array &a) : size(a.size), data(new double[size])
{
  for (unsigned int i = 0; i < size; ++i) {
    data[i] = a.data[i];
  }
}

double Array::getVal(unsigned int index)
{
  if (index < size) {
    return data[index];
  } else  {
    return 0;
  }
}

bool Array::setVal(unsigned int index, double val)
{
  if (index < size) {
    data[index] = val;
    return true;
  } else {
    return false;
  }
}

void Array::setAll(double val)
{
  for (unsigned int i = 0; i < size; ++i) {
    data[i] = val;
  }
}

void Array::print()
{
  for (unsigned int i = 0; i < size; ++i) {
    cout << data[i] << ' ';
  }
  cout << endl;
}

class StatArray : public Array
{
  public:
    StatArray(unsigned int sz) : Array(sz), wriCnt(0) {}
    StatArray(const StatArray &a) : Array(a), wriCnt(0) {}

    virtual bool setVal(unsigned int index, double val)
    {
      ++wriCnt;
      return Array::setVal(index, val);
    }

    unsigned int getWriCnt() { return wriCnt; }
    
  private:
    unsigned int wriCnt;
};

StatArray Accumulate(StatArray a);

int main()
{
  StatArray *a = new StatArray(12);

  a->setAll(1);
  cout << "a am Anfang: ";
  a->print();

  StatArray b = *a;

  cout << "b am Anfang: ";
  b.print();

  for (unsigned int i = 0; i < b.getSize(); ++i) {
    b.setVal(i, pow(2, i));
  }
  
  a->setVal(0, 0);
  cout << "a nach " << a->getWriCnt() << " Änderungen: ";
  a->print();
  delete a;

  StatArray c = b;
  cout << "b nach " << b.getWriCnt() << " Änderungen: ";
  b.print();
  cout << "Kopie davon (" << c.getWriCnt() << " Änderungen): ";
  c.print();

  StatArray d = Accumulate(b);
  cout << "Ergebnis von Accumulate (" << d.getWriCnt() << " Änderungen): ";
  d.print();
  
  cout << "b nach Accumulate (" << b.getWriCnt() << " Änderungen): ";
  b.print();
  
  return 0;
}

// Returniere ein neues Array-Objekt, in dem das i-te Element
// die Summe aller Elemente bis incl. i-tem Element im alten Array ist
// Parameter a wird "by Value" übergeben
// ==> a ist eine Kopie des Array-Objektes im Aufrufer
// und kann lokal modifiziert werden
StatArray Accumulate(StatArray a)
{
  double sum = 0;

  for (unsigned int i = 0; i < a.getSize(); ++i) {
    sum += a.getVal(i);
    a.setVal(i, sum);
  }
  
  return a;
}
