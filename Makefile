#
# Makefile for lv0ldr payloads
# (c) 2022 - MikeM64
#
#

#
# Useful commands:
# - spu-objdump -b binary -D -m spu <payload>.bin

.PHONY: clean, all

.SECONDARY:

all: stage2.h hello-world.h

%.bin: %.c
	spu-gcc -ffreestanding -fno-builtin -nostdlib -fpic $< -Os -e _entry -o $@ -T payload.ld

%.h: %.bin
	xxd -i $< > $@

clean:
	rm *.bin *.o *.h || true
