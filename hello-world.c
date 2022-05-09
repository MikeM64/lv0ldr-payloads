/**
 * lv0ldr-spi: Hello-World Test
 *
 * (c) MikeM64 - 2022
 */

/*
 * This will print out "Hello from lv0ldr!" on the SB UART.
 * It will ONLY work on 3.4.0 lv0ldrs (CECH-2500) as the address
 * to printf changes between versions.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <spu_mfcio.h>
#include <spu_intrinsics.h>

void (*sb_printf)(const char *fmt, ...);
void _entry(void) __attribute__((section("_start")));

void
_entry (void)
{
    sb_printf = (void *)0x19bf8;
    sb_printf("Hello from lv0ldr!\n");
    while(1) {}
}

