#include "list.h"

static list_t *list_extend(list_t *l) {
  l->next = list_create();
  l->next->head = l->head;
  return l->next;
}

list_t *list_create() {
  list_t *l;
  LIST_MALLOC(l, sizeof(list_t));
  l->head  = l;
  l->next  = NULL;
  l->datum = 0;
  return l;
}

list_t *list_add(list_t *l, list_datum_t d) {
  list_t *ll = l;
  ll = list_extend(l);
  ll->datum = d;
  return ll;
}

list_datum_t list_get(list_t *l, uint idx) {
  list_t *ll = l->head;
  for (int i=0;i<idx;++i) {
    if (ll->next == NULL) break;
    ll = ll->next;
  }
  return ll->datum;
}

void list_destroy(list_t *l) {
  for (list_t *p=l->head;p!=NULL;) {
    list_t *current = p;
    list_t *next    = p->next;
    LIST_FREE(current);
    p = next;    
  }
}

