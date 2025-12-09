// Das ist ein Kommentar.
// Er dient zur Erklärung und wird vom Computer ignoriert.

// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

// Weist den Compiler an, den vordefinierten File "stdio.h" zu lesen,
// in dem u.a. die Deklaration für die vordefinierte Funktion "printf" steht.
#include <stdio.h>

// Wir definieren eine Funktion namens "main",
// die einen int-Wert (ganze Zahl) zurückliefert.
//
// "main" ist die Funktion, die automatisch ausgeführt wird,
// wenn wir unser Programm starten.
//
// Wenn "main" fertig ist, endet auch unser Programm.
//
// Den zurückgelieferten Wert könnten wir z.B. in einem Batchfile prüfen.
// Er zeigt Erfolg (0) oder Fehler (>0) an (ist uns aber vorläufig egal).
int main(
  // "main" hat 2 vordefinierte Argumente,
  // in denen unserem Programm die Aufrufs-Befehlszeile übergeben wird.
  //
  // Wir könnten sie nennen, wie wir wollen,
  // aber "argc" und "argv" ist üblich.
  int argc,             // "argc" (Merkregel: "Argument count")
                        // ist eine int-Variable (ganze Zahl),
                        // die die Anzahl der Worte in der Befehlszeile angibt.
                        // "argc" ist immer >=1,
                        // denn der Programmname selbst zählt als erstes Wort.
  const char *argv[]    // "argv" ("Merkregel: "Argument values")
                        // sind die einzelnen Worte:
                        // Der Typ "char *" heißt, es sind Texte, keine Zahlen.
                        // "const" heißt, wir dürfen sie nicht ändern.
                        // [] heißt, es ist nicht ein Wert, sondern mehrere.
  )
{
  if (argc == 1)        // == ... Vergleiche linke und rechte Seite
  { // Beginn der Anweisungen für den Fall, dass die Bedingung wahr ist:
    // argc ist 1, der Programmname ist das einzige Wort in der Befehlszeile.

    // Ausgabe: Aufruf der vordefinierten Funktion "printf":
    // Sie zeigt den Text in "..." am Terminal an.
    //
    // "\n" ist ein Code für den Zeilenvorschub ("newline").
    printf("Hallo, wer bist du?\n");
    
  } // hier enden die Anweisungen für den Wahr-Fall des if
  else
  { // und hier beginnen die Anweisungen für den Falsch-Fall des if:
    // Das wird ausgeführt, wenn "argc" nicht gleich 1 ist.

    // Zähl-Schleife: Wiederhole etwas für jedes einzelne Wort
    // "i" ist unsere Zähl-Variable, wir zählen von 1 bis (argc - 1):
    // In einer []-Variable mit n einzelnen Werten
    // sind die Werte von 0 bis (n-1) durchnummeriert,
    // aber argv[0] ist der Programmname und interessiert uns nicht.
    for (
      int i = 1;     // Deklaration einer neuen Schleifen-Zählvariablen i
                     // (ganzzahlig) und Schleifen-Initialisierung:
                     // Wird ein Mal bei Beginn der Schleife gemacht:
                     // Setze i auf 1 (speichere 1 in der Variable i).
      i <= argc - 1; // Schleifen-Prüfung: Wird in jedem Umlauf
                     // vor Ausführung der Anweisungen in der Schleife geprüft:
                     // Wenn i kleinergleich (argc - 1) ist,
                     // mach die Anweisungen in der Schleife,
                     // sonst verlasse die Schleife
                     // (mach nach der "}" der Schleife weiter).
      ++i            // Weiterzähl-Befehl: Wird in jedem Umlauf
                     // nach Ausführung der Anweisungen in der Schleife gemacht:
                     // Zähle 1 zu i dazu.
      )
    {
      // Ausgabe wie oben, mit "Lückentext-Ersetzung":
      // "%s" wird durch den angegebenen Wert ersetzt.
      // 
      // argv[i] liefert den i-ten Wert in argv,
      // d.h. das i-te Wort der Befehlszeile
      printf("Hallo, %s!\n", argv[i]);
    } // Ende der Anweisungen in der for-Schleife
    
  } // Ende der Anweisungen des Falsch-Falles

  return 0;  // Programmende, gibt 0 zur Befehlszeile zurück: Alles ok.
             // Stattdessen könnte man auch "exit(0);"
             // oder "exit(EXIT_SUCCESS);" schreiben.
  
} // Ende der Anweisungen von "main"
