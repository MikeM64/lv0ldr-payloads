# lv0ldr-payloads
(c) 2022 - MikeM64

This is a collection of payloads to run with your lv0ldr hardware exploit.

# Requirements
- SPU GCC Toolchain

# Writing a new payload
1) Use the following template for the .c file:

```c
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <spu_mfcio.h>
#include <spu_intrinsics.h>

/* Forward declarations */
void _entry(void) __attribute__((section("_start")));

void
_entry (void)
{
    /* Your code goes here */
    while (1) {}
}

```

2) Edit the makefile to add <your file>.h as a target
3) `make`

# Limitations
- Payloads start execution from 0x3e120
- The maximum payload size at the moment is 0xEE0 in order to not clobber syscon message counters.

# Payloads
## hello-world
This prints a message to the SB UART port. It only works on 3.4.0 lv0ldrs due to the fixed offset of the printf function.

## stage2
This dumps the entire contents of the isolated LS over SB UART. This should work on any lv0ldr as it does not rely on any pre-existing code.

