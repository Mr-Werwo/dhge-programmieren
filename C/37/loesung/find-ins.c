// Funktionen: Zahlen sortiert und ohne Doppelte in ein Array einfügen
//
// Aufruf: find+ins z1 z2 z3 ...
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>

// Größe des Arrays (max. Anzahl von Zahlen)
#define ARR_SIZE 6

// Suche zahl in array, anzahl ist die Anzahl der Elemente in array.
int find(const int array[], int anzahl, int zahl);
// Füge zahl an der richtigen Stelle in das Array array ein.
int insert(int array[], int *anzahlP, int groesse, int zahl);
// Genau dasselbe, aber nur wenn noch nicht vorhanden
int insertNoDup(int array[], int *anzahlP, int groesse, int zahl);

// Suche zahl in array, anzahl ist die Anzahl der Elemente in array.
// Returnwert = Index von zahl in array oder -1 wenn zahl nicht gefunden wird.
int find(const int array[], int anzahl, int zahl)
{
  for (int i = 0; i < anzahl; ++ i) {
    if (array[i] == zahl) return i;
  }
  // Alle Elemente durchsucht, nichts gefunden...
  return -1;
}

// Füge zahl an der richtigen Stelle in das Array array ein.
// anzahlP ist die aktuelle Anzahl der Elemente im Array:
// Die aktuelle Anzahl der Elemente müssen wir
// in der Variable des *Aufrufers* hochzählen,
// also brauchen wir einen *Pointer* auf dessen Zähler!
// groesse ist die angelegte Groesse des Arrays
//   (Anzahl der Elemente, die Platz haben).
// Der Returnwert ist der Index der eingefügten Zahl bei Erfolg
// und -1, wenn das Array voll ist oder *anzahlP negativ ist.
int insert(int array[], int *anzahlP, int groesse, int zahl)
{
  if ((*anzahlP < 0) || (*anzahlP >= groesse)) return -1;

  int loch;
  // *anzahlP ist der Index des ersten unbenutzten Elementes im Array.
  // Schiebe dieses "Loch" nach vor
  // (bzw. zu große Elemente davor um 1 nach hinten),
  // solange es nicht ganz vorne ist
  // und das Element davor größer als das einzufügende Element ist.
  for (loch = *anzahlP; (loch > 0) && (array[loch - 1] > zahl); --loch) {
    array[loch] = array[loch - 1];
  }

  // Nach der Schleife ist loch die Nummer des "Loches" (leeren Elementes),
  // und dieses Loch wurde genau an die Stelle im Array geschoben,
  // wo die neue Zahl hingehört.
  array[loch] = zahl;
  ++(*anzahlP);  // erhöhe die Variable, auf die anzahlP zeigt, um 1
  
  return loch;
}

// Genau dasselbe,
// aber mit keinem Einfügen und Ergebnis -1,
// wenn zahl schon in array enthalten ist.
int insertNoDup(int array[], int *anzahlP, int groesse, int zahl)
{
  // anzahlP ist trickreich:
  // - find möchte die Zahl selbst, also *anzahlP
  // - insert möchte einen Pointer auf die Zahl
  //   Genau das ist anzahlP ohnehin schon, also weder & noch * !
  if (find(array, *anzahlP, zahl) != -1) {
    // es gibt die Zahl schon ==> nicht einfügen!
    return -1;
  }
  return insert(array, anzahlP, groesse, zahl);
}

int main(int argc, const char * argv[])
{  
  int zahlen[ARR_SIZE];
  int belegt = 0;   // Am Anfang enthält das Array kein Element.

  for (int i = 1; i < argc; ++i) {
    int z = atoi(argv[i]);
    // Wir müssen insert die Adresse von unserem belegt geben,
    // damit es belegt hochzählen kann.
    int pos = insertNoDup(zahlen, &belegt, ARR_SIZE, z);
    if (pos == -1) {
      printf("%d nicht eingefügt\n", z);
    } else {
      printf("%d an Stelle %d eingefügt\n", z, pos);
    }
  }
  
  for (int i = 0; i < belegt; ++i) {
    printf("%d ", zahlen[i]);
  }
  printf("\n(insges. %d Zahlen)\n", belegt);
  
  exit(EXIT_SUCCESS);
}
