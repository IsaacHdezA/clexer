#include <stdio.h>
#include <string.h>
#include "./includes/list.h"
#include "./includes/utilities.h"

// Global variables
boolean hadError;

void runFile(char *filename);
void runPrompt();
void run(char *buffer, int size);

void error(int line, char *message);
void report(int line, char *where, char *message);

int main(int argc, char **argv) {
  if(argc > 2) {
    printf("Usage: clox [script]");
    return 64;
  } else if (argc == 2) {
    runFile(argv[1]);

    if(hadError) return 65;
  } else runPrompt();

  return 0;
}

// Scanner
int start = 0;
int current = 0;
int line = 1;

char peek(char *source, int length);
char advance(char *source, int length);
boolean match(char expected, char *source, int length);

void string(List *tokens, char *source, int length);

void addToken(List *tokens, TokenType type, char *source);
void scanToken(List *tokens, char *source, int length);
List *scanTokens(char *source, int length);

List *scanTokens(char *source, int length) {
  List *tokens = createList();

  while(current <= length) {
    start = current;
    scanToken(tokens, source, length);
  }

  push(tokens, createToken("", EoF, line));
}

void scanToken(List *tokens, char *source, int length) {
  char c = advance(source, length);

  switch(c) {
    case '(': addToken(tokens, LEFT_PAREN,  source); break;
    case ')': addToken(tokens, RIGHT_PAREN, source); break;
    case '{': addToken(tokens, LEFT_BRACE,  source); break;
    case '}': addToken(tokens, RIGHT_BRACE, source); break;
    case ',': addToken(tokens, COMMA,       source); break;
    case '.': addToken(tokens, DOT,         source); break;
    case '-': addToken(tokens, MINUS,       source); break;
    case '+': addToken(tokens, PLUS,        source); break;
    case ';': addToken(tokens, SEMICOLON,   source); break;
    case '*': addToken(tokens, STAR,        source); break;

    case '!':
      addToken( tokens, match('=', source, length) ? BANG_EQUAL : BANG, source);
    break;

    case '=':
      addToken(tokens, match('=', source, length) ? EQUAL_EQUAL : EQUAL, source);
    break;

    case '<':
      addToken(tokens, match('=', source, length) ? LESS_EQUAL : LESS, source);
    break;

    case '>':
      addToken(tokens, match('=', source, length) ? GREATER_EQUAL : GREATER, source);
    break;

    case '/':
      if(match('/', source, length)) {
        // A comment goes until the end of the line
        while(peek(source, length) != '\n' && current <= length) advance(source, length);
      } else addToken(tokens, SLASH, source);
    break;

    // TODO: Fix trim function so it doesn't fucking break when entering a single space
    case ' ':
    case '\r':
    case '\t':
    break;

    case '\n': line++; break;

    case '"':
      string(tokens, source, length); break;
    break;

    default: error(line, "Unexpected character."); break;
  }
}

void addToken(List *list, TokenType type, char *source) {
  char *str = substring(source, start, current);
  push(
      list,
      createToken(
        str,
        type,
        line
      )
  );
  free(str);
}

// Like advance but without consuming the character (only lookahead)
char peek(char *source, int length) {
  if(current >= length) return '\n';
  return source[current];
}

// Consumes the current character
char advance(char *source, int length) {
  return source[current++];
}

// peek() + advance()
boolean match(char expected, char *source, int length) {
  if(current >= length) return false;
  if(source[current] != expected) return false;

  current++;
  return true;
}

// TODO: Fix that weird "error" that pops when inserting strings
void string(List *tokens, char *source, int length) {
  while(peek(source, length) != '"' && current <= length) {
    if(peek(source, length) == '\n') line++;
    advance(source, length);
  }

  if(current >= length) {
    error(line, "Unterminated string.");
    return;
  }

  // The closing ".
  advance(source, length);

  char *str = substring(source, start + 1, current - 1);
  push(
      tokens,
      createToken(
        str,
        STRING,
        line
      )
  );
  free(str);
}
// End scanner

void runFile(char *filename) {
  filename = trim(filename);
  printf("Running file \"%s\"... ", filename);

  FILE *file = fopen(filename, "r");

  if(!file) {
    printf("[ERROR] Could not open file.\n");
    free(filename);

    return;
  }
  printf("\n\n");

  int buffSize = 0;
  char *buffer = getFileStream(file, &buffSize);

  char *aux = buffer; // So we don't lose the original pointer

  buffer = trim(buffer);
  buffSize = strlen(buffer);

  run(buffer, buffSize);

  // Freeing allocated memory
  free(filename);

  free(aux);
  free(buffer);

  fclose(file);
}

void runPrompt() {
  char *buffer = myMalloc(char, BUFFER_SIZE),
       *aux = buffer;

  printf("Starting REPL...\n");
  printf("Lox > ");

  while(fgets(buffer, BUFFER_SIZE, stdin)) {
    buffer = trim(buffer);

    run(buffer, strlen(buffer));
    printf("Lox > ");

    hadError = false;

    // Restarting the buffers
    free(aux);
    free(buffer);

    buffer = myMalloc(char, BUFFER_SIZE);
    aux = buffer;
  }

  printf("\n");
  free(buffer);
}

void run(char *buffer, int size) {
  // Initialize scanner
  start = 0;
  current = 0;
  line = 1;
  List *tokens = scanTokens(buffer, size);

  printf("(%d bytes) \"%s\"\n\tTokens: ", size, buffer);
  printList(tokens);

  // Freeing scanner
  freeList(tokens);
}

void error(int line, char *message) {
  report(line, "", message);
}

void report(int line, char *where, char *message) {
  fprintf(stderr, "[line %d] Error %s: %s\n", line, where, message);
  hadError = true;
}
