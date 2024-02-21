#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define BUFFER_SIZE 256

void runFile(char *filename);
void runPrompt();

int main(int argc, char **argv) {
  if(argc > 2) {
    printf("Usage: clox [script]");
    return 64;
  } else if (argc == 2) runFile(argv[1]);
  else runPrompt();

  return 0;
}

void runFile(char *filename) {
  printf("Running file \"%s\"", filename);

  FILE *file = fopen(filename, "r");

  if(!file) {
    printf("[ERROR] Could not open file.\n");
    return;
  }
  printf("\n\n");

  // Get file character stream and run it

  fclose(file);
}

void runPrompt() {
  char buffer[BUFFER_SIZE] = { 0 };

  printf("Starting REPL...\n");
  printf("Lox > ");

  while(fgets(buffer, BUFFER_SIZE, stdin)) {
    run(buffer, strlen());
    printf("Lox > ");
  }

  printf("\n");
}

