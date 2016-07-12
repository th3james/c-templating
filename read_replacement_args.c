#include <stdlib.h>
/*
char ***readDict(int argc, char *argv[]) {
  for(int i = 2; i<argc; i++) {
  }
  return argv;
}
*/

typedef struct DictEntry_t {
  char *key;
  char *value;
} DictEntry_t;

DictEntry_t *readDict(int argc, char *argv[]) {
  DictEntry_t *dict = calloc(sizeof(DictEntry_t), argc/2);

  for(int i = 0; i*2 < argc; i++) {
    DictEntry_t entry;
    entry.key = argv[i*2];
    entry.value = argv[(i*2)+1];
    dict[i] = entry;
  }

  return dict;
}
