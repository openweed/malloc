#ifndef _SRC_MALLOC_H_
#define _SRC_MALLOC_H_

#include <stdint.h>

struct  mem_hdr {
    uint16_t size;
    uint16_t next_offset;
    uint32_t flags;
};

struct block {
    struct block *left;             // 8 8
    struct block *right;            // 8 16
    struct block *parent;            // 8 16
    uint16_t data_size;             // 2 18
    uint16_t max_block;             // 2 20
    uint16_t first_block_offset;    // 2 22
    uint16_t first_free_offset;     // 2 24
    uint8_t data[];
};

#endif
