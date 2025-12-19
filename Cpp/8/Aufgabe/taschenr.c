// Ganz einfacher Taschenrechner:
// + - * / ^ von links nach rechts ohne Vorrang und ohne Klammern
// (mit x statt * und p statt ^)
//
// Aufruf: taschenr rechnung
// (eine Zahl / ein Rechenzeichen pro Wort, d.h. mit Zwischenräumen!)
//
// Klaus Kusche, 2012

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char *argv[])
{
  // 1, 3, 5, ... Eingabeworte (+1 für den Programmnamen) sind ok
  // ==> argc muss gerade sein
  if (argc % 2 != 0) {
    fprintf(stderr, "%s: Die Anzahl der Eingaben stimmt nicht!\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Bisheriges Ergebnis = linker Operand für die nächste Rechnung
  // Am Anfang: Erste Zahl
  double result = atof(argv[1]);
  // Schleife in Zweierschritten ab dem ersten Rechenzeichen
  // argv[i] ist das Rechenzeichen, argv[i + 1] ist die nächste Zahl
  for (int i = 2; i < argc; i += 2) {
    // nächste Zahl (nach dem Rechenzeichen) = rechter Operand
    double input = atof(argv[i + 1]);    
    // Rechenzeichen dazwischen anschauen: 1. Zeichen von i-tem Eingabe-Wort
    // switch geht nur mit einzelnen Zeichen, nicht mit ganzen Texten!
    switch (argv[i][0]) {
      case '+':
        result += input;
        break;
      case '-':
        result -= input;
        break;
      case 'x':
        result *= input;
        break;
      case '/':
        if (input == 0) {
          fprintf(stderr, "%s: Division durch 0!\n", argv[0]);
          exit(EXIT_FAILURE);
        }
        result /= input;
        break;
      case 'p':
        result = pow(result, input);
        break;
      default:
        fprintf(stderr, "%s: %c: Kein Rechenzeichen?\n", argv[0], argv[i][0]);
        exit(EXIT_FAILURE);
    }
  }

  printf("Ergebnis: %g\n", result);
  
  exit(EXIT_SUCCESS);
}
