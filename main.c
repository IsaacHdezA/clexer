#include <stdio.h>
#include <string.h>
#include "./includes/utilities.h"
#include "./includes/list.h"

void runFile(char *filename);
void runPrompt();
void run(char *buffer, int size);

int main(int argc, char **argv) {
  List *list = createList();

  push(list, createToken("token 1"));
  push(list, createToken("token 2"));
  push(list, createToken("token 3"));

  printf("List (%d): ", list->size);
  printList(list);

  Node *popped = pop(list);
  printNode(popped);
  printf("\n");

  printf("List (%d): ", list->size);
  printList(list);

  freeList(list);
  freeNode(popped);

  // if(argc > 2) {
  //   printf("Usage: clox [script]");
  //   return 64;
  // } else if (argc == 2) runFile(argv[1]);
  // else runPrompt();

  return 0;
}

void runFile(char *filename) {
  trim(filename, filename);
  printf("Running file \"%s\"", filename);

  FILE *file = fopen(filename, "r");

  if(!file) {
    printf("[ERROR] Could not open file.\n");
    return;
  }
  printf("\n\n");

  int buffSize = 0;
  char *buffer = getFileStream(file, &buffSize);

  trim(buffer, buffer);
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
  }

  printf("\n");
}

void run(char *buffer, int size) {
  printf("(%d bytes) \"%s\"\n", size, buffer);
}

