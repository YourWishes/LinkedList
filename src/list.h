#pragma once
#include <stdbool.h>

// ListEntry is doubly linked
typedef struct ListEntry {
  void *data;
  struct ListEntry *prev;
  struct ListEntry *next;
} ListEntry;

typedef struct {
  int size;
  ListEntry *start;
  ListEntry *end;
} List;

//Method definitions
List * listCreate();
ListEntry * listAdd(List *list, void *data);
void listAddEntry(List *list,  ListEntry *entry);
void listRemove(List *list, ListEntry *entry, bool freeData);
ListEntry * listGetByIndex(List *list, int index);
int listGetIndex(List *list, ListEntry *entry);
void listDispose(List *list, bool freeData);