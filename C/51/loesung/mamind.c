// Mastermind
//
// Aufruf: mamind
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Anzahl der Stellen
#define STELLEN 4
// Anzahl der möglichen Ziffern für eine Stelle
#define ZIFFERN 6

// Minimum-Funktion
inline int min(int a, int b)
{
  return (a < b) ? a : b;
}

// Idee:
// 1.) Ein Versuch bzw. eine Kombination wird als ein String dargestellt:
//     STELLEN viele Ziffern zwischen '1' und der Ziffer ZIFFERN,
//     plus Ende-Markierung (daher ein char-Array der Länge STELLEN + 1).
// 2.) Das Array komb enthält alle möglichen Kombinationen,
//     das sind ZIFFERN hoch STELLEN viele
//     (d.h. char komb[ZIFFERN hoch STELLEN][STELLEN + 1];).
// 3.) Kommt eine Kombination nicht mehr in Frage,
//     wird der entsprechende Eintrag in komb
//     auf den Leerstring gesetzt (d.h. komb[i][0] ist '\0').

// Initialisiere das Array komb (anzahl viele Zeilen)
// mit allen möglichen Kombinationen
void init(char komb[][STELLEN + 1], int anzahl);
// wähle zufällig eine noch in Frage kommende Kombination aus komb,
// returniere einen Pointer darauf.
char *waehle(char komb[][STELLEN + 1], int anzahl);
// loesung enthält irgendeine Kombination
// versuch enthält den aktuellen Versuch 
// ganz und halb enthalten seine Bewertung
// Kann loesung zu diesem Versuch und dieser Bewertung passen (ja/nein)?
bool passt(const char *loesung, const char *versuch, int ganz, int halb);
// streiche alle noch in Frage kommenden Kombinationen aus komb,
// die nicht zum Versuch versuch und seiner Bewertung halb und ganz passen
void streiche(char komb[][STELLEN + 1], int anzahl,
              const char *versuch, int ganz, int halb);


// Initialisiere das Array komb (anzahl viele Zeilen)
// mit allen möglichen Kombinationen
void init(char komb[][STELLEN + 1], int anzahl)
{
  // setze die erste Kombination auf lauter '1'
  for (int j = 0; j < STELLEN; ++j) {
    komb[0][j] = '1';
  }
  komb[0][STELLEN] = '\0';  // Ende-Markierung nicht vergessen!

  // Ab der zweiten Kombination:
  // Wie beim normalen Hochzählen von Zahlen,
  // nur umgekehrt von vorne nach hinten:
  // 1.) Vorigen Eintrag kopieren
  // 2.) Wenn in den Stellen vorne schon die höchste Ziffer steht:
  //     Auf Ziffer 1 zurücksetzen
  // 3.) Die erste Stelle, die noch nicht höchste Ziffer hat, um 1 erhöhen.
  for (int i = 1; i < anzahl; ++i) {
    strcpy(komb[i], komb[i - 1]);
    int j;
    for (j = 0; komb[i][j] == ZIFFERN + '0'; ++j) {
      komb[i][j] = '1';
    }
    ++komb[i][j];
  }
}

// wähle zufällig eine noch in Frage kommende Kombination aus komb,
// returniere einen Pointer darauf.
char *waehle(char komb[][STELLEN + 1], int anzahl)
{
  // Beginne an einer zufälligen Stelle von komb zu suchen
  int beginn = rand() % anzahl;

  // Suche ab dort die erste Kombination, die noch nicht gelöscht ist
  for (int i = beginn; ; ) {
    if (komb[i][0] != '\0') {
      // Nicht gelöschte Kombination gefunden, Pointer darauf zurückgeben
      // Ein zweidimensionales Array mit nur einer []
      // liefert einen Pointer auf die i-te Zeile des Arrays!
      return komb[i];
    }
    // Geh zur nächsten Kombination
    ++i;
    // Bist du hinter dem Ende von komb, fange wieder vorne an
    if (i == anzahl) {
      i = 0;
    }
    if (i == beginn) {
      // wir sind einmal komplett durch alle Kombinationen gelaufen
      // und haben keine noch in Frage kommende Kombination mehr gefunden
      // ==> an den bisherigen Bewertungen war etwas faul!!!
      printf("Du hast mich beschwindelt!\n");
      exit(EXIT_FAILURE);
    }
  }
}

// loesung enthält irgendeine Kombination
// versuch enthält den aktuellen Versuch 
// ganz und halb enthalten seine Bewertung
// Kann loesung zu diesem Versuch und dieser Bewertung passen (ja/nein)?
bool passt(const char *loesung, const char *versuch, int ganz, int halb)
{
  // anzLsg enthält für jede mögliche Ziffer, wie oft sie in loesung vorkommt
  // anzVers enthält dasselbe für versuch
  // gezählt werden nur die Ziffern, die *nicht* genau übereinstimmen
  int anzLsg[ZIFFERN], anzVers[ZIFFERN];
  // beide Arrays mit 0 initialisieren
  for (int i = 0; i < ZIFFERN; ++i) {
    anzLsg[i] = anzVers[i] = 0;
  }

  // treffer zählt die Übereinstimmungen zwischen loesung und versuch
  // (gleiche Ziffer an gleicher Stelle)
  int treffer = 0;
  for (int i = 0; i < STELLEN; ++i) {
    if (loesung[i] == versuch[i]) {
      ++treffer;
    } else {
      // Stelle stimmt nicht überein ==> Ziffern zählen
      // - '1' statt - '0', weil die Ziffern beginnen bei 1, nicht 0,
      // d.h. '1' entspricht Array-Index 0, '2' entspricht 1 usw.
      ++anzLsg[loesung[i] - '1'];
      ++anzVers[versuch[i] - '1'];
    }
  }
  if (treffer != ganz) {
    return false;
  }

  // die ganz Richtigen haben gestimmt,
  // also zählen wir jetzt die halb Richtigen
  // Halb richtig ist jede Ziffer,
  // die sowohl in loesung als auch in versuch vorkommt,
  // aber nicht genau übereinstimmt.
  // Wie oft jede Ziffer in beidem vorkommt,
  // sagt der kleinere Wert von anzLsg und anzVers
  // Die Summe des jeweils kleineren Wertes von anzLsg und anzVers
  // über alle Ziffern ergibt daher die Gesamtzahl der halb Richtigen
  treffer = 0;
  for (int i = 0; i < ZIFFERN; ++i) {
    treffer += min(anzLsg[i], anzVers[i]);
  }
  if (treffer != halb) {
    return false;
  }

  // ganz und halb Richtige sind beide wie angegeben!
  return true;
}

// streiche alle noch in Frage kommenden Kombinationen,
// die nicht zum Versuch versuch und seiner Bewertung halb und ganz passen
void streiche(char komb[][STELLEN + 1], int anzahl,
              const char *versuch, int ganz, int halb)
{
  for (int i = 0; i < anzahl; ++i) {
    // wenn die Kombination noch nicht gestrichen ist und nicht passt ...
    if ((komb[i][0] != '\0') && !passt(komb[i], versuch, ganz, halb)) {
      komb[i][0] = '\0';  // ... streiche sie
    }
  }
}

int main(void)
{
  srand(time(NULL));

  // Anzahl aller möglichen Kombinationen (lround wegen Rundungsfehlern im pow)
  int anzKomb = lround(pow(ZIFFERN, STELLEN));  
  char komb[anzKomb][STELLEN + 1];  // Array aller möglichen Kombinationen

  init(komb, anzKomb);

  // die Schleife zählt die Anzahl der Versuche
  for (int anzVers = 1; ; ++anzVers) {
    char vers[STELLEN + 1]; // Der aktuelle Versuch
    strcpy(vers, waehle(komb, anzKomb));

    // Versuch anzeigen und bewerten lassen
    int ganz, halb;    // Anzahl der ganz und halb Richtigen
    for (;;) {  // wiederhole bis der Benutzer sinnvolle Zahlen eingibt
      printf("\nMein %d. Versuch: %s\n", anzVers, vers);
      printf("Wie viele richtige Ziffern am richtigen Platz? ");
      scanf("%d", &ganz);
      printf("Wie viele zusätzliche richtige Ziffern am falschen Platz? ");
      scanf("%d", &halb);
      // sinnvolle Eingabe?
      if ((ganz >= 0) && (halb >= 0) && (ganz + halb <= STELLEN)) break;
      printf("Das kann nicht stimmen - bitte nochmal!\n");
    }

    // alle Ziffern richtig ==> gewonnen!
    if (ganz == STELLEN) {
      printf("Hurra, erraten in %d Versuchen!\n", anzVers);
      exit(EXIT_SUCCESS);
    }
    
    // streiche alle Kombinationen, die nicht zur aktuellen Bewertung passen
    streiche(komb, anzKomb, vers, ganz, halb);
  }
}
