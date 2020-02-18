#ifndef _INC_ZONE_TREE_H
#define _INC_ZONE_TREE_H

#include "common.h"

struct zone {
    struct zone *left;
    struct zone *right;
    struct zone *parent;
    bsize_t max_block_size;
    bidx_t max_block_idx;
    bidx_t first_block_idx;
    bidx_t first_free_idx;
    bidx_t blocks_end;          // data size in blocks
    uint64_t fill;
    struct block blocks[];
};

struct zone *get_zone(bsize_t blocks);
void free_zone(struct zone *zone);
struct zone *zone_insert(struct zone **root, struct zone *node);
struct zone *zone_search(struct zone *root, size_t key);
struct zone *zone_remove(struct zone **root, struct zone *node);

void print_tree(struct zone *root);

#endif // ZONE_TREE_H
