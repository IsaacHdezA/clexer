#include <stdio.h>
#include <string.h>
#include "./includes/utilities.h"

void runFile(char *filename);
void runPrompt();
void run(char *buffer, int size);

typedef struct token_t {
  char value[BUFFER_SIZE];
} Token;

Token *createToken(char *str) {
  int size = strlen(str);

  Token *token = myMalloc(Token, 1);

  memset(token, 0, sizeof(token));
  strncpy(token->value, str, size);

  return token;
}

void printToken(Token *token) {
  printf("\"%s\"", token->value);
}

typedef struct node_t {
  Token *token;
  struct node_t *next;
} Node;

Node *createNode(Token *token) {
  Node *node = myMalloc(Node, 1);
  memset(node, 0, sizeof(node));

  node->token = token;
  node->next = NULL;
  
  return node;
}

void freeNode(Node *node) {
  free(node->token);
  free(node);
}

void printNode(Node *node) {
  printf("Token: ");
  printToken(node->token);
}

typedef struct list_t {
  Node *head;

  int size;
} List;

List *createList() {
  List *list = myMalloc(List, 1);

  list->head = NULL;
  list->size = 0;

  return list;
}

void push(List *list, Token *token) {
  if(!list->head) {
    list->head = createNode(token);
    list->size++;

    return;
  }

  Node *aux = list->head;
  while(aux->next) aux = aux->next;

  aux->next = createNode(token);
  list->size++;

  return;
}

void printList(List *list) {
  Node *aux = list->head;

  printf("[");
  while(aux) {
    printNode(aux);
    if(aux->next) printf(", ");
    aux = aux->next;
  }
  printf("]\n");
}

void freeList(List *list) {
  Node *head = list->head, *aux = head->next;

  while(head) {
    aux = head;
    head = head->next;

    freeNode(aux);
  }

  free(list);
}

int main(int argc, char **argv) {
  Token *token1 = createToken("token 1"),
        *token2 = createToken("token 2"),
        *token3 = createToken("token 3");
  List *list = createList();

  push(list, token1);
  push(list, token2);
  push(list, token3);

  printf("List (%d): ", list->size);
  printList(list);

  freeList(list);

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

