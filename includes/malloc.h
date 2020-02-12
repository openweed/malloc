#ifndef _SRC_MALLOC_H_
#define _SRC_MALLOC_H_

#include <stdio.h>

#include <stdint.h>

#define ZONE_PAGES 8
#define BLOCK_SIZE 8
#define NULL_OFFSET ((uint16_t)-1)

// Offset
typedef uint16_t offset_t;
// Size in blocks (1 block = 8 byte)
typedef size_t bsize_t;

struct block {
    offset_t size;
    offset_t offset;
    offset_t next_blk;
    offset_t flags;
    uint64_t data[];
};

struct zone {
    struct zone *left;
    struct zone *right;
    struct zone *parent;
    bsize_t max_block_size;
    offset_t first_block_offset;
    offset_t first_free_offset;
    offset_t blocks_count;          // data size in blocks
    uint64_t fill;
    struct block blocks[];
};

struct zone *insert(struct zone **root, struct zone *node);
struct zone *search(struct zone *root, size_t key);
struct zone *delete(struct zone **root, struct zone *node);

void print_tree(struct zone *root);

#endif
