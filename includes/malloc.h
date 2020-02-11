#ifndef _SRC_MALLOC_H_
#define _SRC_MALLOC_H_

#include <stdio.h>

#include <stdint.h>

struct  mem_hdr {
    uint16_t size;
    uint16_t next_offset;
    uint32_t flags;
};

struct block {
    struct block *left;             // 8 8
    struct block *right;            // 8 16
    struct block *parent;           // 8 24
    uint16_t data_size;             // 2 26
    uint16_t max_block;             // 2 28
    uint16_t first_block_offset;    // 2 30
    uint16_t first_free_offset;     // 2 32
    uint8_t data[];
};

struct block *insert(struct block **root, struct block *node);
struct block *search(struct block *root, uint16_t key);
struct block *delete(struct block **root, struct block *node);

void print_tree(struct block *root);

#endif
