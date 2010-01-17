#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../list.h"

#define NUM 10

static void test_list_add(void);
static void test_list_addfront(void);
static void test_list_add_addfront(void);
static void test_list_get(void);
static void test_list_get_negative_idx(void);
static void test_list_check_head(void);
static void test_list_join(void);
static void test_list_insert(void);
static void test_list_remove(void);

static void test_list_add(void) {
  list_t *l = list_create();

  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }

  {
    int i = 1;
    for (list_t *p=list_head(l);p!=NULL;p=p->next,++i) {
      CU_ASSERT(p->datum == i);
    }
  }

  list_destroy(l);
}

static void test_list_addfront(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_addfront(l, i+1);
  }
  
  {
    int i = NUM;
    for (list_t *p=list_head(l);p!=NULL;p=p->next,--i) {
      CU_ASSERT(p->datum == i);
    }
  }
  list_destroy(l);
}

static void test_list_add_addfront(void) {
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
    for (list_t *p=list_head(l);p!=NULL;p=p->next,++i) {
      CU_ASSERT(p->datum == i);
    }
  }
  list_destroy(l);
}


static void test_list_get(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }
  for (int i=0;i<NUM;++i) {
    list_t *p = list_get(l, i);
    CU_ASSERT(p->datum == i+1);
  }
  list_destroy(l);
}

static void test_list_get_negative_idx(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }
  list_t *p = list_get(l, -1);
  CU_ASSERT(p == NULL);
  list_destroy(l);
}

static void test_list_check_head(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }
  list_t *h = list_head(l);
  for (list_t *p=list_head(l);p!=NULL;p=p->next) {
    CU_ASSERT(p->head == h);
  }
  list_destroy(l);
}

static void test_list_join(void) {
  list_t *l1 = list_create();
  l1 = list_add(l1, 2);
  l1 = list_add(l1, 3);
  l1 = list_addfront(l1, 1);
  list_t *l2 = list_create();
  l2 = list_add(l2, 4);
  l2 = list_add(l2, 5);
  l2 = list_add(l2, 6);
  list_t *l3 = list_join(l1, l2);
  {
    int i = 1;
    for (list_t *p=list_head(l3);p!=NULL;p=p->next,++i) {
      CU_ASSERT(p->datum == i);
    }
  }
  list_destroy(l3);
}

static void test_list_insert(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }
  l = list_insert(l, 0,  11);
  l = list_insert(l, 5,  99);
  l = list_insert(l, 12, 100);
  {
    int i = 1;
    for (list_t *p=list_head(l);p!=NULL;p=p->next,++i) {
      printf("%d ", p->datum);
    }
    printf("\n");
  }
  list_t *p = list_head(l);
  CU_ASSERT(p->datum == 11);
  p = p->next;
  CU_ASSERT(p->datum == 1);
  p = p->next;
  CU_ASSERT(p->datum == 2);
  p = p->next;
  CU_ASSERT(p->datum == 3);
  p = p->next;
  CU_ASSERT(p->datum == 4);
  p = p->next;
  CU_ASSERT(p->datum == 99);
  p = p->next;
  CU_ASSERT(p->datum == 5);
  p = p->next;
  CU_ASSERT(p->datum == 6);
  p = p->next;
  CU_ASSERT(p->datum == 7);
  p = p->next;
  CU_ASSERT(p->datum == 8);
  p = p->next;
  CU_ASSERT(p->datum == 9);
  p = p->next;
  CU_ASSERT(p->datum == 10);
  p = p->next;
  CU_ASSERT(p->datum == 100);
  list_destroy(l);
}

static void test_list_remove(void) {
  list_t *l = list_create();
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }
  l = list_remove(l, 0);
  l = list_remove(l, 3);
  l = list_remove(l, 7);
  list_t *p = list_head(l);
  CU_ASSERT(p->datum == 2);
  p = p->next;
  CU_ASSERT(p->datum == 3);
  p = p->next;
  CU_ASSERT(p->datum == 4);
  p = p->next;
  CU_ASSERT(p->datum == 6);
  p = p->next;
  CU_ASSERT(p->datum == 7);
  p = p->next;
  CU_ASSERT(p->datum == 8);
  p = p->next;
  CU_ASSERT(p->datum == 9);
  list_destroy(l);
}

int main (int argc, char *argv[]) {
  CU_pSuite suite_list;
  CU_initialize_registry();
  suite_list = CU_add_suite("list", NULL, NULL);
  CU_add_test(suite_list, "test_list_add",              test_list_add);
  CU_add_test(suite_list, "test_list_addfront",         test_list_addfront);
  CU_add_test(suite_list, "test_list_add_addfront",     test_list_add_addfront);
  CU_add_test(suite_list, "test_list_get",              test_list_get);
  CU_add_test(suite_list, "test_list_get_negative_idx", test_list_get_negative_idx);
  CU_add_test(suite_list, "test_list_check_head",       test_list_check_head);
  CU_add_test(suite_list, "test_list_join",             test_list_join);
  CU_add_test(suite_list, "test_list_insert",           test_list_insert);
  CU_add_test(suite_list, "test_list_remove",           test_list_remove);
  CU_basic_run_tests();
  CU_cleanup_registry();
  
  return 0;
}


