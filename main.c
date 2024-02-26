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

void addToken(List *list, TokenType type, char *source) {
  // TODO: Change substring again so it returns a string ffs.
  //       That means changing trim again god dammit
  // push(
  //     list,
  //     createToken(
  //       substring(source, start, current)
  //       type,
  //       line
  //     )
  // );
}

void scanToken(List *tokens, char *source, int length) {
  char c = source[current++];

  switch(c) {}

}

List *scanTokens(char *source, int length) {
  List *tokens = createList();

  while(current <= length) {
    start = current;
    scanToken(tokens, source, length);
  }

  push(tokens, createToken("", EoF, line));
}

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
  printf("Initializing scanner...\n");
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
