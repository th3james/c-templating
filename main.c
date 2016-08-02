#include <stdio.h>
#include "read_replacement_args.c"
#include "render_template.c"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("Expected arguments: file_name, replacements\n");
    return 1;
  }

  DictEntry_t entries[calculateDictEntryCount(argc)];
  Dict_t replacementDict = readDict(argc, argv, entries);

  FILE *templateFile;
  if ((templateFile = fopen(argv[1], "r")) == NULL) {
    printf("Failed to open file %s\n", argv[1]);
  } else {
    //printf("Opened file: %s\n", argv[1]);
    char result[calculateRenderedLength(templateFile)];
    renderTemplate(templateFile, replacementDict, result);
    puts(result);
  }

  return 0;
}
