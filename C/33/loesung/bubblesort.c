// Bubblesort
//
// Aufruf: bubblesort z1 z2 z3 ...
// 
// Klaus Kusche, 2010

#include <stdio.h>
#include <stdlib.h>

// Sortieren von n Elementen a[0] bis a[n-1] durch Austauschen (Bubblesort)
//
// Idee:
// Vertausche in jedem Durchlauf falsch sortierte benachbarte Elemente
// bis keine Vertauschungen mehr stattfinden
//
// Optimierung:
// Merke dir in jedem Durchlauf den hintersten Austausch:
// Weiter nach hinten musst du in folgenden Durchläufen nicht mehr gehen,
// weil dahinter schon alles stimmt
void bubblesort(int a[], int n)
{
  int limit = n - 1;  // Index des hintersten noch zu prüfenden Elements
                      
  while (limit > 0) { // limit == 0 ... nichts mehr zu prüfen
    int last = 0; // Index des hintersten Austausches im aktuellen Durchlauf
    for (int i = 0; i < limit; ++i) {
      if (a[i] > a[i + 1]) {
        int tmp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = tmp;
        last = i;
      }
    }
    // Hinterste Vertauschung im aktuellen Umlauf
    // = Ende der Schleife im nächsten Umlauf
    limit = last;
  }
}

int main(int argc, const char *argv[])
{
  int elems = argc - 1;  // Anzahl der zu sortierenden Werte
  // vorsichtshalber argc statt elems (d.h. 1 Element zu viel)
  // denn beim Aufruf ohne Werte wäre elems gleich 0,
  // und Arrays der Größe 0 sind verboten
  int array[argc];
         
  for (int i = 0; i < elems; ++i) {
    array[i] = atoi(argv[i + 1]);
  }

  bubblesort(array, elems);

  for (int i = 0; i < elems; ++i) {
    printf("%d ", array[i]);
  }
  putchar('\n');
  
  exit(EXIT_SUCCESS);
}
