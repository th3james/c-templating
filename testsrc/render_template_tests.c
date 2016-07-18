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
  // rewinds the file
  fpos_t position;
  fgetpos(templateFile, &position);
  assert(position == SEEK_SET);
  fclose(templateFile);
}

void testRenderChar() {
  ParserState_t state = buildStartState();
  char c;
  c = 'H';
  assert(renderChar(c, &state) == 'H');
  assert(state.inCount == 0);
  
  // Opening delimiter
  c = OPEN_DELIMITER;
  assert(renderChar(c, &state) == '\0');
  assert(state.inCount == 1);
  assert(renderChar(c, &state) == '\0');
  assert(state.inCount == 2);

  // Closing delimiter
  c = CLOSING_DELIMITER;
  assert(renderChar(c, &state) == '\0');
  assert(state.inCount == 1);
  assert(renderChar(c, &state) == '\0');
  assert(state.inCount == 0);
}

void testRenderBasicTemplate() {
  int argc = 2;
  char *argv[] = {"name:", "World"};

  DictEntry_t entries[calculateDictEntryCount(argc)];
  Dict_t dict = readDict(argc, argv, entries);

  FILE *templateFile = getTemplateFile();
  char result[calculateRenderedLength(templateFile)];
  renderTemplate(templateFile, dict, result);
  printf("Got result '%s'", result);
  assert(strcmp(result, "Hello World") == 0);
  fclose(templateFile);
}

void testSuiteRenderTemplate() {
  testCalculateRenderedLength();
  testRenderChar();
  testRenderBasicTemplate();
}
