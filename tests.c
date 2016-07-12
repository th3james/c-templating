#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "read_replacement_args.c"

void testReadDictOneEntry() {
  int argc = 2;
  char *argv[] = {"hat:", "boat"};

  DictEntry_t *result = readDict(argc, argv);
  assert(strcmp(result[0].key, "hat:") == 0);
  assert(strcmp(result[0].value, "boat") == 0);
  free(result);
}

void testReadDictTwoEntries() {
  int argc = 4;
  char *argv[] = {
    "one:", "one",
    "two:", "two"
  };

  DictEntry_t *result = readDict(argc, argv);
  assert(strcmp(result[0].key, "one:") == 0);
  assert(strcmp(result[0].value, "one") == 0);
  assert(strcmp(result[1].key, "two:") == 0);
  assert(strcmp(result[1].value, "two") == 0);
  free(result);
}

int main(int argc, char *argv[]) {
  testReadDictOneEntry();
  testReadDictTwoEntries();
}
