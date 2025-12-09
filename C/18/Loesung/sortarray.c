// In einem Array sortiert einfügen / löschen
//
// Aufruf: sortarray
// (nichts auf der Befehlszeile, aber interaktive Eingabe)
// 
// Klaus Kusche, 2011

#include <stdio.h>
#include <stdlib.h>

// Größe unseres Arrays
#define SIZE 100

// Wir brauchen diesmal nichts von der Befehlszeile ==> void
int main(void)
{
  int data[SIZE];
  int used = 0;    // Anzahl der benutzten Elemente in data
                   // ist zugleich Index des ersten freien Elementes!
  int i, z;

  for (;;) {  // Schleife wird unten im else mit break verlassen
    
    printf("\nNeue Zahl (0 = Ende, -Zahl = Löschen)? ");
    scanf("%d", &z);
    
    if (z > 0) {  // Einfügen
      if (used == SIZE) {  // kein Platz mehr!
        printf("Die Zahl hat keinen Platz mehr!\n");
      } else {
        // Wir suchen von hinten nach vor die richtige Stelle:
        // Die ist unmittelbar hinter der ersten Zahl, die <= z ist
        // bzw. ganz vorne (i = 0), wenn alle Zahlen > z sind
        // Achtung: Die Reihenfolge im && ist zwingend so und nicht andersrum!
        // (data[i - 1] > z) && (i > 0) würde ev. auf data[-1] zugreifen!
        //
        // Und wir schieben die Zahlen dabei gleich 1 nach hinten:
        // i ist die Nummer des gerade freien Platzes!
        //
        // Wir brauchen i nach der Schleife,
        // also muss i vor dem for deklariert sein, nicht "for (int i = ..."
        for (i = used; (i > 0) && (data[i - 1] > z); --i) {
          data[i] = data[i - 1];
        }
        data[i] = z;  // die neue Zahl kommt in den freien Platz
        ++used;       // die Zahlen sind 1 mehr geworden
      }
    } else if (z < 0) {  // Löschen
      z = -z;  // Die entsprechende positive Zahl suchen
      // Wir müssen suchen, solange wir nicht am Ende sind,
      // und solange die aktuelle Zahl kleiner als die gesuchte ist.
      for (i = 0; (i < used) && (data[i] < z); ++i) {}
      // Jetzt gibt es 3 Möglichkeiten:
      // i == used: Alle Zahlen durchsucht, nicht gefunden
      // data[i] == z: Gefunden
      // data[i] > z: z hätte schon vor data[i] kommen müssen ==> nicht gefunden
      if ((i < used) && (data[i] == z)) {
        --used;   // die Zahlen werden 1 weniger
        // alle Zahlen dahinter eins nach vor schieben!
        // i ist die Nummer des freien Platzes (der gelöschten Zahl)
        for ( ; i < used; ++i) {  
          data[i] = data[i + 1];
        }
      } else {
        printf("Die Zahl wurde nicht gefunden!\n");
      }
    } else {   // z == 0: Ende
      break;
    }

    // Inhalt des Arrays ausgeben
    for (i = 0; i < used; ++i) {
      printf("%d ", data[i]);
    }
  }
  
  exit(EXIT_SUCCESS);
}
