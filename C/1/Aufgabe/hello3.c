// Unser drittes Programm: Hallo mit Ausgabe eines oder mehrerer Namen
//
// Aufruf: hello3 name1 name2 ...
//
// Klaus Kusche, 2010

#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    printf("Hallo, ich bin %s wer bist du?\n", argv[0]);
  } else if (argc > 10) {
    printf("Hallo an alle!\n");
  }
  else {
    for (int i = 1; i < argc; ++i) {
      int person = argc - i;
      if (i == 1) {
        printf("Hallo, %s! Du bist erster Platz\n", argv[person]);
      } else {
        printf("Hallo, %s! Du bist der %d. Platz\n", argv[person], i);
      }
    }
    printf("\n\n Hallo");
    for (int i = 1; i < argc; ++i) {
      int rest = argc - i;
      if (argc == 2) {
        printf(", %s!", argv[i]);
      } else {
        if (rest == 1) {
          printf(" und %s!\n", argv[i]);
        } else {
          printf(", %s", argv[i]);
        }
      }
    }
    printf("Ihr seid %d Leute \n", argc-1);
  }

  return 0;
}
