#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

List * listCreate() {
  List *list = malloc(sizeof(List));
  list->start = NULL;
  list->end = NULL;
  list->size = 0;
  return list;
}

ListEntry * listAdd(List *list, void *data) {
  //Create the list entry
  ListEntry *entry = malloc(sizeof(ListEntry));
  entry->data = data;
  entry->next = NULL;
  entry->prev = NULL;

  //Add it to the list
  listAddEntry(list, entry);

  //Return the entry
  return entry;
}

void listAddEntry(List *list, ListEntry *entry) {
  //Is this the first / only thing in the list?
  if(list->start == NULL) {
    list->start = entry;
    list->end = entry;
  } else {
    //Make the end's next be this entry, and this entry's prev the end, then 
    //make this the new end
    entry->prev = list->end;
    list->end->next = entry;
    list->end = entry;
  }
  list->size++;
}


void listRemove(List *list, ListEntry *entry, bool freeData) {
  //Update next and prev
  if(entry->prev != NULL) entry->prev->next = entry->next;
  if(entry->next != NULL) entry->next->prev = entry->prev;

  //Was this at the end?
  if(list->start == entry) list->start = entry->next;
  if(list->end == entry) list->end = entry->prev;

  if(freeData) free(entry->data);
  free(entry);

  list->size--;
}

ListEntry * listGetByIndex(List *list, int index) {
  if(index >= list->size) return NULL;

  //TODO: We can probably make this more efficient by deciding which way we 
  //should loop from based on the list size.

  int i = 0;
  ListEntry *previous = list->start;

  while(previous != NULL) {
    if(i == index) return previous;
    i++;
    previous = previous->next;
  }

  return NULL;
}

int listGetIndex(List *list, ListEntry *entry) {
  int i = 0;
  ListEntry *previous = list->start;

  while(previous != NULL) {
    if(previous == entry) return i;
    i++;
    previous = previous->next;
  }
  
  return -1;
}

void listDispose(List *list, bool freeData) {
  //Free all of the entries
  ListEntry *next = list->start;
  ListEntry *current;
  
  while(next != NULL) {
    current = next;
    next = current->next;
    if(freeData) free(current->data);
    free(current);
  }

  free(list);
}