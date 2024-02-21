#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros
#define isWhitespace(c) (\
                          (c == '\t') ||\
                          (c == '\n') ||\
                          (c == '\v') ||\
                          (c == '\f') ||\
                          (c == '\r') ||\
                          (c ==  ' ')\
                        )

// Constants
#define BUFFER_SIZE 256

int rtrim(char *str, int len);
int ltrim(char *str, int len);
void trim(char *dest, char *src);
void substring(char *dest, char *src, int start, int end);

void runFile(char *filename);
void runPrompt();
void run(char *buffer, int size);

int main(int argc, char **argv) {
  if(argc > 2) {
    printf("Usage: clox [script]");
    return 64;
  } else if (argc == 2) runFile(argv[1]);
  else runPrompt();

  return 0;
}

int ltrim(char *str, int len) {
  int start = 0;
  while(isWhitespace(str[start])) start++;

  return start;
}

int rtrim(char *str, int len) {
  int end = len;
  while(isWhitespace(str[end]) || str[end] == '\0') end--;

  return end + 1;
}


void substring(char *dest, char *src, int start, int end) {
  int i = 0;
  for (i = 0; i < (end - start); i++) dest[i] = src[i + start];
  dest[i] = '\0';
}

void trim(char *dest, char *src) {
  if(src[0] == '\n') {
    src[0] = '\0';
    return;
  }

  int len   = strlen(src) - 1,
      start = ltrim(src, len),
      end   = rtrim(src, len);

  substring(dest, src, start, end);
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

  // Get file character stream and run it

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

