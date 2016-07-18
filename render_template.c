#include <stdio.h>
#include <stdint.h>
#ifndef RENDER_TEMPLATE
#define RENDER_TEMPLATE
#define OPEN_DELIMITER '{'
#define CLOSING_DELIMITER '}'
#define DELIMITER_COUNT 2

size_t calculateRenderedLength(FILE *templateFp) {
  fseek(templateFp, 0, SEEK_END);
  fpos_t position = ftell(templateFp)*3;
  rewind(templateFp);
  return (size_t)position;
}

typedef struct ParserState_t {
  int8_t inCount;
} ParserState_t;

ParserState_t buildStartState() {
  ParserState_t state;
  state.inCount = 0;
  return state;
}

char renderChar(char c, ParserState_t *state) {
  if (c == '{') {
    state->inCount++;
    return '\0'
  } else if (c == '}') {
    state->inCount--;
    return '\0';
  }

  if (state->inCount == 0) {
    return c;
  }
}

void renderTemplate(FILE *templateFp, Dict_t replacements, char *result) {
  size_t fileLength = 10;
  size_t p=0;
  char c;
  ParserState_t state = buildStartState();

  while((c=fgetc(templateFp)) != EOF) {
    if ((c = renderChar(c, &state)) != '\0') {
      result[p] = c;
      p++;
    }
  }
  result[++p] = '\0';
}
#endif
