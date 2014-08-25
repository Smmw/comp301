// This was copied from:
// http://www.valvers.com/embedded-linux/raspberry-pi/step02-bare-metal-programming-in-c-pt2

.section ".text.startup"

.global _start
.global _get_stack_pointer

_start:
	// Set stack pointer to the bottom of RAM
	// The amount of RAM differs depending on config.txt
	ldr sp, =(128 * (1024 * 1024))
	//ldr sp, =(256 * (1024 * 1024))

	// RAM starts at 0, so subtract 4 bytes
	sub sp, sp, #0x4

	// The rest of the start up code is in C!
	b _cstartup

_get_stack_pointer:
	// Returns the stack pointer address
	str sp, [sp]
	ldr r0, [sp]
	// Return from this function
	mov pc, lr
