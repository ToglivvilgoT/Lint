#include "token.h"

// splits input at whitespaces
Token* tokenize(const char* line) {
  Token* tokens = NULL;
  int cnt = 0;
  int word_len = 0;
  for (size_t i = 0; i < strlen(line); i++) {
    if (line[i] == ' ' || line[i] == '\n') {
      if (word_len) {
        cnt++;
        word_len = 0;
      }
      continue;
    }
    word_len++;
  }
  // count the last word
  if (word_len) cnt++;

  tokens = malloc(sizeof(Token) * cnt);
  return tokens;
}

