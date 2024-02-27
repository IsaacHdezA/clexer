#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/token.h"
#include "../includes/list.h"

// Node functions
Node *createNode(Token *token) {
  Node *node = myMalloc(Node, 1);
  memset(node, 0, sizeof(node));

  node->token = token;
  node->next = NULL;
  
  return node;
}

void freeNode(Node *node) {
  freeToken(node->token);
  free(node);
}

void printNode(Node *node) {
  printToken(node->token);
}

// List functions
List *createList() {
  List *list = myMalloc(List, 1);
  memset(list, 0, sizeof(List));

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

