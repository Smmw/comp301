/*
 * Start up file for the ARM.
 * At this point we have a stack, but we still need to zero the bss section.
 * After this, we just jump to the kernel.
 *
 * http://www.valvers.com/embedded-linux/raspberry-pi/step02-bare-metal-programming-in-c-pt2
 */

extern int __bss_start__;
extern int __bss_end__;

extern void kernel_main(unsigned int r0, unsigned int r1,
			unsigned int atags);

void _cstartup(unsigned int r0, unsigned int r1, unsigned int r2) {
  int *bss = &__bss_start__;
  int *bss_end = &__bss_end__;

  /* Clear the bss section.
   * Refer to http://en.wikipedia.org/wiki/.bss */
  while (bss < bss_end)
    *bss++ = 0;

  /* Jump to the kernel entry point. In this case, the kernel is the
   * boot program within MINIX that sets up the processor and boots
   * all of the other programs within MINIX. */
  kernel_main(r0, r1, r2);

  /* Kernel should never return, but if it does we can trap here. */
  while (1)
    ;
}
