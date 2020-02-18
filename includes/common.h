#ifndef COMMON_H
#define COMMON_H

// XXX debug
#include <stdio.h>

#include <stddef.h>
#include <stdint.h>

#define ZONE_PAGES 8
#define BLOCK_BYTES 8
#define NULL_BIDX ((uint16_t)-1)
#define HEADER_BLOCKS 1

#define FLAG_ALLOC 1

extern struct zone *zone_root;

// Offset
typedef uint16_t bidx_t;
// Size in blocks (1 block = 8 byte)
typedef size_t bsize_t;

struct block {
    bidx_t next_free;// if 0 block not free
    bidx_t size;     // total blocks in block
    bidx_t prev;     // prev block offset
    bidx_t idx;      // block index, block[-idx] == zone->blocks[0]
    uint64_t data[];
};

void set_max_block(struct zone *zone);
struct block *get_prev_free(struct zone *zone, bidx_t bidx);
struct block *ptr2block(void *p);
struct zone *block2zone(struct block *block);

#endif // COMMON_H
