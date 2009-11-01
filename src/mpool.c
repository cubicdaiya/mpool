
/* written by C99 style */

#include "mpool.h"

mpool_t *mpool_create (size_t siz) {
  if (siz <= 0) {
    siz = MPOOL_SIZE;
  }
  mpool_t *p;
  MPOOL_MALLOC(p, sizeof(mpool_t));
  MPOOL_MALLOC(p->data, siz);
  p->begin = p->data;
  p->usiz  = 0;
  p->msiz  = siz;
  p->org   = p;
  p->next  = NULL;
  return p;
}

void mpool_extend(mpool_t *p, size_t siz) {
  p->next = mpool_create(siz);
  p->next->org = p->org;
}

mpool_data_t *mpool_palloc(mpool_t **p, size_t siz) {
  mpool_t *pp = *p;
  size_t usiz = pp->usiz + siz;
  size_t msiz = pp->msiz;
  mpool_data_t *d = pp->begin;
  if (usiz > msiz) {
    mpool_extend(pp, usiz * 2);
    pp->next->usiz = usiz;
    d = pp->next->begin;
    *p = pp->next;
  } else {
    pp->usiz = usiz;
    pp->begin += siz;
  }
  return d;
}

void mpool_destroy (mpool_t *pool) {
  for (mpool_t *p=pool->org;p!=NULL;) {
    mpool_t *current = p;
    mpool_t *next    = p->next;
    MPOOL_FREE(current->data);
    MPOOL_FREE(current);
    p = next;
  }
}
