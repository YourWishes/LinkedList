#include "./../../src/list.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
  //Create a list
  List *list = listCreate();

  //Add a few strings
  char *data1 = "Hello";
  ListEntry *entry1 = listAdd(list, data1);

  char *data2 = "World";
  ListEntry *entry2 = listAdd(list, data2);

  char *data3 = "How";
  ListEntry *entry3 = listAdd(list, data3);

  char *data4 = "Are";
  ListEntry *entry4 = listAdd(list, data4);

  char *data5 = "You?";
  ListEntry *entry5 = listAdd(list, data5);
  
  //Iterate over the list
  ListEntry *loop = list->start;//Start at the beginning
  while(loop != NULL) {
    printf(loop->data);//Print the data
    loop = loop->next;//Setup for next loop

    if(loop != NULL) printf(" ");//If there's about to be another loop, space
  }
  printf("\n");

  //Cleanup
  listDispose(list, false);//Pass false to prevent the char *'s being freed
  return 0;
}