#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "lint.h"

int main() {
  printf("Lint 0.0.1\n");

  while (true) {
    printf("> ");
    char* line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) != -1) {
      run(line);
    }
  }

  return 0;
}
