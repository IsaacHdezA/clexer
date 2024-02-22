#include <stdio.h>
#include <string.h>
#include "../includes/utilities.h"

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

char *getFileStream(FILE *file, int *len) {
  char fileBuffer[BUFFER_SIZE] = { 0 };
  *len = 0;

  while(fgets(fileBuffer, BUFFER_SIZE, file)) *len += strlen(fileBuffer);
  rewind(file);

  char *buffer = myMalloc(char, ++(*len));
  memset(buffer, 0, *len);
  while(fgets(fileBuffer, BUFFER_SIZE, file))
    strncat(buffer, fileBuffer, strlen(fileBuffer));

  return buffer;
}

char *char2str(char c) {
  char *str = myMalloc(char, 1);
  memset(str, 0, sizeof(char));
  str[0] = c;

  return str;
}
