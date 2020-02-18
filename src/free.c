#include "zone.h"
#include "common.h"

void free_block(struct zone *zone, struct block *block)
{
    struct block *blocks;
    struct block *prev;
    struct block *next;

    blocks = zone->blocks;
    prev = get_prev_free(zone, block->idx);
    if (prev && prev->next_free != NULL_BIDX)
        next = &blocks[prev->next_free];
    else if (zone->first_free_idx != NULL_BIDX)
        next = &blocks[zone->first_free_idx];
    else
        next = NULL;

    if (!prev)
    {
        zone->first_free_idx = block->idx;
    }
    else if (prev->idx + prev->size == block->idx)
    {
        prev->size += block->size;
        block = prev;
    }
    else
    {
        prev->next_free = block->idx;
    }

    if (!next)
    {
        block->next_free = NULL_BIDX;
    }
    else if (block->idx + block->size == next->idx)
    {
        block->next_free = next->next_free;
        block->size += next->size;
    }
    else
    {
        block->next_free = next->idx;
    }
    set_max_block(zone);
}

void ft_free(void *p)
{
    struct block *block;
    struct zone *zone;

    block = ptr2block(p);
    zone = block2zone(block);
    free_block(zone, block);
    if (zone->max_block_size == zone->blocks_end)
        free_zone(zone);
}
