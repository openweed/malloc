#include "zone.h"

struct block *reallocate_block(struct zone *zone, struct block *block)
{
    struct block *next;

    next = &block[block->size];
    return block;
}

void *ft_realloc(void *p, size_t size)
{
    struct block *block;
    struct zone *zone;

    block = ptr2block(p);
    zone = block2zone(block);
    block = reallocate_block(zone, block);
    if (!block)
        return NULL;
    return (void *)block->data;
}
