
#include "common.h"
#include "zone.h"

void set_max_block(struct zone *zone)
{
    struct block *blocks;
    bidx_t i;
    bidx_t max;

    blocks = zone->blocks;
    i = zone->first_free_idx;
    max = i;
    while (i != NULL_BIDX)
    {
        if (blocks[i].size > blocks[max].size)
            max = i;
        i = blocks[i].next_free;
    }
    zone->max_block_idx = max;
    zone->max_block_size = blocks[max].size;
    zone_remove(&zone_root, zone);
    zone_insert(&zone_root, zone);
    return;
}

struct block *get_prev_free(struct zone *zone, bidx_t bidx)
{
    bidx_t prev;
    struct block *blocks;

    if ((prev = zone->first_free_idx) == NULL_BIDX)
        return NULL;
    if (prev > bidx)
        return NULL;

    blocks = zone->blocks;
    while (blocks[prev].next_free < bidx)
        prev = blocks[prev].next_free;

    return &blocks[prev];
}

struct block *ptr2block(void *p)
{
    return (struct block *)((uint8_t *)p - sizeof(struct block));
}

struct zone *block2zone(struct block *block)
{
    return (struct zone *)((uint8_t *)(&block[-block->idx]) - sizeof(struct zone));
}
