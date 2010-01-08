#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include "../list.h"

#define NUM 10

void test_list_add(void);
void test_list_addfront(void);
void test_list_add_addfront(void);
void test_list_get(void);
void test_list_check_head(void);

void test_list_add(void) {
  list_t *l = list_create();

  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }

  {
    int i = 1;
    for (list_t *p=l->head;p!=NULL;p=p->next,++i) {
      CU_ASSERT(p->datum == i);
    }
  }

  list_destroy(l);
}

void test_list_addfront(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_addfront(l, i+1);
  }
  
  {
    int i = NUM;
    for (list_t *p=l->head;p!=NULL;p=p->next,--i) {
      CU_ASSERT(p->datum == i);
    }
  }
  list_destroy(l);
}

void test_list_add_addfront(void) {
  list_t *l = list_create();
  l = list_add(l, 3);
  l = list_add(l, 4);
  l = list_add(l, 5);
  l = list_add(l, 6);
  l = list_addfront(l, 2);
  l = list_addfront(l, 1);
  l = list_add(l, 7);
  l = list_add(l, 8);
  l = list_add(l, 9);
  l = list_add(l, 10);

  {
    int i = 1;
    for (list_t *p=l->head;p!=NULL;p=p->next,++i) {
      CU_ASSERT(p->datum == i);
    }
  }

  list_destroy(l);
}


void test_list_get(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }
  for (int i=0;i<NUM;++i) {
    CU_ASSERT(list_get(l, i) == i+1);
  }
  list_destroy(l);
}

void test_list_check_head(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }
  list_t *h = l->head;
  for (list_t *p=l->head;p!=NULL;p=p->next) {
    CU_ASSERT(p->head == h);
  }
  list_destroy(l);
}


int main (int argc, char *argv[]) {
  CU_pSuite suite_list;
  CU_initialize_registry();
  suite_list = CU_add_suite("list", NULL, NULL);
  CU_add_test(suite_list, "test_list_add",          test_list_add);
  CU_add_test(suite_list, "test_list_addfront",     test_list_addfront);
  CU_add_test(suite_list, "test_list_add_addfront", test_list_add_addfront);
  CU_add_test(suite_list, "test_list_get",          test_list_get);
  CU_add_test(suite_list, "test_list_check_head",   test_list_check_head);
  CU_console_run_tests();
  CU_cleanup_registry();
  
  return 0;
}


