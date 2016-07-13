#ifndef RENDER_TEMPLATE
#define RENDER_TEMPLATE
size_t calculateRenderedLength(FILE *templateFile) {
  fseek(templateFile, 0, SEEK_END);
  return ftell(templateFile)*3;
}
#endif
