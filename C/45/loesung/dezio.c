// Einlesen und Ausgeben von Dezimalzahlen
//
// Aufruf: dezio zahl1 zahl2 ...
// 
// Klaus Kusche, 2017

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Größe des Strings für das Ergebnis (incl. '\0')
// 8 Zeichen sind für große int's zu wenig
// ==> man kann dadurch auch den Überlauf testen
#define MAX_LEN 8

int unser_atoi(const char str[])
{
  int i = 0;     // Position der nächsten Ziffer in str
  int vorz = 1;  // Vorzeichen (+1 oder -1)

  // Vorzeichen am Anfang speichern, am Ende zur Zahl dazumultiplizieren
  if (str[0] == '-') {
    vorz = -1;
    ++i;     // Ziffern-Schleife fängt erst beim 2. Zeichen an
  }
  
  int z = 0;     // der bisher eingelesene Wert der Zahl
  for ( ; str[i] != '\0'; ++i) {  // Schleife über alle Zeichen von str
    char c = str[i];   // das i-te Zeichen von str
    if (isdigit(c)) {
      // ASCII-Code c in Zahl umrechnen und hinten an z anhängen
      // (d.h. den bisherigen Wert von z um eine Stelle nach links schieben)
      // Wenn c ein Ziffern-Zeichen ist, liefert c - '0' den Ziffernwert von c
      z = (10 * z) + (c - '0'); 
    } else {
      printf("'%c' ist keine Ziffer\n", c);
      break;
    }
  }
  
  return z * vorz;
}

char *unser_itoa(char ausg[], int len, int z)
{
  // wir brauchen mindestens 2 Zeichen Platz: Eine Ziffer und '\0'
  if (len < 2) {
    if (len > 0) ausg[0] = '\0';  // trotzdem "schönen" String speichern!
    return NULL;
  }

  // i: beim wievielten Zeichen beginnen die Ziffern in ausg?
  int i = 0;  
  if (z < 0) {  // Negative Zahl: Ergebnis beginnt mit '-'
    ausg[0] = '-';
    ++i;     // die Ziffern beginnen erst im 2. Element von ausg
    z = -z;  // verwandle die Zahl ohne Vorzeichen
  }

  // wir berechnen die Ziffern von hinten nach vorne,
  // speichern sie von vorne nach hinten, und drehen sie dann um
  // j: wo sind wir gerade in ausg? (wohin gehört die nächste Ziffer)
  int j = i;
  // do...while, damit auch bei '0' eine Stelle ausgegeben wird!
  // (bei normalem while (z > 0) bekämen wir bei 0 den Leerstring)
  do {     
    if (j == len - 1) {  // String voll, Ziffer hat keinen Platz mehr!
      ausg[j] = '\0';    // trotzdem "schönen" String speichern!
      return NULL;
    }
    ausg[j] = (z % 10) + '0'; // + '0' ergibt das Ziffernzeichen zu einer Zahl
    z /= 10;
    ++j;
  } while (z > 0);
  
  ausg[j] = '\0';  // gleich einmal eine Endemarkierung speichern
  --j;             // ... und j wieder auf die letzte Ziffer stellen
  
  // drehe die Zeichen zwischen i und j (jeweils einschließlich) um
  for ( ; i < j; ++i, --j) {
    char tmp;
    tmp = ausg[i]; ausg[i] = ausg[j]; ausg[j] = tmp;
  }
  
  return ausg;
}

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    fprintf(stderr, "Aufruf: %s zahl1 zahl2 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; ++i) {
    int z = unser_atoi(argv[i]);
    char ergeb[MAX_LEN];
    char *p = unser_itoa(ergeb, sizeof(ergeb), z);
    if (p == NULL) {
      printf("%d ist länger als %d Zeichen!\n", z, MAX_LEN - 1);
    } else {
      printf("%s = %d = %s\n", argv[i], z, p);
    }
  }
  
  exit(EXIT_SUCCESS);
}
