
/* written by C99 style */

#ifndef MPOOL_H
#define MPOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MPOOL_SIZE 72

#define MPOOL_MALLOC(p, n)             \
  do {                                 \
    if (((p) = malloc(n)) == NULL) {   \
      printf("malloc failed");         \
      exit(-1);                        \
    }                                  \
  } while(false)

#define MPOOL_REALLOC(p, n)             \
  do {                                  \
    if (((p) = realloc(p, n)) == NULL) { \
      printf("realloc failed");         \
      exit(-1);                         \
    }                                   \
  } while(false)

#define MPOOL_FREE(p)                           \
  do {                                          \
    free(p);                                    \
    (p) = NULL;                                 \
  } while(false)

typedef void mpool_data_t;

typedef struct mpool_t {
  mpool_data_t *data;
  mpool_data_t *org;
  mpool_data_t *begin;
  size_t usiz;
  size_t msiz;
} mpool_t;

mpool_t *mpool_create();
mpool_data_t *mpool_palloc(mpool_t **p, size_t siz);
mpool_t *mpool_extend(mpool_t *p, size_t siz);
void mpool_destroy(mpool_t *p);


#endif


