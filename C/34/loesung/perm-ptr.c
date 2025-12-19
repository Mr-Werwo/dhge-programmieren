// Erzeugen aller Permutationen (Version mit Pointer-Arithmetik)
//
// Aufruf: perm-ptr anzahl
// 
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *left, int *right);
void reverse(int *left, int *right);
int *find_smaller(int first[], int *last);
int *find_larger(int first[], int *last, int x);
bool perm(int arr[], int anz);
void fill(int arr[], int anz);
void print(const int arr[], int anz);

// Vertauscht die Elemente, auf die left und right zeigen.
void swap(int *left, int *right)
{
  int tmp = *left;
  *left = *right;
  *right = tmp;
}

// Dreht die Reihenfolge der Elemente zwischen left und right um
// (jeweils einschließlich Element left und right)
void reverse(int *left, int *right)
{
  for ( ; left < right; ++left, --right) {
    swap(left, right);
  }
}

// Liefert einen Pointer auf das erste Element von hinten,
// das kleiner als das Element dahinter ist,
// oder NULL, wenn es kein solches Element gibt.
// first zeigt auf den Anfang des Arrays,
// last ist ein Pointer auf das letzte Element des Arrays
int *find_smaller(int first[], int *last)
{
  // wir beginnen beim Vorletzten, weil der Letzte hat keinen Nachfolger
  for (int *p = last - 1; p >= first; --p) {
    if (*p < *(p + 1)) {
      return p;
    }
  }
  return NULL;
}

// Liefert einen Pointer auf das erste Element von hinten,
// das größer als x ist, 
// oder NULL, wenn es kein solches Element gibt.
// first zeigt auf den Anfang des Arrays,
// last ist ein Pointer auf das letzte Element des Arrays
int *find_larger(int first[], int *last, int x)
{
  for (int *p = last; p >= first; --p) {
    if (*p > x) {
      return p;
    }
  }
  return NULL;
}

// Erzeugt die nächste Permutation im Array arr.
// anz ist die Anzahl der Elemente in arr.
// Returnwert true bei Erfolg,
// false wenn arr schon die letzte Permutation enthält.
bool perm(int arr[], int anz)
{
  int *last = &(arr[anz - 1]);  // Pointer auf das letzte Element des Arrays

  int *left = find_smaller(arr, last);
  if (left == NULL) return false;
  int *right = find_larger(arr, last, *left); // das sollte nie NULL liefern!

  swap(left, right);
  reverse(left + 1, last);
  return true;
}

// Füllt das Array arr (anz Elemente) aufsteigend mit den Zahlen 1 bis anz.
void fill(int arr[], int anz)
{
  // Da wir hier i+1 als Zahl brauchen,
  // würde ein Umbau auf Pointer keinen Nutzen bringen
  for (int i = 0; i < anz; ++i) {
    arr[i] = i + 1;  // Index von 0 bis anz-1, Zahlen von 1 bis anz
  }
}

// Gibt das Array arr (anz Elemente) aus.
void print(const int arr[], int anz)
{
  // Ein Pointer in ein const-Array muss const sein
  for (const int *p = arr; p < arr + anz; ++p) {
    printf("%d ", *p);
  }
  printf("\n");
}

int main(int argc, const char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Aufruf: %s anzahl\n", argv[0]);
    exit(EXIT_FAILURE);    
  }

  int anz = atoi(argv[1]);
  if ((anz < 1) || (anz > 30)) {
    fprintf(stderr, "%s: Die Anzahl (%d) muss zwischen 1 und 30 sein!\n",
            argv[0], anz);
    exit(EXIT_FAILURE);    
  }
  int array[anz];
  
  fill(array, anz);
  print(array, anz);
  while (perm(array, anz)) {
    print(array, anz);
  }

  exit(EXIT_SUCCESS);
}
