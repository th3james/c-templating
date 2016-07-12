#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "read_replacement_args.c"

void testCalculateDictEntryCount() {
  assert(calculateDictEntryCount(2) == 1);
  assert(calculateDictEntryCount(0) == 0);
  assert(calculateDictEntryCount(6) == 3);
  assert(calculateDictEntryCount(3) == -1);
  assert(calculateDictEntryCount(5) == -1);
}

void testReadDictOneEntry() {
  int argc = 2;
  char *argv[] = {"hat:", "boat"};

  DictEntry_t result[calculateDictEntryCount(argc)];
  readDict(argc, argv, result);

  assert(strcmp(result[0].key, "hat:") == 0);
  assert(strcmp(result[0].value, "boat") == 0);
}

void testReadDictTwoEntries() {
  int argc = 4;
  char *argv[] = {
    "one:", "one",
    "two:", "two"
  };

  DictEntry_t result[calculateDictEntryCount(argc)];
  readDict(argc, argv, result);

  assert(strcmp(result[0].key, "one:") == 0);
  assert(strcmp(result[0].value, "one") == 0);
  assert(strcmp(result[1].key, "two:") == 0);
  assert(strcmp(result[1].value, "two") == 0);
}

int main(int argc, char *argv[]) {
  testCalculateDictEntryCount();
  testReadDictOneEntry();
  testReadDictTwoEntries();
}
