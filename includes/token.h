#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>
#include "../includes/utilities.h"

typedef enum token_e {
  // Single-character tokens
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals
  IDENTIFIER, STRING, NUMBER,

  // Keywords
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  EoF
} TokenType;

typedef struct token_t {
  TokenType type;
  char *lexeme;
  float literal;
  int line;

} Token;

Token *createToken(char *str, TokenType type, int line);
Token *createCToken(char c, TokenType type, int line);
void printToken(Token *token);
void freeToken(Token *token);

#endif
