#include <stdio.h>
#include <assert.h>
#include "../read_replacement_args.c"
#include "../render_template.c"

FILE *getTemplateFile() {
  static const char *templateFileName = "template.hsh";
  FILE *templateFile;
  if ((templateFile = fopen(templateFileName, "r")) == NULL) {
    printf("Failed to test template file open file %s\n", templateFileName);
    assert(-1);
    return NULL;
  }
  return templateFile;
}

void testCalculateRenderedLength() {
  FILE *templateFile = getTemplateFile();
  // it returns 3X the file length
  static const size_t templateFileSize = 15;
  static const size_t expectedSize = templateFileSize*3;
  size_t result = calculateRenderedLength(templateFile);
  // returns correct size
  assert(result == expectedSize);
  fclose(templateFile);
}

void testRenderBasicTemplate() {
  int argc = 2;
  char *argv[] = {"name:", "World"};

  DictEntry_t entries[calculateDictEntryCount(argc)];
  Dict_t dict = readDict(argc, argv, entries);

  FILE *templateFile = getTemplateFile();
  //char result[calculateRenderedLength(templateFile)];
  fclose(templateFile);
}

void testSuiteRenderTemplate() {
  testCalculateRenderedLength();
  testRenderBasicTemplate();
}
