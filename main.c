#include <stdio.h>
#include "read_replacement_args.c"

int main(int argc, char *argv[]) {
  if (argc > 5) {
    printf("Expected arguments: file_name, replacement\n");
    return 1;
  }

  DictEntry_t entries[calculateDictEntryCount(argc)];
  Dict_t replacementDict = readDict(argc, argv, entries);

  FILE *templateFile;
  if ((templateFile = fopen(argv[1], "r")) == NULL) {
    printf("Failed to open file %s\n", argv[1]);
  } else {
    printf("Opened file: %s\n", argv[1]);
    char c;
    while((c = getc(templateFile)) != EOF) {
      putchar(c);
    }
  }

  printf("Key hat: %s", dictFind(replacementDict, "hat"));

  return 0;
}
