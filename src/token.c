#include "../includes/token.h"

char *tokenNames[39] = {
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
  "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",

  "BANG", "BANG_EQUAL",
  "EQUAL", "EQUAL_EQUAL",
  "GREATER", "GREATER_EQUAL",
  "LESS", "LESS_EQUAL",

  "IDENTIFIER", "STRING", "NUMBER",

  "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR",
  "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",

  "EOF"
};

// Token functions
Token *createToken(char *str, TokenType type, int line) {
  int size = strlen(str);

  Token *token = myMalloc(Token, 1);
  memset(token, 0, sizeof(Token));

  token->lexeme = myMalloc(char, size + 1);
  memset(token->lexeme, 0, size + 1);
  strncpy(token->lexeme, str, size);

  token->type = type;
  token->line = line;

  if(type == NUMBER) token->literal = atof(token->lexeme);
  else token->literal = -1;

  return token;
}

void printToken(Token *token) {
  printf("[%s] \"%s\"", tokenNames[token->type], token->lexeme);
  if(token->type == NUMBER) printf(" (%f)", token->literal);
}

void freeToken(Token *token) {
  free(token->lexeme);
  free(token);
}
