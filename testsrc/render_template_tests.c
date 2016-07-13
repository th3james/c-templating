#include <stdio.h>
#include <assert.h>
#include "../read_replacement_args.c"

void testRenderBasicTemplate() {
  int argc = 2;
  char *argv[] = {"name:", "World"};

  DictEntry_t entries[calculateDictEntryCount(argc)];
  Dict_t dict = readDict(argc, argv, entries);

  static const char *templateFileName = "template.hsh";
  FILE *templateFile;
  if ((templateFile = fopen(templateFileName, "r")) == NULL) {
    printf("Failed to test template file open file %s\n", templateFileName);
  } else {
    printf("Opened file: %s\n", argv[1]);
  }
}

void testSuiteRenderTemplate() {
  testRenderBasicTemplate();
}
