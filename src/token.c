#include "token.h"

#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

#include "scanner.h"
#include "utils/string_utils.h"

// FORWARDING
static TokenType lookup_token_type(const char* str);
static const char* token_type_name(TokenType type);

// LOCAL TYPES
// =============================================================================

typedef struct {
    const char* lexeme;
    TokenType type;
} LookupEntry;

// PRIVATE VARIABLES
// =============================================================================

static const char operators[] = {'+', '-', '/', '*', '=', '!', '>', '<'};
static const char punctuators[] = {'(', ')', '{', '}', ',',};

// for debugging purposes
static const char* token_names[] = {
  "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "LEFT_BRACE", "RIGHT_BRACE",
  "MINUS", "PLUS", "STAR", "SLASH", "SEMICOLON", "QUOTES", "COMMA", "DOT",

  "BANG", "BANG_EQUAL",
  "EQUAL", "EQUAL_EQUAL",
  "GREATER", "GREATER_EQUAL",
  "LESS", "LESS_EQUAL",

  "STRING", "LITERAL", "IDENTIFIER",

  "AND", "OR", "NOT", "IF", "ELIF", "ELSE", "TRUE", "FALSE",
  "FUNCTION", "FOR", "WHILE", "RETURN", "LET",

  "INVALID"
};

/* Single + multi-char operators, punctuation, keywords */
static LookupEntry token_lookup[] = {
    // Single character tokens
    { "(", LEFT_PARENTHESIS },   { ")", RIGHT_PARENTHESIS },
    { "{", LEFT_BRACE },         { "}", RIGHT_BRACE },
    { "-", MINUS },              { "+", PLUS },
    { "*", STAR },               { "/", SLASH },
    { ";", SEMICOLON },          { "\"", QUOTES },
    { ",", COMMA },              { ".", DOT },

    // Boolean / arithmetic operators
    { "and", AND }, { "or", OR }, { "not", NOT },

    // Comparison operators
    { "!", BANG },         { "!=", BANG_EQUAL },
    { "=", EQUAL },        { "==", EQUAL_EQUAL },
    { ">", GREATER },      { ">=", GREATER_EQUAL },
    { "<", LESS },         { "<=", LESS_EQUAL },

    // Keywords
    { "if", IF },     { "elif", ELIF }, { "else", ELSE },
    { "true", TRUE }, { "false", FALSE },
    { "fn", FUNCTION },
    { "for", FOR },   { "while", WHILE },
    { "ret", RETURN },
    { "let", LET },

    // Literals handled separately by scanner
    // STRING, LITERAL, IDENTIFIER discovered dynamically

    { NULL, INVALID }
};


// TOKENSCANNER CONDITIONS
// =============================================================================

static bool init_word(const char c) { return isalpha(c) || c == '_'; }
static bool end_word(const char c) { return !(isalnum(c) || c == '_'); }

static bool init_literal(const char c) { return isdigit(c) || c == '.'; }
static bool end_literal(const char c) { return !(isdigit(c) || c == '.'); }

static bool init_string(const char c) { return c == '"'; }
static bool end_string(const char c) { return c == '"' || c == '\0'; }

static bool init_op(const char c) { return char_in_arr(c, operators); }
static bool end_op(const char c) { return !char_in_arr(c, operators); }

static bool init_punctuator(const char c) { return char_in_arr(c, punctuators); }
static bool end_punctuator(const char c) { return char_in_arr(c, punctuators); }

// SCANNERS
// =============================================================================

const TokenScanner word_scanner = { 
  .init_condition = init_word,
  .end_condition = end_word,
  .include_end = false,
  .include_begin = false,
};

const TokenScanner literal_scanner = { 
  .init_condition = init_literal,
  .end_condition = end_literal,
  .include_end = false,
  .include_begin = false,
}; 

const TokenScanner string_scanner = { 
  .init_condition = init_string,
  .end_condition = end_string,
  .include_end = true,
  .include_begin = true,
};

const TokenScanner op_scanner = { 
  .init_condition = init_op,
  .end_condition = end_op,
  .include_end = false,
  .include_begin = false,
};

const TokenScanner punctuation_scanner = { 
  .init_condition = init_punctuator,
  .end_condition = end_punctuator,
  .include_end = false,
  .include_begin = false,
};

const TokenScanner* scanners[] = { 
  &word_scanner, &literal_scanner, &string_scanner, 
  &op_scanner, &punctuation_scanner,
};

/*
 * Tokenize searches for tokens in the following order:
 * 1. Keywords & Identifiers 
 * 2. Literals
 * 3. Strings
 * 4. Operators
 * 5. Punctuation
 */
Vector tokenize(const char* line, uint32_t row) {
  Vector tokens;
  vec_init(&tokens);

  size_t len = strlen(line);

  for (size_t i = 0; i < len; i++) {
    if (is_delimiter(line[i], NULL)) continue;
    printf("entering at %d\n", i);

    TokenScanner* scanner = NULL;
    for (size_t j = 0; j < sizeof(scanners) / sizeof(scanners[0]); j++) {
      if (scanners[j]->init_condition(line[i])) {
        scanner = scanners[j];
        break;
      }
    }

    if (scanner == NULL) {
      printf("No suitable scanner found! (unrecognized starting character)\n");
      printf("at column %lu, row %d\n", i, row);
      continue;
    }

    // scan lexeme
    const char* lexeme = scan(*scanner, line, i, row);
    printf("lexeme: %s\n", lexeme);

    Token* tok = malloc(sizeof(Token));
    *tok = (Token){ .type = lookup_token_type(lexeme), 
      .token = lexeme, .column = i, .row = row };

    // handle literals manually
    if (scanner == &word_scanner && tok->type == INVALID) {
      tok->type = IDENTIFIER;
    } else if (scanner == &literal_scanner) {
      // TODO implement the dynamic scanner types (identifier, literals, strings)
    }

    assert(tok->token != NULL);
    vec_push(&tokens, tok);
    i += strlen(tok->token) - 1;
  }
  return tokens;
}

void print_token(Token* token) {
  printf("Token(type=%s, lexeme=%s, row=%u, col=%u)\n",
    token_type_name(token->type),
    token->token,
    token->row,
    token->column
  );
}

static TokenType lookup_token_type(const char* str) {
  for (size_t i = 0; token_lookup[i].lexeme != NULL; i++) {
    if (strcmp(token_lookup[i].lexeme, str) == 0) {
      return token_lookup[i].type;
    }
  }
  return INVALID; // default fallback when not recognized
}

static const char* token_type_name(TokenType type) {
  return token_names[type];
}

