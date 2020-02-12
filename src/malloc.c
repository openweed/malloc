#include <unistd.h>
#include <sys/mman.h>

#include "malloc.h"

static struct zone *root = NULL;

static struct zone *new_zone()
{
    struct zone *zone;
    struct block *last_block;
    size_t blocks_count;
    size_t size;

    size = getpagesize() * ZONE_PAGES;
    zone = mmap(NULL, size, PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (zone == MAP_FAILED)
    {
        return NULL;
    }
    blocks_count = (size - sizeof (struct zone)) / BLOCK_SIZE;
    zone->max_block_size = blocks_count;
    zone->first_free_offset = NULL_OFFSET;
    zone->blocks_count = blocks_count;
    zone->first_block_offset = 0;
}

static struct zone *get_zone(size_t blocks)
{
    struct zone *zone;

    zone = search(root, blocks);
    if (!zone)
    {
        zone = new_zone();
        if (!zone)
            return NULL;
        insert(&root, zone);
    }
    return zone;
}

offset_t get_free_block(struct zone *zone, size_t blocks_count)
{
    offset_t off;
    struct block *blocks;

    off = zone->first_free_offset;
    blocks = zone->blocks;
    while (1)
    {

    }
}

struct block *reserve_block(struct zone *zone, bsize_t size)
{
    offset_t pre_off;
    offset_t blk_off;
    offset_t post_off;
    struct block *block;

    pre_off = zone->first_free_offset;
}

void *malloc(size_t size)
{
	(void)size;
	return NULL;
}
