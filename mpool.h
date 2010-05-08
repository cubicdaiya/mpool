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

#ifndef MPOOL_H
#define MPOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MPOOL_POOL_SIZ   (64 * 1024)
#define MPOOL_ALIGN_SIZE (8)

#define MPOOL_MALLOC(p, siz)                    \
    do {                                        \
        if (((p) = malloc(siz)) == NULL) {      \
            fprintf(stderr, "malloc failed");   \
            exit(-1);                           \
        }                                       \
    } while(false)

#define MPOOL_FREE(p)                           \
    do {                                        \
        free(p);                                \
        (p) = NULL;                             \
    } while(false)

typedef void mpool_pool_t;

/**
 * memory pool structure
 */
typedef struct mpool_t {
    mpool_pool_t   *pool;     // memory pool field
    struct mpool_t *next;     // next memory pool's pointer
} mpool_t;

typedef struct mpool_manager_t {
    mpool_t      *head;       // memory pool's head
    mpool_pool_t *begin;      // data for internal conduct
    size_t        usiz;       // used pool size of current pool
    size_t        msiz;       // max pool size of current pool
    mpool_t      *mpool;      // memory pool struct's pointer
} mpool_manager_t;

bool mpool_create (size_t siz, mpool_manager_t *manager);
mpool_pool_t *mpool_alloc(size_t siz, mpool_manager_t *manager);
void mpool_destroy (mpool_manager_t *manager);

#endif


