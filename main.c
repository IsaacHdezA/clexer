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
void addToken(Scanner *scanner, TokenType type);
boolean match(Scanner *scanner, char c);

List *scanTokens(Scanner *scanner) {
  while(!isAtEnd(scanner)) {
    scanner->start = scanner->current;
    scanToken(scanner);
  }

  push(scanner->tokens, createToken("", EoF, scanner->line));
  return scanner->tokens;
}

void scanToken(Scanner *scanner) {
  char c = scanner->source[scanner->current++];

  switch(c) {
    case '(': addToken(scanner,  LEFT_PAREN ); break;
    case ')': addToken(scanner,  RIGHT_PAREN); break;
    case '{': addToken(scanner,  LEFT_BRACE ); break;
    case '}': addToken(scanner,  RIGHT_BRACE); break;
    case ',': addToken(scanner,  COMMA      ); break;
    case '.': addToken(scanner,  DOT        ); break;
    case '-': addToken(scanner,  MINUS      ); break;
    case '+': addToken(scanner,  PLUS       ); break;
    case ';': addToken(scanner,  SEMICOLON  ); break;
    // case '/': push(scanner, createCToken(c, SLASH,       scanner->line)); break;
    // case '*': push(scanner, createCToken(c, STAR,        scanner->line)); break;
    
    case '!':
        addToken(scanner, match(scanner, '=') ? BANG_EQUAL : BANG);
    break;

    case '=':
        addToken(scanner, match(scanner, '=') ? EQUAL_EQUAL : EQUAL);
    break;

    case '>':
        addToken(scanner, match(scanner, '=') ? GREATER_EQUAL : GREATER);
    break;

    case '<':
        addToken(scanner, match(scanner, '=') ? LESS_EQUAL : LESS);
    break;
    
    default:
      error(scanner->line, "Unexpected character");
    break;
  }
}

void addToken(Scanner *scanner, TokenType type) {
  char *token = substring(scanner->source, scanner->start, scanner->current);
  push(scanner->tokens, createToken(token, type,  scanner->line));
}


boolean isAtEnd(Scanner *scanner) {
  return scanner->current >= scanner->size;
}

boolean match(Scanner *scanner, char expected) {
  if(isAtEnd(scanner)) return false;
  if(scanner->source[scanner->current] != expected) return false;

  scanner->current++;
  return true;
}

void freeScanner(Scanner *scanner) {
  free(scanner->source);
  free(scanner->tokens);
  free(scanner);
}

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
  printList(scanTokens(scanner));
  freeScanner(scanner);
}
