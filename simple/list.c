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
  list_t *ln    = list_create();
  ln->datum     = d;
  ln->head      = ln;
  ln->next      = l->head->head;
  l->head->head = ln;
  return l;
}

/**
 * get the idxth element of list 
 */
list_t *list_get(list_t *l, uint_t idx) {
  if (idx < 0) {
    return NULL;
  }
  list_t *ll = list_head(l);
  for (int i=0;i<idx;++i) {
    if (ll->next == NULL) {
      return NULL;
    }
    ll = ll->next;
  }
  return ll;
}

/**
 * release all elements of list
 */
void list_destroy(list_t *l) {
  for (list_t *p=list_head(l);p!=NULL;) {
    list_t *current = p;
    list_t *next    = p->next;
    LIST_FREE(current);
    p = next;    
  }
}

list_t *list_join(list_t *l1, list_t *l2) {
  l1->next = list_head(l2);
  l2->head = list_head(l1);
  return l2;
}

list_t *list_head(list_t *l) {
  return l->head->head;
}

list_t *list_insert(list_t *l, uint_t idx, list_datum_t d) {
  if (idx == 0) {
    return list_addfront(l, d);
  }
  list_t *insert_prev  = list_get(l, idx - 1);
  if (insert_prev == NULL) {
    return l;
  }
  list_t *insert_after = insert_prev->next;
  if (insert_after == NULL) {
    return list_add(l, d);
  }
  list_t *insert    = list_create();
  insert->datum     = d;
  insert->next      = insert_after;
  insert_prev->next = insert;
  return l;
}

list_t *list_remove(list_t *l, uint_t idx) {
  uint_t idx_prev = idx - 1;
  list_t *head = list_head(l);
  if (idx == 0) {
    if (head == NULL) {
      return NULL;
    }
    list_t *new_head = head->next;
    new_head->head = new_head;
    l->head = new_head;
    LIST_FREE(head);
    return l;
  }
  list_t *remove_prev = list_get(l, idx_prev);
  list_t *remove;
  list_t *remove_after;
  if (remove_prev == NULL) {
    return l;
  }
  remove = remove_prev->next;
  if (remove) {
    remove_after = remove->next;
    LIST_FREE(remove);
    if (remove_after) {
      remove_prev->next  = remove_after;
      remove_after->head = head;
      return remove_after;
    } else {
      remove_prev->next = NULL;
      remove_prev->head = head;
      return remove_prev;
    }
  }
  return l;
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
