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
  static const size_t templateFileSize = 29;
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

void testBuildStartState() {
  ParserState_t state = buildStartState();
  assert(strcmp(state.replacementKey, "") == 0);
  deleteState(&state);
}

void testRenderCharNotParsing() {
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
  deleteState(&state);
}

void testRenderCharParsing() {
  ParserState_t state = buildStartState();
  char c;

  // inCount == DELIMITER_COUNT, space
  c = ' ';
  state.inCount = DELIMITER_COUNT;
  assert(renderChar(c, &state) == '\0');
  assert(strcmp(state.replacementKey, "") == 0);

  // inCount == DELIMITER_COUNT, character
  c = 'n';
  state.inCount = DELIMITER_COUNT;
  assert(renderChar(c, &state) == '\0');
  assert(state.inCount == DELIMITER_COUNT);
  assert(strcmp(state.replacementKey, "n") == 0);

  // inCount == DELIMITER_COUNT, character
  c = 'e';
  state.inCount = DELIMITER_COUNT;
  assert(renderChar(c, &state) == '\0');
  assert(state.inCount == DELIMITER_COUNT);
  assert(strcmp(state.replacementKey, "ne") == 0);

  // inCount == DELIMITER_COUNT, space, pre-existing replacementKey
  c = ' ';
  state.inCount = DELIMITER_COUNT;
  assert(renderChar(c, &state) == '\0');
  assert(state.inCount == DELIMITER_COUNT);
  assert(strcmp(state.replacementKey, "ne") == 0);

  deleteState(&state);
}

void testShouldRenderReplacement() {
  ParserState_t state = buildStartState();

  // when inCount > 0 => false
  state.inCount = 1;
  assert(shouldRenderReplacement(&state) == 0);

  // when inCount == 0 and replacementKey == "" => false
  state.inCount = 0;
  state.replacementKey[0] = '\0';
  assert(shouldRenderReplacement(&state) == 0);

  // when inCount == 0 and replacementKey != "" => true
  state.inCount = 0;
  strcpy(state.replacementKey, "hat");
  assert(shouldRenderReplacement(&state) == 1);

  deleteState(&state);
}

void testRenderBasicTemplate() {
  int argc = 4;
  char *argv[] = {"greeting:", "Hello", "name:", "World"};

  DictEntry_t entries[calculateDictEntryCount(argc)];
  Dict_t dict = readDict(argc, argv, entries);

  FILE *templateFile = getTemplateFile();
  char result[calculateRenderedLength(templateFile)];
  renderTemplate(templateFile, dict, result);

  printf("Got result '%s'", result);
  char * expected = "Well, Hello World!\n";
  printf("Expected '%s'", expected);

  assert(strcmp(result, expected) == 0);
  fclose(templateFile);
}

void testSuiteRenderTemplate() {
  testCalculateRenderedLength();
  testBuildStartState();
  testRenderCharNotParsing();
  testRenderCharParsing();
  testShouldRenderReplacement();
  testRenderBasicTemplate();
}
