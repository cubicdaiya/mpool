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
static inline bool mpool_extend(mpool_pool_t *p, size_t siz, mpool_t *pool);
static inline size_t mpool_align(size_t siz);
static inline size_t mpool_decide_create_siz(size_t siz);

/**
 * create memory pool
 */
mpool_t *mpool_create (size_t siz) {
    mpool_t *pool;
    siz = mpool_decide_create_siz(siz);

    pool = malloc(sizeof(*pool));
    if (pool == NULL) {
        return NULL;
    }

    pool->mpool = malloc(sizeof(*pool->mpool));
    if (pool->mpool == NULL) {
        return NULL;
    }

    pool->mpool->pool = malloc(siz);
    if (pool->mpool->pool == NULL) {
        return NULL;
    }

    pool->mpool->next = NULL;

    pool->begin = pool->mpool->pool;
    pool->head  = pool->mpool;
    pool->usiz  = 0;
    pool->msiz  = siz;
    
    return pool;
}

/**
 * allocate memory from memory pool
 */
void *mpool_alloc(size_t siz, mpool_t *pool) {
    mpool_pool_t **p = &pool->mpool;
    mpool_pool_t *pp = *p;
    size_t usiz = mpool_align(pool->usiz + siz);
    size_t msiz = pool->msiz;
    void     *d = pool->begin;
    if (usiz > msiz) {
        if (!mpool_extend(pp, usiz * 2 + 1, pool)) {
            return NULL;
        }
        pool->usiz = 0;
        pool->msiz = usiz * 2;
        d = pool->begin;
        pool->begin += mpool_align(siz);
        *p = pp->next;
    } else {
        pool->usiz = usiz;
        pool->begin += mpool_align(siz);
    }
    
    return d;
}

/**
 * release all memory pool
 */
void mpool_destroy (mpool_t *pool) {
    for (mpool_pool_t *cur = pool->head, *next; cur; cur = next){
        next = cur->next;
        MPOOL_FREE(cur->pool);
        MPOOL_FREE(cur);
    }
    
    MPOOL_FREE(pool);
}

/* following is private function */ 

/**
 * extend memory pool
 */
static inline bool mpool_extend(mpool_pool_t *p, size_t siz, mpool_t *pool) {
    siz = mpool_decide_create_siz(siz);
    mpool_pool_t *pp;

    pp = malloc(sizeof(*pp));
    if (pp == NULL) {
        return false;
    }

    pp->pool = malloc(siz);
    if (pp->pool == NULL) {
        return false;
    }

    memset(pp->pool, 0, siz);
    
    pp->next = NULL;

    p->next = pp;

    pool->begin = pp->pool;

    return true;
}

/**
 * align byte boundary
 */
static inline size_t mpool_align(size_t siz) {
    return (siz + (MPOOL_ALIGN_SIZE - 1)) & ~(MPOOL_ALIGN_SIZE - 1);
}

/**
 * decide mpool size
 */
static inline size_t mpool_decide_create_siz(size_t siz) {
    return siz < 1 ? MPOOL_POOL_SIZ : mpool_align(siz);
}

