#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/list.h"

char *tokenNames[39] = {
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
  "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",

  "BANG", "BANG_EQUAL",
  "EQUAL", "EQUAL_EQUAL",
  "GREATER", "GREATER_EQUAL",
  "LESS", "LESS_EQUAL",

  "IDENTIFIER", "STRING", "NUMBER",

  "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR",
  "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",

  "EOF"
};

// Token functions
Token *createToken(char *str, TokenType type) {
  int size = strlen(str);

  Token *token = myMalloc(Token, 1);
  memset(token, 0, sizeof(Token));

  strncpy(token->lexeme, str, size);
  token->type = type;
  if(type == NUMBER) token->literal = atof(token->lexeme);
  else token->literal = -1;

  return token;
}

void printToken(Token *token) {
  printf("[%s] \"%s\"", tokenNames[token->type], token->lexeme);
  if(token->type == NUMBER) printf(" (%f)", token->literal);
  // printf("[%ud] \"%s\"", token->type, token->lexeme);
}

// Node functions
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
  printToken(node->token);
}

// List functions
List *createList() {
  List *list = myMalloc(List, 1);

  list->head = NULL;
  list->size = 0;

  return list;
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
}

Node *pop(List *list) {
  Node *node = list->head, *popped = node->next;

  while(popped->next) {
    node = node->next;
    popped = node->next;
  }

  node->next = NULL;
  list->size--;

  return popped;
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

