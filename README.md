# LinkedList
Simple LinkedList in C. Small sweet portable and reusable.
Since this is a doubly linked list it does use significantly more memory than
a regular linked list, but operations should be significantly faster too.


## Usage
Lists consist of a length, start and end positions. List entries consist of
pointers to some data, and their sibling pointers.

*Creating a list*
```c
List * listCreate();
```

*Adding to a list*
```c
ListEntry * listAdd(List *list, void *data);
```

*Removing from a list*
```c
void listRemove(List *list, ListEntry *entry, bool freeData);
```

*Getting entry by index*
```c
ListEntry * listGetByIndex(List *list, int index);
```

*Getting index by entry*
```c
int listGetIndex(List *list, ListEntry *entry);
```

*Disposing a list*
```c
void listDispose(List *list, bool freeData);
```

*Getting a list's size*
```c
List *list = listCreate();
list->size;
```

*Iterating over a list*
```c
List *list = listCreate();
ListEntry *loop = list->start;
while(loop != NULL) {
  //...
  loop = loop->next;
}
```

*Reverse looping*
```c
List *list = listCreate();
ListEntry *loop = list->end;
while(loop != NULL) {
  //...
  loop = loop->prev;
}
```



## Examples
Refer to ./examples/*