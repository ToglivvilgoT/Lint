#ifndef TEST_H_
#define TEST_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utils/string_utils.h"

void runTests() {
  const char* str = "  this is  a    string  ";
  const char* gold[] = {"this", "is", "a", "string"};

  size_t len = -1;
  const char** splitted = split_string(str, &len, NULL);
  assert(len == 4);

  for (size_t i = 0; i < len; i++) {
    assert(strcmp(splitted[i], gold[i]) == 0);
    printf("|%s| ", splitted[i]);
  }
  printf("\nTests passed!\n");
}

#endif // TEST_H_
