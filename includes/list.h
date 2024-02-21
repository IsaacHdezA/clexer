#ifndef LIST_H
#define LIST_H

#include "../includes/utilities.h"

typedef struct token_t {
  char value[BUFFER_SIZE];
} Token;

Token *createToken(char *str);
void printToken(Token *token);

typedef struct node_t {
  Token *token;
  struct node_t *next;
} Node;

Node *createNode(Token *token);
void freeNode(Node *node);

void printNode(Node *node);

typedef struct list_t {
  Node *head;

  int size;
} List;

List *createList();
void freeList(List *list);

void push(List *list, Token *token);
Node *pop(List *list);

void printList(List *list);

#endif // !LIST_H
