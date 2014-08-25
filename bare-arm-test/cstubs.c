/*
 * Stubs for C standard library.
 */
#include <sys/stat.h>

extern caddr_t _get_stack_pointer(void);

/* Increase program data space. malloc and related functions rely on
 * this. */
caddr_t _sbrk(int incr) {
  extern char _end; /* Defined by GCC */
  static char *heap_end;
  char *prev_heap_end;

  if (*heap_end == 0)
    heap_end = &_end;

  prev_heap_end = heap_end;

  /* If the heap and the stack collide, loop forever. Should probably
   * fix this! */
  if ((heap_end + incr) > _get_stack_pointer()) {
    while(1)
      ;
  }

  heap_end += incr;
  return (caddr_t)prev_heap_end;
}
