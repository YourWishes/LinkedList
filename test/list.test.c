#include <unity.h>
#include <string.h>
#include <malloc.h>
#include "./../src/list.h"

void test_listCreate() {
  List *list = listCreate();

  //List should be made
  TEST_ASSERT_NOT_NULL(list);

  //List should start empty
  TEST_ASSERT_NULL(list->start);
  TEST_ASSERT_NULL(list->end);
  TEST_ASSERT_EQUAL(0, list->size);

  listDispose(list, true);
}

void test_listAdd() {
  char *data = "Hello World";
  List *list = listCreate();
  ListEntry *entry = listAdd(list, data);

  //Verify the list item is correct
  TEST_ASSERT_NOT_NULL(entry);
  TEST_ASSERT_EQUAL(data, entry->data);
  TEST_ASSERT_NULL(entry->next);
  TEST_ASSERT_NULL(entry->prev);

  //Check the list is correct
  TEST_ASSERT_EQUAL(1, list->size);
  TEST_ASSERT_EQUAL(entry, list->start);
  TEST_ASSERT_EQUAL(entry, list->end);

  //Try adding something else
  char *data2 = "Hello2";
  ListEntry *entry2 = listAdd(list, data2);
  TEST_ASSERT_NOT_NULL(entry2);
  TEST_ASSERT_EQUAL(data2, entry2->data);
  TEST_ASSERT_EQUAL(entry, entry2->prev);
  TEST_ASSERT_EQUAL(entry2, entry->next);
  TEST_ASSERT_NULL(entry2->next);

  //Check the list
  TEST_ASSERT_EQUAL(2, list->size);
  TEST_ASSERT_EQUAL(entry, list->start);
  TEST_ASSERT_EQUAL(entry2, list->end);

  //Cleanup
  listDispose(list, false);
}

void test_listRemove() {
  List *list = listCreate();

  char *data = "Hello World";
  ListEntry *entry = listAdd(list, data);
  TEST_ASSERT_NOT_NULL(entry);
  TEST_ASSERT_EQUAL(1, list->size);

  //Removing the only entry
  listRemove(list, entry, false);
  TEST_ASSERT_EQUAL(0, list->size);
  TEST_ASSERT_NULL(list->start);
  TEST_ASSERT_NULL(list->end);

  //Removing when there's multiple entries
  char* data1 = "Hello";
  char* data2 = "World";
  char* data3 = "How";
  char* data4 = "You?";
  
  ListEntry *entry1 = listAdd(list, data1);
  ListEntry *entry2 = listAdd(list, data2);
  ListEntry *entry3 = listAdd(list, data3);
  ListEntry *entry4 = listAdd(list, data4);

  TEST_ASSERT_NOT_NULL(entry);
  TEST_ASSERT_EQUAL(4, list->size);
  TEST_ASSERT_EQUAL(entry1, list->start);
  TEST_ASSERT_EQUAL(entry4, list->end);

  //Remove something near the middle
  listRemove(list, entry3, false);
  TEST_ASSERT_EQUAL(3, list->size);
  TEST_ASSERT_EQUAL(entry4, entry2->next);
  TEST_ASSERT_EQUAL(entry2, entry4->prev);
  TEST_ASSERT_EQUAL(entry1, list->start);
  TEST_ASSERT_EQUAL(entry4, list->end);

  //Remove something at the start
  listRemove(list, entry1, false);
  TEST_ASSERT_EQUAL(2, list->size);
  TEST_ASSERT_NULL(entry2->prev);
  TEST_ASSERT_EQUAL(entry2, list->start);
  TEST_ASSERT_EQUAL(entry4, list->end);

  //Remove something at the end
  listRemove(list, entry4, false);
  TEST_ASSERT_EQUAL(1,list->size);
  TEST_ASSERT_NULL(entry2->next);
  TEST_ASSERT_EQUAL(entry2, list->start);
  TEST_ASSERT_EQUAL(entry2, list->end);

  listRemove(list, entry2, false);
  TEST_ASSERT_EQUAL(0, list->size);

  //Cleanup
  listDispose(list, false);
}

void test_listDispose() {
  List *list = listCreate();
  listAdd(list, "Hello");
  listAdd(list, "World");

  TEST_ASSERT_EQUAL(2, list->size);
  listDispose(list, false);

  //Test Malloc
  list = listCreate();
  for(int i = 0; i < 5; i++) {
    int *mi = malloc(sizeof(int));
    *mi = i;
    listAdd(list, mi);
  }

  TEST_ASSERT_EQUAL(0, *((int *)list->start->data));
  TEST_ASSERT_EQUAL(4, *((int *)list->end->data));

  listDispose(list, true);
}

void test_listGetByIndex() {
  List *list = listCreate();
  char* data1 = "Hello";
  char* data2 = "World";
  char* data3 = "How";
  char* data4 = "You?";
  ListEntry *entry1 = listAdd(list, data1);
  ListEntry *entry2 = listAdd(list, data2);
  ListEntry *entry3 = listAdd(list, data3);
  ListEntry *entry4 = listAdd(list, data4);

  //Get by indexes
  TEST_ASSERT_EQUAL(entry1, listGetByIndex(list, 0));
  TEST_ASSERT_EQUAL(entry3, listGetByIndex(list, 2));
  TEST_ASSERT_EQUAL(entry4, listGetByIndex(list, 3));
  TEST_ASSERT_EQUAL(entry2, listGetByIndex(list, 1));

  listDispose(list, false);
}

void test_listGetIndex() {
  List *list = listCreate();
  char* data1 = "Hello";
  char* data2 = "World";
  char* data3 = "How";
  char* data4 = "You?";
  ListEntry *entry1 = listAdd(list, data1);
  ListEntry *entry2 = listAdd(list, data2);
  ListEntry *entry3 = listAdd(list, data3);
  ListEntry *entry4 = listAdd(list, data4);

  //Get by indexes
  TEST_ASSERT_EQUAL(0, listGetIndex(list, entry1));
  TEST_ASSERT_EQUAL(2, listGetIndex(list, entry3));
  TEST_ASSERT_EQUAL(3, listGetIndex(list, entry4));
  TEST_ASSERT_EQUAL(1, listGetIndex(list, entry2));

  listDispose(list, false);
}


//Test Runner
void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int main() {
  UNITY_BEGIN();
  
  RUN_TEST(test_listCreate);
  RUN_TEST(test_listAdd);
  RUN_TEST(test_listRemove);
  RUN_TEST(test_listDispose);
  RUN_TEST(test_listGetByIndex);
  RUN_TEST(test_listGetIndex);

  return UNITY_END();
}