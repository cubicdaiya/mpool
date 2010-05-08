#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/types.h>
#include <time.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <mpool.h>

#define IS_ALIGNED(ptr) ((uintptr_t)(ptr) % (MPOOL_ALIGN_SIZE) == 0)

static void mpool_test001(void);
static void mpool_test002(void);
static void mpool_test003(void);
static void mpool_test004(void);
static void mpool_test005(void);

static void mpool_test001(void){
    mpool_t pool;
    CU_ASSERT(mpool_create(0, &pool));
    char *c;
    c = mpool_alloc(sizeof(*c), &pool);
    *c = 'a';
    CU_ASSERT(*c == 'a');
    CU_ASSERT(IS_ALIGNED(c));
    mpool_destroy(&pool);
}

static void mpool_test002(void){
    mpool_t pool;
    CU_ASSERT(mpool_create(0, &pool));
    char *c1;
    char *c2;
    char *c3;
    char *c4;
    char *c5;
    c1 = mpool_alloc(sizeof(*c1), &pool);
    c2 = mpool_alloc(sizeof(*c2), &pool);
    c3 = mpool_alloc(sizeof(*c3), &pool);
    c4 = mpool_alloc(sizeof(*c4), &pool);
    c5 = mpool_alloc(sizeof(*c5), &pool);
    *c1 = 'a';
    *c2 = 'b';
    *c3 = 'c';
    *c4 = 'd';
    *c5 = 'e';
    CU_ASSERT(*c1 == 'a');
    CU_ASSERT(*c2 == 'b');
    CU_ASSERT(*c3 == 'c');
    CU_ASSERT(*c4 == 'd');
    CU_ASSERT(*c5 == 'e');

    CU_ASSERT(IS_ALIGNED(c1));
    CU_ASSERT(IS_ALIGNED(c2));
    CU_ASSERT(IS_ALIGNED(c3));
    CU_ASSERT(IS_ALIGNED(c4));
    CU_ASSERT(IS_ALIGNED(c5));

    mpool_destroy(&pool);
}

static void mpool_test003(void){
    mpool_t pool;
    CU_ASSERT(mpool_create(0, &pool));
    bool               *b;
    short              *s;
    char               *c;
    unsigned char      *uc;
    int                *n;
    unsigned int       *un;
    long               *l;
    unsigned long      *ul;
    long long          *ll;
    unsigned long long *ull;
    float              *f;
    double             *d;
    long double        *ld;
    time_t             *t;
    off_t              *ot;
    intptr_t           *ipt;
    size_t             *siz;
    ptrdiff_t          *pdt;
    
    b   = mpool_alloc(sizeof(*b),   &pool);
    s   = mpool_alloc(sizeof(*s),   &pool);
    c   = mpool_alloc(sizeof(*c),   &pool);
    uc  = mpool_alloc(sizeof(*uc),  &pool);
    n   = mpool_alloc(sizeof(*n),   &pool);
    un  = mpool_alloc(sizeof(*un),  &pool);
    l   = mpool_alloc(sizeof(*l),   &pool);
    ul  = mpool_alloc(sizeof(*ul),  &pool);
    ll  = mpool_alloc(sizeof(*ll),  &pool);
    ull = mpool_alloc(sizeof(*ull), &pool);
    f   = mpool_alloc(sizeof(*f),   &pool);
    d   = mpool_alloc(sizeof(*d),   &pool);
    ld  = mpool_alloc(sizeof(*ld),  &pool);
    t   = mpool_alloc(sizeof(*t),   &pool);
    ot  = mpool_alloc(sizeof(*ot),  &pool);
    ipt = mpool_alloc(sizeof(*ipt), &pool);
    siz = mpool_alloc(sizeof(*siz), &pool);
    pdt = mpool_alloc(sizeof(*pdt), &pool);
    
    *b   = true;
    *s   = 2;
    *c   = 'a';
    *uc  = 'b';
    *n   = 5;
    *un  = 255;
    *l   = 550;
    *ul  = 333;
    *ll  = 950;
    *ull = 111;
    *f   = 113.5;
    *d   = 50.8;
    *ld  = 115.3;
    *t   = 123;
    *ot  = 22;
    *ipt = 33;
    *siz = 55;
    *pdt = 150;
    
    CU_ASSERT(*b   == true);
    CU_ASSERT(*s   == 2);
    CU_ASSERT(*c   == 'a');
    CU_ASSERT(*uc  == 'b');
    CU_ASSERT(*n   == 5);
    CU_ASSERT(*un  == 255);
    CU_ASSERT(*l   == 550);
    CU_ASSERT(*ul  == 333);
    CU_ASSERT(*ll  == 950);
    CU_ASSERT(*ull == 111);
    CU_ASSERT(*f   == 113.5);
    CU_ASSERT(*d   == 50.8);
    CU_ASSERT(*ld  == 115.3);
    CU_ASSERT(*t   == 123);
    CU_ASSERT(*ot  == 22);
    CU_ASSERT(*ipt == 33);
    CU_ASSERT(*siz == 55);
    CU_ASSERT(*pdt == 150);

    CU_ASSERT(IS_ALIGNED(b));
    CU_ASSERT(IS_ALIGNED(s));
    CU_ASSERT(IS_ALIGNED(c));
    CU_ASSERT(IS_ALIGNED(uc));
    CU_ASSERT(IS_ALIGNED(n));
    CU_ASSERT(IS_ALIGNED(un));
    CU_ASSERT(IS_ALIGNED(l));
    CU_ASSERT(IS_ALIGNED(ul));
    CU_ASSERT(IS_ALIGNED(ll));
    CU_ASSERT(IS_ALIGNED(ull));
    CU_ASSERT(IS_ALIGNED(f));
    CU_ASSERT(IS_ALIGNED(d));
    CU_ASSERT(IS_ALIGNED(ld));
    CU_ASSERT(IS_ALIGNED(t));
    CU_ASSERT(IS_ALIGNED(ot));
    CU_ASSERT(IS_ALIGNED(ipt));
    CU_ASSERT(IS_ALIGNED(siz));
    CU_ASSERT(IS_ALIGNED(pdt));

    mpool_destroy(&pool);
}

static void mpool_test004(void){
    mpool_t pool;
    CU_ASSERT(mpool_create(10, &pool));
    const char *cs[] = {"cubicdaiya", "bokko"};
    char *s1;
    char *s2;
    
    s1 = mpool_alloc(strlen(cs[0]) + 1, &pool);
    s2 = mpool_alloc(strlen(cs[1]) + 1, &pool);
    strcpy(s1, cs[0]);
    strcpy(s2, cs[1]);
    CU_ASSERT(strncmp(s1, cs[0], strlen(s1)) == 0);
    CU_ASSERT(strncmp(s2, cs[1], strlen(s2)) == 0);
    CU_ASSERT(IS_ALIGNED(s1));
    CU_ASSERT(IS_ALIGNED(s2));
    
    mpool_destroy(&pool);
}

static void mpool_test005(void){
    mpool_t pool;
    CU_ASSERT(mpool_create(10, &pool));
    
    typedef struct st_s {
        int  n;
        char c;
    } st_t;
    
    st_t *st;
    int *n;
    st = mpool_alloc(sizeof(*st), &pool);
    n  = mpool_alloc(sizeof(*n), &pool);
    
    st->n = 5;
    st->c = 'a';
    *n    = 10;
    
    CU_ASSERT(st->n == 5);
    CU_ASSERT(st->c == 'a');
    CU_ASSERT(*n    == 10);

    CU_ASSERT(IS_ALIGNED(st));
    CU_ASSERT(IS_ALIGNED(n));
    
    mpool_destroy(&pool);
}

int main (int argc, char *argv[]) {
    CU_pSuite suite_mpool;
    CU_initialize_registry();
    suite_mpool = CU_add_suite("mpool", NULL, NULL);
    CU_add_test(suite_mpool, "mpool_test001", mpool_test001);
    CU_add_test(suite_mpool, "mpool_test002", mpool_test002);
    CU_add_test(suite_mpool, "mpool_test003", mpool_test003);
    CU_add_test(suite_mpool, "mpool_test004", mpool_test004);
    CU_add_test(suite_mpool, "mpool_test005", mpool_test005);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
