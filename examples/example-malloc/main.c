#include "./../../src/list.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct { int x, y, z; } SomeThing;
SomeThing * thingCreate(int x, int y, int z) {
  SomeThing *thing = malloc(sizeof(SomeThing));
  thing->x = x, thing->y = y, thing->z = z;
  return thing;
}

List * thingListCreate(int width, int height, int depth) {
  List *list = listCreate();

  SomeThing *thing;
  for(int x = 0; x < width; x++) {
    for(int y = 0; y < height; y++) {
      for(int z = 0; z < depth; z++) {
        thing = thingCreate(x,y,z);
        listAdd(list, thing);
      }
    }
  }

  return list;
}

void thingNoOrigin(List *list) {
  ListEntry *loop = list->start;

  while(loop != NULL) {
    SomeThing *thing = (SomeThing *)loop->data;
    if(thing->x != 0 || thing->y != 0 || thing->z != 0) {
      loop = loop->next;
      continue;
    }
    listRemove(list, loop, true);//True to also free() the SomeThing from memory
    break;
  }
}

int main() {
  List *list = thingListCreate(3, 3, 3);//Create cube

  printf("List is %i in size\n", list->size);//Prints 27
  thingNoOrigin(list);
  printf("List is %i in size\n", list->size);//Prints 26

  listDispose(list, true);//True to also free() the SomeThing's in the list
  return 0;
}