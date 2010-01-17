

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIST_MALLOC(p, n)              \
  do {                                 \
    if (((p) = malloc(n)) == NULL) {   \
      printf("malloc failed");         \
      exit(-1);                        \
    }                                  \
  } while(false)
#define LIST_FREE(p)                            \
  do {                                          \
    free(p);                                    \
    (p) = NULL;                                 \
  } while(false)

typedef int list_datum_t;
typedef unsigned int uint_t;

typedef struct list_t {
  list_datum_t datum;
  struct list_t *head;
  struct list_t *next;
} list_t;

list_t *list_create();
list_t *list_get(list_t *l, uint_t idx);
list_t *list_add(list_t *l, list_datum_t d);
list_t *list_addfront(list_t *l, list_datum_t d);
list_t *list_join(list_t *l1, list_t *l2);
list_t *list_head(list_t *l);
list_t *list_insert(list_t *l, uint_t idx, list_datum_t d);
list_t *list_remove(list_t *l, uint_t idx);
void list_destroy(list_t *l);

#endif
