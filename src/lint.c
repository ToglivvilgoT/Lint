#include "lint.h"

void run(const char* line) { 
  Token* tokens = tokenize(line); 

  free(tokens);
}
