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
static inline void mpool_extend(mpool_t *p, size_t siz, mpool_manager_t *manager);
static inline size_t mpool_align(size_t siz);

/**
 * create memory pool
 */
mpool_t *mpool_create (size_t siz, mpool_manager_t *manager) {
    if (siz <= 0) {
        siz = MPOOL_POOL_SIZ;
    } else {
        siz = mpool_align(siz);
    }
    mpool_t *p;
    MPOOL_MALLOC(p, sizeof(mpool_t));
    MPOOL_MALLOC(p->pool, siz);
    p->next = NULL;

    manager->begin = p->pool;
    manager->head  = p;
    manager->usiz  = 0;
    manager->msiz  = siz;
    
    return p;
}

/**
 * allocate memory from memory pool
 */
mpool_pool_t *mpool_alloc(mpool_t **p, size_t siz, mpool_manager_t *manager) {
    mpool_t *pp = *p;
    size_t usiz = mpool_align(manager->usiz + siz);
    size_t msiz = manager->msiz;
    mpool_pool_t *d = manager->begin;
    if (usiz > msiz) {
        mpool_extend(pp, usiz * 2, manager);
        manager->usiz = usiz;
        d = manager->begin;
        manager->begin += mpool_align(siz);
        *p = pp->next;
    } else {
        manager->usiz = usiz;
        manager->begin += mpool_align(siz);
    }
    
    return d;
}

/**
 * release all memory pool
 */
void mpool_destroy (mpool_manager_t *manager) {
    for (mpool_t *p=manager->head;p!=NULL;) {
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
static inline void mpool_extend(mpool_t *p, size_t siz, mpool_manager_t *manager) {
    if (siz <= 0) {
        siz = MPOOL_POOL_SIZ;
    } else {
        siz = mpool_align(siz);
    }
    mpool_t *pp;
    MPOOL_MALLOC(pp, sizeof(mpool_t));
    MPOOL_MALLOC(pp->pool, siz);
    pp->next = NULL;

    p->next = pp;

    manager->begin = pp->pool;
}

/**
 * align byte boundary
 */
static inline size_t mpool_align(size_t siz) {
    return (siz + (MPOOL_ALIGN_SIZE - 1)) & ~(MPOOL_ALIGN_SIZE - 1);
}

