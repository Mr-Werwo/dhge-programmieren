// Erzeugen aller Permutationen
//
// Aufruf: perm anzahl
// 
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int arr[], int left, int right);
void reverse(int arr[], int left, int right);
int find_smaller(const int arr[], int anz);
int find_larger(const int arr[], int anz, int x);
bool perm(int arr[], int anz);
void fill(int arr[], int anz);
void print(const int arr[], int anz);

// Vertauscht die Elemente Nummer left und right im Array arr.
void swap(int arr[], int left, int right)
{
  int tmp = arr[left];
  arr[left] = arr[right];
  arr[right] = tmp;
}

// Dreht die Reihenfolge der Elemente von arr
// zwischen den Positionen left und right (jeweils einschließlich) um.
void reverse(int arr[], int left, int right)
{
  for ( ; left < right; ++left, --right) {
    swap(arr, left, right);
  }
}

// Liefert den Index des ersten Elementes in arr von hinten,
// das kleiner als das Element dahinter ist,
// oder -1, wenn es kein solches Element gibt.
// anz ist die Anzahl der Elemente im Array.
int find_smaller(const int arr[], int anz)
{
  // wir beginnen beim Vorletzten, weil der Letzte hat keinen Nachfolger
  for (int i = anz - 2; i >= 0; --i) {
    if (arr[i] < arr[i + 1]) {
      return i;
    }
  }
  return -1;
}

// Liefert den Index des ersten Elementes in arr von hinten,
// das größer als x ist, 
// oder -1, wenn es kein solches Element gibt.
// anz ist die Anzahl der Elemente im Array.
int find_larger(const int arr[], int anz, int x)
{
  for (int i = anz - 1; i >= 0; --i) {
    if (arr[i] > x) {
      return i;
    }
  }
  return -1;
}

// Erzeugt die nächste Permutation im Array arr.
// anz ist die Anzahl der Elemente in arr.
// Returnwert true bei Erfolg,
// false wenn arr schon die letzte Permutation enthält.
bool perm(int arr[], int anz)
{
  int left = find_smaller(arr, anz);
  if (left == -1) return false;
  int right = find_larger(arr, anz, arr[left]);

  swap(arr, left, right);
  reverse(arr, left + 1, anz - 1);
  return true;
}

// Füllt das Array arr (anz Elemente) aufsteigend mit den Zahlen 1 bis anz.
void fill(int arr[], int anz)
{
  for (int i = 0; i < anz; ++i) {
    arr[i] = i + 1;  // Index von 0 bis anz-1, Zahlen von 1 bis anz
  }
}

// Gibt das Array arr (anz Elemente) aus.
void print(const int arr[], int anz)
{
  for (int i = 0; i < anz; ++i) {
    printf("%d ", arr[i]);
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
