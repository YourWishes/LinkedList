#pragma once
#include <stdbool.h>

/**
 * Entry within a given linked list.
 * @param data* The pointer to the data that is within the entry.
 * @param prev* Pointer to the previous entry in the list.
 * @param next* Pointer to the next entry in the list.
 */
typedef struct ListEntry {
  void *data;
  struct ListEntry *prev;
  struct ListEntry *next;
} ListEntry;

/**
 * Linked List of elements, Doubly Linked.
 * @param size The count of elements currently within the list
 * @param start* First element within the list.
 * @param end* Last element within the list.
 */
typedef struct {
  int size;
  ListEntry *start;
  ListEntry *end;
} List;

//Method definitions

/**
 * Creates a new linked list
 * @return Pointer to a new linked list.
 */
List * listCreate();

/**
 * Adds data to a linked list
 * 
 * @param list* Pointer to a previously created linked list
 * @param data* Pointer to your data
 * @return A pointer to the new entry in the linked list that was created
 */
ListEntry * listAdd(List *list, void *data);

/**
 * Internal function
 */
void listAddEntry(List *list,  ListEntry *entry);

/**
 * Remove a list entry from the linked list
 * @param list* Pointer to a previously created linked list
 * @param entry* Pointer to the entry within the linked list.
 * @param freeData If true the data of the ListEntry will be free()'d
 */
void listRemove(List *list, ListEntry *entry, bool freeData);

/**
 * Returns the entry at a given index. This method is costly.
 * @param list* Pointer to a previously created linked list
 * @param index Index of element within the linked list to remove
 * @return The entry at the index or NULL if outside the bounds.
 */
ListEntry * listGetByIndex(List *list, int index);

/**
 * Returns the index of an entry within the linked list. This method is costly.
 * @param list* Pointer to a previously created linked list
 * @param entry* Pointer to the entry within the linked list.
 * @return The index within the list the entry is in, or -1 if not found.
 */ 
int listGetIndex(List *list, ListEntry *entry);

/**
 * Dispose a previously created link list.
 * @param list* Pointer to a previously created linked list
 * @param freeData If true the data within each ListEntry will be free()'d
 */
void listDispose(List *list, bool freeData);