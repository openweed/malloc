
#include "common.h"
#include "zone.h"

struct block *get_free_block(struct zone *zone, bsize_t bsize, bidx_t **prev)
{
    bidx_t i;
    struct block *blocks;

    i = zone->first_free_idx;
    *prev = &zone->first_free_idx;
    blocks = zone->blocks;
    while (blocks[i].size < bsize && blocks[i].next_free < zone->blocks_end) // XXX Delete next_free check
    {
        *prev = &blocks[i].next_free;
        i = blocks[i].next_free;
    }
    return &blocks[i];
}

struct block *reserve_block(struct zone *zone, bsize_t bsize)
{
    bidx_t *prev_free;
    struct block *block;
    struct block *free_part;

    block = get_free_block(zone, bsize, &prev_free);
    if (block->size == bsize)
    {
        *prev_free = block->next_free;
    }
    else
    {
        free_part = &block[bsize];
        free_part->size = block->size - bsize;
        free_part->prev = block->idx;
        free_part->idx = block->idx + bsize;
        free_part->next_free = block->next_free;
        *prev_free = free_part->idx;
        block->size = bsize;
    }
    block->next_free = 0;
    if (block->idx == zone->max_block_idx)
        set_max_block(zone);
    return block;
}

void *ft_malloc(size_t size)
{
    bsize_t bsize;
    struct zone *zone;
    struct block *block;

    bsize = size / BLOCK_BYTES + ((size % BLOCK_BYTES) ? 1 : 0) + HEADER_BLOCKS;
    zone = get_zone(bsize);
    if (!zone)
        return NULL;
    block = reserve_block(zone, bsize);
    return (void *)block->data;
}
