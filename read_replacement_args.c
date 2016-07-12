#include <stdlib.h>
#define DICT_NO_KEY "§§DICT_NO_KEY§§"

typedef struct DictEntry_t {
  char *key;
  char *value;
} DictEntry_t;

typedef struct Dict_t {
  size_t count;
  DictEntry_t *entries;
} Dict_t;

int calculateDictEntryCount(int argc) {
  if (argc % 2 > 0) {
    return -1;
  } else {
    return argc/2;
  }
}

Dict_t readDict(int argc, char *argv[], DictEntry_t *entries) {
  Dict_t dict;
  dict.count = calculateDictEntryCount(argc);
  for(int i = 0; i*2 < argc; i++) {
    DictEntry_t entry;
    entry.key = argv[i*2];
    entry.value = argv[(i*2)+1];
    entries[i] = entry;
  }
  dict.entries = entries;

  return dict;
}

const char * dictFind(Dict_t dict, const char * key) {
  for(size_t i=0; i < dict.count; i++) {
    printf("Comparing %s == %s\n", dict.entries[i].key, key);
    if (strcmp(dict.entries[i].key, key) == 0) {
      return dict.entries[i].value;
    }
  }

  return DICT_NO_KEY;
}
