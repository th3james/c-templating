#ifndef RENDER_TEMPLATE
#define RENDER_TEMPLATE
size_t calculateRenderedLength(FILE *templateFp) {
  fseek(templateFp, 0, SEEK_END);
  fpos_t position = ftell(templateFp)*3;
  rewind(templateFp);
  return (size_t)position;
}

void renderTemplate(FILE *templateFp, Dict_t replacements, char *result) {
  result[0] = 'H';
}
#endif
