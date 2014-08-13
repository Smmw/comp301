/*
 * Doubly Linked List
 *
 * Dan Collins 2014
 * 1183446
 *
 * COMP301 - 14B
 */
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

list_t * list_init(void) {
  list_t *list;

  /* Allocate memory for the list */
  list = malloc(sizeof(list_t));
  if (list == NULL) {
    fprintf(stderr, "Error allocating memory for the list.\n");
    return NULL;
  }

  /* Prepare list */
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;

  return list;
}

void list_add(list_t *list, void *data) {
  list_el_t *tmp, *item;

  /* Create an item to insert into the list */
  item = malloc(sizeof(list_el_t));
  if (item == NULL) {
    fprintf(stderr, "Failed to allocate memory for list item.\n");
    return;
  }
  item->next = NULL;
  item->prev = NULL;
  item->data = data;

  /* If the list is empty, new item becomes the head and tail of
   * the list. */
  if (list->head == NULL) {
    list->head = item;
    list->tail = item;
    list->length++;

    return;
  }

  /* Insert the item as the head of the list */
  tmp = list->head;
  list->head = item;
  item->next = tmp;
  tmp->prev = item;
  list->length++;
}

void list_insert(list_t *list, void *data, compare_t compare) {
  list_el_t *tmp, *item;

  /* Create an item to insert into the list */
  item = malloc(sizeof(list_el_t));
  if (item == NULL) {
    fprintf(stderr, "Failed to allocate memory for list item.\n");
    return;
  }
  item->next = NULL;
  item->prev = NULL;
  item->data = data;

  /* If the list is empty, new item becomes the head and tail of the
   * list. */
  if (list->head == NULL) {
    list->head = item;
    list->tail = item;
    list->length++;

    return;
  }

  /* Starting at the bottom of the list, scan backwards until the
   * new item is larger than the item scanned. */
  tmp = list->tail;
  while (tmp != NULL) {
    if (compare(item->data, tmp->data) > 0) {
      /* New item gets inserted after tmp. If we are inserting at the
       * tail, then there's one less link to manage. */
      if (tmp->next == NULL) {
	list->tail = item;
	item->prev = tmp;
	tmp->next = item;
      } else {
	item->next = tmp->next;
	item->prev = tmp;
	tmp->next->prev = item;
	tmp->next = item;
      }

      list->length++;

      return;
    }

    tmp = tmp->prev;
  }

  /* Item is smaller than the list head, so insert at the head. */
  tmp = list->head;
  list->head = item;
  item->next = tmp;
  tmp->prev = item;
  list->length++;
}

void list_remove(list_t *list, void *data, compare_t compare) {
  list_el_t *tmp;

  /* If the list is empty, then there is nothing to do */
  if (list->head == NULL)
    return;

  /* Starting at the top of the list, remove all instances of the
   * data from the list */
  tmp = list->head;
  while(tmp != NULL) {
    if (compare(data, tmp->data) == 0) {
      if (tmp == list->head) {
	list->head = tmp->next;
	tmp->next->prev = NULL;
      } else if (tmp == list->tail) {
	list->tail = tmp->prev;
	tmp->prev->next = NULL;
      } else {
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
      }

      list->length--;

      free(tmp);
    }

    tmp = tmp->next;
  }
}

void list_clear(list_t *list) {
  list_el_t *tmp, *tmp2;

  /* Starting at the top of the list, remove all elements in the
   * list */
  tmp = list->head;
  while(tmp != NULL) {
    tmp2 = tmp->next;
    free(tmp);
    tmp = tmp2;
  }

  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
}
