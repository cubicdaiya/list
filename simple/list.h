

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
typedef unsigned int uint;

typedef struct list_t {
  list_datum_t datum;
  struct list_t *head;
  struct list_t *next;
} list_t;

list_t *list_create();
list_datum_t list_get(list_t *l, uint idx);
list_t *list_add(list_t *l, list_datum_t d);
list_t *list_addfront(list_t *l, list_datum_t d);
void list_destroy(list_t *l);

#endif
