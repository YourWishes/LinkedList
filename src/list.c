#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

// Creates a new list, ListEntry->data is typeof void*, cast this to YourType*
List * listCreate() {
  List *list = malloc(sizeof(List));
  list->start = NULL;
  list->end = NULL;
  list->size = 0;
  return list;
}

// Add data to the list, returns a pointer to its entry.
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

// Add an entry to the list and update the entries
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


// Remove an entry from the array. Optionally free the data at that entry.
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

// Get an entry in the list by its position (costly)
ListEntry * listGetByIndex(List *list, int index) {
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

// Get the index of an entry (costly)
int listGetIndex(List *list, ListEntry *entry) {
  int i = 0;
  ListEntry *previous = list->start;

  while(previous != NULL) {
    if(previous == entry) break;
    i++;
    previous = previous->next;
  }
  
  return i;
}


/*
 * Destroys a list, if freeData is provided then the data within the list will
 * also be freed
 */
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