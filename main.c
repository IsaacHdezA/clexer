#include <stdio.h>
#include <string.h>

#include "./includes/list.h"
#include "./includes/token.h"
#include "./includes/utilities.h"

typedef struct scanner_t {
  char *source;
  List *tokens;
  int size;

  int start;
  int current;
  int line;

} Scanner;

Scanner *createScanner(char *source) {
  Scanner *scanner = myMalloc(Scanner, 1);
  memset(scanner, 0, sizeof(Scanner));

  // scanner->source = source; // Might only copy it

  scanner->size = strlen(source);

  scanner->source = myMalloc(char, scanner->size + 1);
  memset(scanner->source, 0, scanner->size + 1);
  strncpy(scanner->source, source, scanner->size + 1);

  scanner->tokens = createList();
  scanner->start = 0;
  scanner->current = 0;
  scanner->line = 1;

  return scanner;
}

Scanner *createScanner(char *source);
void freeScanner(Scanner *scanner);
boolean isAtEnd(Scanner *scanner);
List *scanTokens(Scanner *scanner);
void scanToken(Scanner *scanner);

List *scanTokens(Scanner *scanner) {
  while(!isAtEnd(scanner)) {
    scanner->start = scanner->current;
    scanToken(scanner);
    printList(scanner->tokens);
  }
}

void scanToken(Scanner *scanner) {
  char c = scanner->source[scanner->current++];

  switch(c) {
    case '(': push(scanner->tokens, createCToken(c, LEFT_PAREN,  scanner->line)); break;
    case ')': push(scanner->tokens, createCToken(c, RIGHT_PAREN, scanner->line)); break;
    case '{': push(scanner->tokens, createCToken(c, LEFT_BRACE,  scanner->line)); break;
    case '}': push(scanner->tokens, createCToken(c, RIGHT_BRACE, scanner->line)); break;
    case ',': push(scanner->tokens, createCToken(c, COMMA,       scanner->line)); break;
    case '.': push(scanner->tokens, createCToken(c, DOT,         scanner->line)); break;
    case '-': push(scanner->tokens, createCToken(c, MINUS,       scanner->line)); break;
    case '+': push(scanner->tokens, createCToken(c, PLUS,        scanner->line)); break;
    case ';': push(scanner->tokens, createCToken(c, SEMICOLON,   scanner->line)); break;
    // case '/': push(scanner->tokens, createCToken(c, SLASH,       scanner->line)); break;
    // case '*': push(scanner->tokens, createCToken(c, STAR,        scanner->line)); break;
  }
}

boolean isAtEnd(Scanner *scanner) {
  return scanner->current >= scanner->size;
}

void freeScanner(Scanner *scanner) {
  free(scanner->source);
  free(scanner->tokens);
  free(scanner);
}

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

void runFile(char *filename) {
  trim(filename, filename);
  printf("Running file \"%s\"... ", filename);

  FILE *file = fopen(filename, "r");

  if(!file) {
    printf("[ERROR] Could not open file.\n");
    return;
  }
  printf("\n\n");

  int buffSize = 0;
  char *buffer = getFileStream(file, &buffSize);

  trim(buffer, buffer);
  buffSize = strlen(buffer);

  run(buffer, buffSize);

  free(buffer);
  fclose(file);
}

void runPrompt() {
  char buffer[BUFFER_SIZE] = { 0 };

  printf("Starting REPL...\n");
  printf("Lox > ");

  while(fgets(buffer, BUFFER_SIZE, stdin)) {
    trim(buffer, buffer);
    run(buffer, strlen(buffer));
    printf("Lox > ");

    hadError = false;
  }

  printf("\n");
}

void run(char *buffer, int size) {
  Scanner *scanner = createScanner(buffer);
  scanTokens(scanner);
  freeScanner(scanner);
}


void error(int line, char *message) {
  report(line, "", message);
}

void report(int line, char *where, char *message) {
  fprintf(stderr, "[line %d] Error %s: %s\n", line, where, message);
  hadError = true;
}
