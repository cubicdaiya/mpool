#include <stdio.h>
#include <string.h>
#include <mpool.h>

int main (int argc, char *argv[]) {
  
  mpool_t *pool;
  int  *n  = NULL;
  int  *m  = NULL;
  char *c  = NULL;
  char *s1 = NULL;
  char *s2 = NULL;
  const char *name[] = {"bokko", "cubicdaiya"};
  pool = mpool_create(0);
  n    = mpool_alloc(&pool, sizeof(int));
  m    = mpool_alloc(&pool, sizeof(int));
  c    = mpool_alloc(&pool, sizeof(char));
  s1   = mpool_alloc(&pool, strlen(name[0]) + 1);
  s2   = mpool_alloc(&pool, strlen(name[1]) + 1);
  *n   = 5;
  *m   = 10;
  *c   = 'a';
  strncpy(s1, name[0], strlen(name[0]) + 1);
  strncpy(s2, name[1], strlen(name[1]) + 1);
  printf("n  = %d\n", *n);
  printf("m  = %d\n", *m);
  printf("c  = %c\n", *c);
  printf("s1 = %s\n", s1);
  printf("s2 = %s\n", s2);
  mpool_destroy(pool);
  
  return 0;
}
