#ifndef SCANNER_H_
#define SCANNER_H_

#include <stdbool.h>
#include <stdint.h>

#include "token.h"

typedef struct TokenScanner {
  bool (*init_condition)(const char c);
  bool (*end_condition)(const char c);

  // indicates whether the beginning character should be included
  bool include_begin;

  // indicates whether the ending character should be included or not
  bool include_end;
} TokenScanner;

char* scan(TokenScanner scanner, const char* line, 
    uint32_t linePos, uint32_t row);

#endif // SCANNER_H_
