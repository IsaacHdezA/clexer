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
  printf("(%d bytes) \"%s\"\n", size, buffer);
}

void error(int line, char *message) {
  report(line, "", message);
}

void report(int line, char *where, char *message) {
  fprintf(stderr, "[line %d] Error %s: %s\n", line, where, message);
  hadError = true;
}
