#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>

// Macros
#define myMalloc(type, len) ((type *) malloc(sizeof(type) * len))
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

// Enums
typedef enum enum_e {
  false = 0,
  true = 1
} boolean;

// Custom string handling
int rtrim(char *str, int len);
int ltrim(char *str, int len);
void trim(char *dest, char *src);
void substring(char *dest, char *src, int start, int end);
char *getFileStream(FILE *file, int *len);

#endif
