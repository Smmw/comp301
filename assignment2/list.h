/*
 * Doubly Linked List
 *
 * Dan Collins 2014
 * 1183446
 *
 * COMP301 - 14B
 */

/**
 * An item within the list.
 * TODO: Add a to_string function?
 * TODO: Add a free function?
 */
typedef struct list_el_s {
  void *data;
  struct list_el_s *next, *prev;
} list_el_t;

/**
 * A doubly linked list structure.
 */
typedef struct list_s {
  list_el_t *head;
  list_el_t *tail;
  unsigned int length;
} list_t;

/**
 * Compare function used to compare items in the list.
 * @param d1 The first item's data
 * @param d2 The second item's data
 * @returns -1 if the d1 is smaller, 0 if the d1 is the same
 *          and 1 if the d1 is larger than d2
 */ 
typedef int (*compare_t)(void *d1, void *d2);

/**
 * Create a new list structure.
 * @returns A new list object on success and NULL on failure.
 */
list_t * list_init(void);

/**
 * Add an item to the head of the list
 * @param list A pointer to the list structure
 * @param data A pointer to the data to add
 */
void list_add(list_t *list, void *data);

/**
 * Insert an item into the list
 * @param list A pointer to the list structure
 * @param data A pointer to the data to insert
 * @param compare The compare function to use
 */
void list_insert(list_t *list, void *data, compare_t compare);

/**
 * Remove all occurances of a given item from the list
 * @param list A pointer to the list structure
 * @param data A pointer to the data to insert
 * @param compare The compare function to use
 */
void list_remove(list_t *list, void *data, compare_t compare);

/**
 * Remove all items from the list
 * @param list A pointer to the list structure
 */
void list_clear(list_t *list);

/**
 * Search for the first instance of the given item within the list
 * @param list A pointer to the list structure
 * @param data A pointer to the data to search for
 * @param compare The compare function to use
 * @returns The first instance of the object if found, otherwise NULL
 */
void * list_find_first(list_t *list, void *data, compare_t compare);

/**
 * Search for the next occurance of the given item within the list
 * @param list A pointer to the list structure
 * @param data A pointer to the data to search for
 * @param reference This pointer will keep track of the position in
 *                  the list. It is important to pass this pointer
 *                  at each call to list_find_next. Initialise to NULL
 *                  for the first call.
 * @param compare The compare function to use
 * @returns The next instance of the object if found, otherwise NULL
 */
void * list_find_next(list_t *list, void *data, list_el_t **reference,
		      compare_t compare);
