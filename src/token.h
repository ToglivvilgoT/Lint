#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  // Single character
  LEFT_PARENTHESIS, RIGHT_PARENTHESIS, LEFT_BRACE, RIGHT_BRACE,
  MINUS, PLUS, STAR, SLASH, SEMICOLON, QUOTES, COMMA, DOT, 
  
  // Comparison
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,
  
  // Literals
  IDENTIFIER, STRING, NUMBER,

  // Keywords
  AND, IF, ELSE, TRUE, FALSE, FUNCTION, FOR, WHILE, OR,
  RETURN, LET, 
} TokenType;

typedef struct {
  char* token;
  TokenType type;
  uint32_t line;
  uint32_t character;
} Token;

Token* tokenize(const char* line, int* out_count);

#endif  // TOKEN_H_
