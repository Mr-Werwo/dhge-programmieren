// C++: Inventarliste, mit zusammengesetztem Objekt
//
// Abgeleitete Klasse Comp (Computer), Header
//
// Klaus Kusche, 2011

#ifndef _COMP_H
#define _COMP_H

#include <string>

using namespace std;

#include "inventar.h"

class Comp : public Inventar
{
  public:
    Comp(string name, double baseValue, int ramGB, int diskGB) :
      Inventar(name), mBaseValue(baseValue), mRamGB(ramGB), mDiskGB(diskGB) {
      ++MCompCount;
      MTotalRamGB += mRamGB;
      MTotalDiskGB += mDiskGB;
    }
    Comp(const Comp &orig) :
      Inventar(orig),
      mBaseValue(orig.mBaseValue), mRamGB(orig.mRamGB), mDiskGB(orig.mDiskGB) {
      ++MCompCount;
      MTotalRamGB += mRamGB;
      MTotalDiskGB += mDiskGB;
    }
    virtual ~Comp() {
      --MCompCount;
      MTotalRamGB -= mRamGB;
      MTotalDiskGB -= mDiskGB;
    }

    virtual double getValue() {
      return mBaseValue + mRamGB * MRamValPerGB + mDiskGB * MDiskValPerGB;
    }
    virtual void setValue(double value) { mBaseValue = value; }
    virtual void print();

    virtual Comp* clone() const { return new Comp(*this); }

    int getRamGB() { return mRamGB; }
    int getDiskGB() { return mDiskGB; }
    void addRamGB(int ramGB) {
      MTotalRamGB += ramGB; mRamGB += ramGB;
    }
    void addDiskGB(int diskGB) {
      MTotalDiskGB += diskGB; mDiskGB += diskGB;
    }

    // statische Member ==> statische Methoden!
    static int getCompCount() { return MCompCount; }
    static int getTotalRamGB() { return MTotalRamGB; }
    static int getTotalDiskGB() { return MTotalDiskGB; }
    static double getRamValPerGB() { return MRamValPerGB; }
    static double getDiskValPerGB() { return MDiskValPerGB; }
    static void setRamValPerGB(double val) { MRamValPerGB = val; }
    static void setDiskValPerGB(double val) { MDiskValPerGB = val; }

  protected:
    double mBaseValue;
    int mRamGB;
    int mDiskGB;

  private:
    static int MCompCount;
    static int MTotalRamGB;
    static int MTotalDiskGB;

  protected:
    static double MRamValPerGB;
    static double MDiskValPerGB;
};

#endif
