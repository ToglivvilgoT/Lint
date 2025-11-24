#include "lint.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils/vector.h"

void runFile(const char* path) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    printf("File not found!\n");
    exit(1);
  }

  fclose(file);
}

void run(const char* line) {
  Vector tokens;
  vec_init(&tokens);

  tokenize(line, &tokens);

  vec_free(&tokens);
}
