#include <stdio.h>

#include "list.h"

#define NUM 10

int main (int argc, char *argv[]) {
  
  list_t *l = list_create();
  
  for (int i=0;i<NUM;++i) {
    l = list_add(l, i+1);
  }

  for (int i=0;i<NUM;++i) {
    list_datum_t d = list_get(l, i);
    printf("%d ", d);
  }
  printf("\n");

  list_destroy(l);
  return 0;
}


