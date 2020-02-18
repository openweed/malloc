#include <unistd.h>
#include <sys/mman.h>

#include "zone.h"

struct zone *zone_root = NULL;

static struct zone *_new_zone();

struct zone *get_zone(bsize_t blocks)
{
    struct zone *zone;

    zone = zone_root ? zone_search(zone_root, blocks) : NULL;
    if (!zone)
    {
        zone = _new_zone();
        if (!zone)
            return NULL;
        zone_insert(&zone_root, zone);
    }
    return zone;
}

void free_zone(struct zone *zone)
{
    // XXX
    printf("free_zone called\n");
    zone_remove(&zone_root, zone);
}

static struct zone *_new_zone()
{
    struct zone *zone;
    struct block *block;
    bsize_t blocks_count;
    size_t size;

    size = getpagesize() * ZONE_PAGES;
    zone = mmap(NULL, size, PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (zone == MAP_FAILED)
    {
        return NULL;
    }
    blocks_count = (size - sizeof (struct zone)) / BLOCK_BYTES;
    zone->max_block_size = blocks_count;
    zone->max_block_idx = 0;
    zone->blocks_end = blocks_count;
    zone->first_block_idx = 0;
    zone->first_free_idx = 0;
    block = zone->blocks;
    block->size = blocks_count;
    block->prev = 0;
    block->idx = 0;
    block->next_free = NULL_BIDX;
    return zone;
}
