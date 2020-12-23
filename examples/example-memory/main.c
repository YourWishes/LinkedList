#include "./../../src/list.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

int main() {
  //Idea of this test is to forever create lists and dispose them to show no
  //memory leaks are present.

  while(true) {
    List *list = listCreate();

    ListEntry *entry;
    listAddEntry(list, entry);

    for(int j = 0; j < 99999; j++) {
      int* integerArray = malloc(sizeof(int));
      *integerArray = j;
      listAdd(list, integerArray);
    }
    
    listDispose(list, true);//true to cleanup the integers
  }

  return 0;
}