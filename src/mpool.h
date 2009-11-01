
/* written by C99 style */

#ifndef MPOOL_H
#define MPOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MPOOL_SIZE 72

#define MPOOL_MALLOC(p, siz)           \
  do {                                 \
    if (((p) = malloc(siz)) == NULL) { \
      printf("malloc failed");         \
      exit(-1);                        \
    }                                  \
  } while(false)

#define MPOOL_FREE(p)                           \
  do {                                          \
    free(p);                                    \
    (p) = NULL;                                 \
  } while(false)

typedef void mpool_data_t;

typedef struct mpool_t {
  mpool_data_t *data;
  mpool_data_t *begin;
  size_t usiz;
  size_t msiz;
  struct mpool_t *org;
  struct mpool_t *next;
} mpool_t;

mpool_t *mpool_create(size_t siz);
mpool_data_t *mpool_palloc(mpool_t **p, size_t siz);
void mpool_extend(mpool_t *p, size_t siz);
void mpool_destroy(mpool_t *p);


#endif


