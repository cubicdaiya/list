#include "list.h"

/**
 * private function
 */
static list_t *list_extend(list_t *l);

/**
 * initialize list
 */
list_t *list_create() {
  list_t *l;
  LIST_MALLOC(l, sizeof(list_t));
  l->head  = NULL;
  l->next  = NULL;
  return l;
}

/**
 * add an element to the tail of list
 */
list_t *list_add(list_t *l, list_datum_t d) {
  list_t *ll = l;
  if (ll->head == NULL) {
    ll->datum = d;
    ll->head  = ll;
    return ll;
  }
  ll = list_extend(l);
  ll->datum = d;
  return ll;
}

/**
 * add an element to the head of list
 */
list_t *list_addfront(list_t *l, list_datum_t d) {
  if (l->head == NULL) {
    l->datum = d;
    l->head  = l;
    return l;
  }
  list_t *ln  = list_create();
  ln->datum   = d;
  ln->head    = ln;
  ln->next    = l->head->head;
  l->head->head = ln;
  return l;
}

/**
 * get the idxth element of list 
 */
list_datum_t list_get(list_t *l, uint idx) {
  list_t *ll = l->head;
  for (int i=0;i<idx;++i) {
    if (ll->next == NULL) break;
    ll = ll->next;
  }
  return ll->datum;
}

/**
 * release all elements of list
 */
void list_destroy(list_t *l) {
  for (list_t *p=l->head;p!=NULL;) {
    list_t *current = p;
    list_t *next    = p->next;
    LIST_FREE(current);
    p = next;    
  }
}

list_t *list_head(list_t *l) {
  return l->head->head;
}

list_t *list_join(list_t *l1, list_t *l2) {
  l1->next = list_head(l2);
  l2->head = list_head(l1);
  return l2;
}

/* following is private function */ 

/**
 * extend list
 */
static list_t *list_extend(list_t *l) {
  l->next = list_create();
  l->next->head = l->head->head;
  return l->next;
}
