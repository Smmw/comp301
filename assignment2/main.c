/*
 * Simple Scheduler
 *
 * Dan Collins 2014
 * 1183446
 *
 * COMP301 - 14B
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "list.h"

#define MAX_LINE 1024


void usage(void) {
  printf("usage: scheduler input_file\n");
}

int string_compare(void *d1, void *d2) {
  return strcmp((char *)d1, (char *)d2);
}

void print_list(list_t *list) {
  list_el_t *tmp = list->head;

  printf("Printing list of length %d\n", list->length);

  while (tmp != NULL) {
    printf("%s\n", (char *)tmp->data);
    tmp = tmp->next;
  }
}

int main(int argc, char **argv) {
  FILE *infile = NULL;
  char line[MAX_LINE];
  unsigned int time = 0;
  list_t *list;

  /* Check input arguments */
  if (argc != 2) {
    fprintf(stderr, "Invalid input arguments.\n");
    usage();
    return -1;
  }

  /* Test list */
  list = list_init();
  list_insert(list, (void *)"Pear", &string_compare);
  list_insert(list, (void *)"Apple", &string_compare);
  list_insert(list, (void *)"Banana", &string_compare);
  list_insert(list, (void *)"Pineapple", &string_compare);
  list_insert(list, (void *)"Pineapple", &string_compare);
  list_insert(list, (void *)"Anchovy", &string_compare);

  print_list(list);

  list_remove(list, (void *)"Pineapple", &string_compare);

  print_list(list);

#if 0
  /* Open the input file */
  infile = fopen(argv[1], "r");
  if (infile == NULL) {
    fprintf(stderr, "Error (%d) opening the specified input file.\n",
	    errno);
    return -1;
  }

  /* Read the input file */
  while(fgets(line, MAX_LINE, infile) != NULL) {
    
  }

  /* Close the input file */
  fclose(infile);
#endif

  return 0;
}
