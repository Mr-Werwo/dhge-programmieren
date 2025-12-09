// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
// Erweiterung 4
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    printf("Hallo, wer bist du?\n");
  } else {  // man könnte auch diese { } weglassen und else if schreiben 
    if (argc > 11) { // 10 Namen + Programmname ==> argc ist 11
      printf("Hallo an alle!\n");
    } else {
      for (int i = 1; i < argc; ++i) {
        printf("Hallo, %s!\n", argv[i]);
      }
    }
  }

  return 0;
}
