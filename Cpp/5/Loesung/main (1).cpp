// C++: Inventarliste, mit Kopieren
//
// Hauptprogramm
//
// Klaus Kusche, 2011

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

#include "inventar.h"
#include "comp.h"
#include "zubeh.h"

const int MAX_INV = 1000;  // Max. Zahl von Einträgen
Inventar *list[MAX_INV];   // Inventarliste (gelöschte Elemente sind nullptr)
int nextListPos = 0;       // Erste freie / unbenutzte Position in list

int getEntry();

// Frag den Benutzer nach einer Inventarnummer
// und suche das entsprechende Gerät in list
// Returnwert wenn es gefunden wird: Index des Gerätes in list
// Returnwert wenn es nicht gefunden wird: nextListPos (erster freier Eintrag)
int getEntry()
{
  int i;
  int nummer;

  cout << "Inventarnummer? ";
  cin >> nummer;

  for(i = 0; i < nextListPos; ++i) {
    if ((list[i] != nullptr) && (list[i]->getInvNr() == nummer)) return i;
  }
  cout << "Nicht gefunden!" << endl;
  return i;
}

int main()
{
  int code;
  int i;

  for (;;) {
    cout << "\n0 Ende\n"
            "1 Inventareintrag löschen\n"
            "2 Zubehör eintragen\n"
            "3 Computer eintragen\n"
            "4 letztes Gerät kopieren\n"
            "5 beliebiges Gerät kopieren\n"
            "10 Gesamtliste + GesamtWert\n"
            "11 Gerät anzeigen\n"
            "12 Wert berichtigen\n"
            "13 Computer RAM/Disk ändern\n"
            "14 Preis RAM/Disk ändern\n"
            "15 Summe Computer / RAM / Disk\n"
            "==> ";
    cin >> code;
    cout << endl;
    switch (code) {
      case 0: exit(EXIT_SUCCESS); break;
      case 1:
        i = getEntry();
        if (i < nextListPos) {
          delete list[i];
          list[i] = nullptr;          
        }
        break;
      case 2:
        if (nextListPos == MAX_INV) {
          cout << "Liste voll!" << endl;
        } else {
          string name;
          double wert;
          cout << "Name des Gegenstandes? ";
          cin >> name;
          cout << "Wert des Gegenstandes? ";
          cin >> wert;
          list[nextListPos] = new Zubeh(name, wert);
          list[nextListPos]->print();
          ++nextListPos;
        }
        break;
      case 3:
        if (nextListPos == MAX_INV) {
          cout << "Liste voll!" << endl;
        } else {
          string name;
          double wert;
          int ram, disk;
          cout << "Name des Computers? ";
          cin >> name;
          cout << "Wert des Grundgerätes? ";
          cin >> wert;
          cout << "GB RAM? ";
          cin >> ram;
          cout << "GB Disk? ";
          cin >> disk;
          list[nextListPos] = new Comp(name, wert, ram, disk);
          list[nextListPos]->print();
          ++nextListPos;
        }
        break;
      case 4:
        if (nextListPos == MAX_INV) {
          cout << "Liste voll!" << endl;
        } else if (nextListPos == 0) {
          cout << "Noch kein Gerät angelegt?" << endl;
        } else if (list[nextListPos - 1] == nullptr) {
          cout << "Voriges Gerät ist schon gelöscht!" << endl;
        } else {
          list[nextListPos] = list[nextListPos - 1]->clone();
          list[nextListPos]->print();
          ++nextListPos;
        }
        break;
      case 5:
        if (nextListPos == MAX_INV) {
          cout << "Liste voll!" << endl;
        } else {
          i = getEntry();
          if (i < nextListPos) {
            list[nextListPos] = list[i]->clone();
            list[nextListPos]->print();
            ++nextListPos;
          }
        }
        break;
      case 10:
        {
          double summe = 0;
          for(i = 0; i < nextListPos; ++i) {
            if (list[i] != nullptr) {
              list[i]->print();
              summe += list[i]->getValue();
            }
          }
          cout << "*** Gesamtwert: " << summe << endl;
        }
        break;
      case 11:
        i = getEntry();
        if (i < nextListPos) {
          list[i]->print();
        }
        break;
      case 12:
        i = getEntry();
        if (i < nextListPos) {
          double wert;
          list[i]->print();
          cout << "Neuer Wert? ";
          cin >> wert;
          list[i]->setValue(wert);
          list[i]->print();
        }
        break;
      case 13:
        i = getEntry();
        if (i < nextListPos) {
          if (list[i]->isComp()) {
            int ram, disk;
            Comp *comp = (Comp *)(list[i]);
            cout << "Bisher " << comp->getRamGB() << " GB RAM. Zusätzliches RAM (GB)? ";
            cin >> ram;
            cout << "Bisher " << comp->getDiskGB() << " GB Disk. Zusätzliches RAM (GB)? ";
            cin >> disk;
            comp->addRamGB(ram);
            comp->addDiskGB(disk);
            comp->print();
          } else {
            cout << "Das ist kein Computer!" << endl;
          }
        }
        break;
      case 14:
        {
          double ram, disk;
          cout << "Bisheriger RAM-Preis " << Comp::getRamValPerGB() << " pro GB. Neuer Preis? ";
          cin >> ram;
          cout << "Bisheriger Disk-Preis " << Comp::getDiskValPerGB() << " pro GB. Neuer Preis? ";
          cin >> disk;
          Comp::setRamValPerGB(ram);
          Comp::setDiskValPerGB(disk);
        }
        break;
      case 15:
        cout << "Anzahl Computer: " << Comp::getCompCount() << endl;
        cout << "Gesamtmenge RAM: " << Comp::getTotalRamGB() << endl;
        cout << "Gesamtkapazität Disk: " << Comp::getTotalDiskGB() << endl;
        break;
      default:
        cout << "???" << endl;
        break;
    }
  }
}
