/**
 * lv0ldr-spi: Stage 2 - Dumper Code
 *
 * (c) MikeM64 - 2022
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <spu_mfcio.h>
#include <spu_intrinsics.h>

#define SPU_DMA_TAG 0
#define SPU_DMA_TAG_MASK    (1 << SPU_DMA_TAG)

/* Forward declarations */
void _entry(void) __attribute__((section("_start")));

/*
 * SPU DMA transfers must share the same low 4-bits on both
 * source and destination addresses otherwise an alignment
 * error will be raised.
 *
 * Safe addresses available are 0x3e000 to 0x3e120 before
 * overwriting the payload.
 */
static uint8_t *s_dma_buf;

static inline void
dma_transfer (volatile void *lsa,
              unsigned int   eah,
              unsigned int   eal,
              unsigned int   size,
              unsigned int   tag_id,
              unsigned int   dma_cmd)
{
    spu_mfcdma64(lsa, eah, eal, size, tag_id, dma_cmd);
}

/* TX space is available when this bit is set */
#define SB_STAT_FFF308_CAN_PUTC 0x100

void
sb_putc (char c)
{
    uint32_t *dma_resp = (uint32_t *)&s_dma_buf[8];

    /* Wait for space to put the character */
    do {
        dma_transfer(dma_resp,
                     0x240,
                     0xfff308,
                     sizeof(*dma_resp),
                     SPU_DMA_TAG,
                     MFC_GET_CMD);
        do {
            mfc_write_tag_mask(SPU_DMA_TAG_MASK);
        } while(mfc_read_tag_status_immediate() == 0);
    } while (!((*dma_resp) & SB_STAT_FFF308_CAN_PUTC));

    dma_resp = (uint32_t *)&s_dma_buf[0xc];
    *dma_resp = c;

    dma_transfer(dma_resp,
                 0x240,
                 0xfff31c,
                 sizeof(*dma_resp),
                 SPU_DMA_TAG,
                 MFC_PUT_CMD);
    do {
        mfc_write_tag_mask(SPU_DMA_TAG_MASK);
    } while(mfc_read_tag_status_immediate() == 0);
}

void
sb_printstr (const char *str)
{
    while (*str) {
        sb_putc(*str);
        *str++;
    }
}

void
_entry (void)
{
    uint8_t *ls_addr = 0;
    s_dma_buf = (uint8_t *)0x3e000;

    sb_printstr("Starting dump:\n");

    for (ls_addr = 0; ls_addr < (uint8_t *)0x40000; ls_addr++) {
        sb_putc(*ls_addr);
    }

    sb_printstr("\nComplete!\n");

    while(1) {}
}

