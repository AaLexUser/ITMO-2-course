#define _DEFAULT_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "mem_internals.h"
#include "mem.h"
#include "util.h"
#define BLOCK_MIN_CAPACITY 24

void debug_block(struct block_header* b, const char* fmt, ... );
void debug(const char* fmt, ... );

extern inline block_size size_from_capacity( block_capacity cap );
extern inline block_capacity capacity_from_size( block_size sz );

static bool            block_is_big_enough( size_t query, struct block_header* block ) { return block->capacity.bytes >= query; }
static size_t          pages_count   ( size_t mem )                      { return mem / getpagesize() + ((mem % getpagesize()) > 0); }
static size_t          round_pages   ( size_t mem )                      { return getpagesize() * pages_count( mem ) ; }

static void block_init( void* restrict addr, block_size block_sz, void* restrict next ) {
  *((struct block_header*)addr) = (struct block_header) {
    .next = next,
    .capacity = capacity_from_size(block_sz),
    .is_free = true
  };
}

static size_t region_actual_size( size_t query ) { return size_max( round_pages( query ), REGION_MIN_SIZE ); }

extern inline bool region_is_invalid( const struct region* r );



static void* map_pages(void const* addr, size_t length, int additional_flags) {
  return mmap( (void*) addr, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | additional_flags , -1, 0 );
}

/*  аллоцировать регион памяти и инициализировать его блоком */
static struct region alloc_region  ( void const * addr, size_t query ) {
    const size_t region_size = region_actual_size(size_from_capacity((block_capacity){query}).bytes);
    void* region_start = map_pages(addr, region_size, MAP_FIXED_NOREPLACE);
    if (region_start == MAP_FAILED) {
        region_start = map_pages(addr, region_size, 0);
    }
    if (region_start == MAP_FAILED) {
        return REGION_INVALID;
    }

    struct region region = { .addr = region_start, .size = region_size, .extends = region_start == addr };
    if(!region_is_invalid(&region)) {
        block_size block_size = { .bytes = region_size };
        block_init(region_start, block_size, NULL);
    }
    return region;
}

static void* block_after( struct block_header const* block )         ;

void* heap_init( size_t initial ) {
  const struct region region = alloc_region( HEAP_START, initial );
  if ( region_is_invalid(&region) ) return NULL;

  return region.addr;
}


/*  --- Разделение блоков (если найденный свободный блок слишком большой )--- */

static bool block_splittable( struct block_header* restrict block, size_t query) {
  return block-> is_free && query + offsetof( struct block_header, contents ) + BLOCK_MIN_CAPACITY <= block->capacity.bytes;
}
/* Split a block into two blocks if it is larger than the required size,
 * and return true. If the block is not splittable (i.e., it is already
 * at the minimum capacity), return false.
 */
static bool split_if_too_big( struct block_header* block, size_t query ) {
    /* Check if the block can be split */
    if (!block_splittable(block, query)) return false;
    /* Calculate the size of the block before the split */
    block_size before_split_sz = size_from_capacity(
            (block_capacity){size_max(query, BLOCK_MIN_CAPACITY)});
    /* Calculate the size of the block after the split */
    block_size after_split_sz = size_from_capacity((block_capacity)
            {block->capacity.bytes - before_split_sz.bytes});

    /* Calculate the address of the block after the split */
    void* block_after_split_addr = (char*)block + before_split_sz.bytes;

    /* Initialize the block after the split */
    block_init(block_after_split_addr, after_split_sz, block->next);
    /* Update the block before the split */
    block->capacity = capacity_from_size(before_split_sz);
    /* Update the original block's next field to point to the block after the split */
    block->next = block_after_split_addr;
    return true;
}

/*  --- Слияние соседних свободных блоков --- */

static void* block_after( struct block_header const* block )              {
  return  (void*) (block->contents + block->capacity.bytes);
}
static bool blocks_continuous (
                               struct block_header const* fst,
                               struct block_header const* snd ) {
  return (void*)snd == block_after(fst);
}

static bool mergeable(struct block_header const* restrict fst, struct block_header const* restrict snd) {
  return fst->is_free && snd->is_free && blocks_continuous( fst, snd ) ;
}

static bool try_merge_with_next( struct block_header* block ) {
    // Check if block or next block are null or if blocks are not mergeable
    struct block_header* next = block->next;
    if (!block || !next || !mergeable(block, next)) return false;

    // Increase the capacity of the current block by the size of the next block
    block->capacity.bytes += size_from_capacity(next->capacity).bytes;
    // Set the next block of the current block to the next block of the next block
    block->next = next->next;
    return true;
}


/*  --- ... ecли размера кучи хватает --- */

struct block_search_result {
  enum {BSR_FOUND_GOOD_BLOCK, BSR_REACHED_END_NOT_FOUND, BSR_CORRUPTED} type;
  struct block_header* block;
};


static struct block_search_result find_good_or_last  ( struct block_header* restrict block, size_t sz )    {
    struct block_header* prev_block = block;
    while (block) {
        while (try_merge_with_next(block));
        if( block->is_free && block_is_big_enough(sz, block) )
            return (struct block_search_result) { .block = block, .type = BSR_FOUND_GOOD_BLOCK };
        prev_block = block;
        block = block->next;
    }
    if(prev_block->next == NULL){
        return (struct block_search_result) {BSR_REACHED_END_NOT_FOUND, prev_block};
    }else {
        return (struct block_search_result) {BSR_CORRUPTED, NULL};
    }
}

/*  Попробовать выделить память в куче начиная с блока `block` не пытаясь расширить кучу
 Можно переиспользовать как только кучу расширили. */
static struct block_search_result try_memalloc_existing ( size_t query, struct block_header* block ) {
    struct block_search_result result = find_good_or_last(block, query);
    if (result.type == BSR_FOUND_GOOD_BLOCK) {
        split_if_too_big(result.block, query);
        result.block->is_free = false;
        return result;
    }
    return result;
}

/*  Grow the heap by allocating a new region of memory and adding it to the end of the heap.
 Returns a pointer to the new region, or NULL if the allocation failed. */
static struct block_header* grow_heap( struct block_header* restrict last, size_t query ) {
    if (last == NULL) return NULL;
    const struct region region = alloc_region(block_after(last), query);
    if (region_is_invalid(&region)) return NULL;
    if(region.extends && last->is_free){
        last->capacity.bytes += region.size;
        return last;
    }
    last->next = region.addr;
    return region.addr;
}

/*  Реализует основную логику malloc и возвращает заголовок выделенного блока */
static struct block_header* memalloc( size_t query, struct block_header* heap_start) {
    query = size_max(query, BLOCK_MIN_CAPACITY); // Ensure that the block is at least BLOCK_MIN_CAPACITY bytes long
    // Try to allocate memory within the existing heap
    struct block_search_result result = try_memalloc_existing(query, heap_start);
    if (result.type == BSR_FOUND_GOOD_BLOCK) return result.block;
    // No suitable block was found within the existing heap, try to extend the heap
    struct block_header* new_block = grow_heap(result.block, query);
    if (new_block == NULL) return NULL; // Heap extension failed
    // Heap was successfully extended, split the new block if needed and mark it as allocated
    split_if_too_big(new_block, query);
    new_block->is_free = false;
    return new_block;
}

void* _malloc( size_t query ) {
  struct block_header* const addr = memalloc( query, (struct block_header*) HEAP_START );
    return (addr) ? addr->contents  : NULL;
}

static struct block_header* block_get_header(void* contents) {
  return (struct block_header*) (((uint8_t*)contents)-offsetof(struct block_header, contents));
}

void _free( void* mem ) {
  if (!mem) return ;
  struct block_header* header = block_get_header( mem );
  header->is_free = true;
  while (try_merge_with_next(header));
}
