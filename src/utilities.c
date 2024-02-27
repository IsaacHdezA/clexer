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

char *substring(char *src, int start, int end) {
  int size = (end - start);
  char *dest = myMalloc(char, size + 1);
  memset(dest, 0, size + 1);

  int i = 0;
  for (i = 0; i < size; i++) dest[i] = src[i + start];
  dest[i] = '\0';

  return dest;
}

char *trim(char *src) {
  char *out = NULL;

  if(src[0] == '\n' || src[0] == '\0') {
    out = myMalloc(char, 1);
    out[0] = '\0';

    return out;
  }
  
  int len = strlen(src),
      start = ltrim(src, len),
      end   = rtrim(src, len);

  out = substring(src, start, end);
  
  return out;
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

