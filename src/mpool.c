/**
 In short, mpool is distributed under so called "BSD license",
 
 Copyright (c) 2009-2010 Tatsuhiko Kubo <cubicdaiya@gmail.com>
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:
 
    * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
 
    * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
 
    * Neither the name of the authors nor the names of its contributors
    may be used to endorse or promote products derived from this software 
    without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* written by C99 style */

#include "mpool.h"

/**
 * private function
 */
static void mpool_extend(mpool_t *p, size_t siz);
static size_t mpool_align(size_t siz);

/**
 * create memory pool
 */
mpool_t *mpool_create (size_t siz) {
  if (siz <= 0) {
    siz = MPOOL_DEFAULT_SIZE;
  } else {
    siz = mpool_align(siz);
  }
  mpool_t *p;
  MPOOL_MALLOC(p, sizeof(mpool_t));
  MPOOL_MALLOC(p->pool, siz);
  p->begin = p->pool;
  p->usiz  = 0;
  p->msiz  = siz;
  p->head  = p;
  p->next  = NULL;
  return p;
}

/**
 * allocate memory from memory pool
 */
mpool_pool_t *mpool_alloc(mpool_t **p, size_t siz) {
  mpool_t *pp = *p;
  size_t usiz = mpool_align(pp->usiz + siz);
  size_t msiz = pp->msiz;
  mpool_pool_t *d = pp->begin;
  if (usiz > msiz) {
    mpool_extend(pp, usiz * 2);
    pp->next->usiz = usiz;
    d = pp->next->begin;
    pp->next->begin += siz;
    *p = pp->next;
  } else {
    pp->usiz = usiz;
    pp->begin += siz;
  }
  
  return d;
}

/**
 * release all memory pool
 */
void mpool_destroy (mpool_t *pool) {
  for (mpool_t *p=pool->head;p!=NULL;) {
    mpool_t *current = p;
    mpool_t *next    = p->next;
    MPOOL_FREE(current->pool);
    MPOOL_FREE(current);
    p = next;
  }
}

/* following is private function */ 

/**
 * extend memory pool
 */
static void mpool_extend(mpool_t *p, size_t siz) {
  p->next = mpool_create(siz);
  p->next->head = p->head;
}

/**
 * align byte boundary
 */
static size_t mpool_align(size_t siz) {
  size_t siz_padding = siz % MPOOL_ALIGN_SIZE;
  size_t siz_aligned;
  if (siz_padding == 0) {
    siz_aligned = siz;
  } else if (siz == siz_padding) {
    siz_aligned = MPOOL_ALIGN_SIZE;
  } else {
    siz_aligned = siz + siz_padding;
  }
  return siz_aligned;
}

