#include <stdio.h>
#include <stdint.h>
#ifndef RENDER_TEMPLATE
#define RENDER_TEMPLATE
#define OPEN_DELIMITER '{'
#define CLOSING_DELIMITER '}'
#define DELIMITER_COUNT 2
#define MAX_REPLACEMENT_LENGTH 40

size_t calculateRenderedLength(FILE *templateFp) {
  fseek(templateFp, 0, SEEK_END);
  fpos_t position = ftell(templateFp)*3;
  rewind(templateFp);
  return (size_t)position;
}

typedef struct ParserState_t {
  int8_t inCount;
  char *replacementKey;
} ParserState_t;

ParserState_t buildStartState() {
  ParserState_t state;
  state.inCount = 0;
  state.replacementKey = calloc(sizeof(char), MAX_REPLACEMENT_LENGTH);
  return state;
}

void deleteState(ParserState_t *state) {
  free(state->replacementKey);
}

int8_t shouldRenderReplacement(ParserState_t *state) {
  if (state->inCount == 0 && *state->replacementKey != '\0') {
    return 1;
  } else {
    return 0;
  };
}

char renderChar(char c, ParserState_t *state) {
  if (c == '{') {
    state->inCount++;
    return '\0';
  } else if (c == '}') {
    state->inCount--;
    return '\0';
  }

  if (state->inCount == 0) {
    return c;
  } else if (state->inCount == DELIMITER_COUNT && c != ' ' ) {
    int16_t strEnd = 0;
    while(state->replacementKey[strEnd] != '\0') { strEnd++; }
    state->replacementKey[strEnd] = c;
    state->replacementKey[strEnd+1] = '\0';
    return '\0';
  } else {
    assert(-1); // shouldn't happen
    return '\0';
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
    if (shouldRenderReplacement(&state)) {
      const char * replacementValue = dictFind(
        replacements, state.replacementKey
      );
      size_t keyPos = 0;
      char repC;
      while((repC = replacementValue[keyPos]) != '\0') {
        result[p] = repC;
        p++;
        keyPos++;
      }
      state.replacementKey[0] = '\0';
    }
  }
  deleteState(&state);
  result[p] = '\0';
}
#endif
