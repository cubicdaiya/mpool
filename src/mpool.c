
/* written by C99 style */

#include "mpool.h"

mpool_t *mpool_create () {
  mpool_t *p;
  MPOOL_MALLOC(p, sizeof(mpool_t));
  MPOOL_MALLOC(p->data, MPOOL_SIZE);
  p->begin = p->data;
  p->org   = p->data;
  p->usiz  = 0;
  p->msiz  = MPOOL_SIZE;
  return p;
}

mpool_t *mpool_extend(mpool_t *p, size_t siz) {
  MPOOL_REALLOC(p->data, siz);
  return p;
}

mpool_data_t *mpool_palloc(mpool_t **p, size_t siz) {
  mpool_t *pp = *p;
  size_t usiz = pp->usiz + siz;
  size_t msiz = pp->msiz;
  if (usiz > msiz) {
    mpool_extend(pp, usiz * 2);
    pp->msiz = usiz * 2;
  }
  pp->usiz += siz;
  mpool_data_t *d = pp->begin;
  if (pp->data == pp->org) {
    pp->begin += siz;
  } else {
    pp->begin += siz + 1;
  }
  return d;
}

void mpool_destroy (mpool_t *p) {
  MPOOL_FREE(p->org);
  MPOOL_FREE(p);
}
