// Unser zweites Programm: Hallo mit Ausgabe eines Namens
//
// Aufruf: hello2   oder   hello2 name
//
// Klaus Kusche, 2010
 
#include <stdio.h>

int main(int argc, const char *argv[])
{
  if (argc == 1) {
    printf("Hallo, wer bist du?\n");
  } else {
    printf("Hallo, %s!\n", argv[1]);
  }

  return 0;
}
