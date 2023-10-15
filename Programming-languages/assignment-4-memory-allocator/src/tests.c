#define _DEFAULT_SOURCE
/*file for tests:
 * 1. The test is a normal successful memory allocation.
 * 2. The test is freeing one block from several allocated ones.
 * 3. The test is the freeing of two blocks from several allocated ones.
 * 4. The test memory is over, the new memory region expands the old one.
 * 5. The test memory is over, the old memory region cannot be expanded
 * due to a different allocated address range, the new region is allocated elsewhere.
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "mem.h"
#include "mem_internals.h"
#include "tests.h"
#define HEAP_SIZE (100 * 1024) // heap size is 100 KB
#define BLOCK1_SIZE (40 * 1024) // block1 size is 40KB
#define BLOCK2_SIZE (10 * 1024) // block2 size is 10KB
#define BLOCK3_SIZE (7 * 1024) // block3 size is 7KB
#define BLOCK_TEST4_SIZE (140 * 1024) // block4 size is 140KB
static bool is_valid(void* item, const char* error_message) {
    if (item == NULL) {
        printf("Error: %s\n", error_message);
        return false;
    }
    return true;
}
static void heap_free( void* heap ){
    munmap( heap, HEAP_SIZE );
}
struct block_header* block_header_from_block(void* block) {
    return block - offsetof(struct block_header, contents);
}

//The test is a normal successful memory allocation.
bool test1(){
    printf("Test 1: Normal successful memory allocation\n");
    printf("Initialize the heap with 100KB of memory\n");
    void* heap = heap_init(0);
    is_valid(heap, "heap_init failed");
    debug_heap(stdout, heap);
    printf("Allocate block of memory, 10KB\n");
    void *block1 = _malloc(0);
    is_valid(block1, "malloc failed");
    debug_heap(stdout, heap);
    printf("Free the first block\n");
    _free(block1);
    debug_heap(stdout, heap);
    printf("Free the heap\n");
    munmap(HEAP_START, HEAP_SIZE);
    return true;
}

//The test is freeing one block from several allocated ones.
bool test2(){
    printf("Test 2: Freeing one block from several allocated ones\n");
    printf("Initialize the heap with 100KB of memory\n");
    void* heap = heap_init(HEAP_SIZE);
    is_valid(heap, "heap_init failed");
    debug_heap(stdout, heap);
    printf("Allocate 3 blocks of memory, 40KB, 10KB, and 7KB\n");
    void *block1 = _malloc(BLOCK1_SIZE);
    void *block2 = _malloc(BLOCK2_SIZE);
    void *block3 = _malloc(BLOCK3_SIZE);
    is_valid(block1, "malloc block1 failed");
    is_valid(block2, "malloc block2 failed");
    is_valid(block3, "malloc block3 failed");
    debug_heap(stdout, heap);
    printf("Free the middle block\n");
    _free(block2);
    if(block_header_from_block(block1)->is_free || !block_header_from_block(block2)->is_free ||
    block_header_from_block(block3)->is_free){
        printf("Error: _free failed\n");
        return false;
    }
    debug_heap(stdout, heap);
    _free(block1);
    _free(block3);
    heap_free(heap);
    return true;
}

//The test is the freeing of two blocks from several allocated ones.
bool test3(){
    printf("Test 3: Freeing of two blocks from several allocated ones\n");
    printf("Initialize the heap with 100KB of memory\n");
    void* heap = heap_init(HEAP_SIZE);
    is_valid(heap, "heap_init failed");
    debug_heap(stdout, heap);
    printf("Allocate 3 blocks of memory, 40KB, 10KB, and 7KB\n");
    void *block1 = _malloc(BLOCK1_SIZE);
    void *block2 = _malloc(BLOCK2_SIZE);
    void *block3 = _malloc(BLOCK3_SIZE);
    is_valid(block1, "malloc block1 failed");
    is_valid(block2, "malloc block2 failed");
    is_valid(block3, "malloc block3 failed");
    debug_heap(stdout, heap);
    printf("Free first and middle blocks\n");
    _free(block1);
    _free(block2);
    if(!block_header_from_block(block1)->is_free || !block_header_from_block(block2)->is_free ||
       block_header_from_block(block3)->is_free){
        printf("Error: _free failed\n");
        return false;
    }
    debug_heap(stdout, heap);
    _free(block3);
    heap_free(heap);
    return true;
}

//The test memory is over, the new memory region expands the old one.
bool test4(){
    printf("Test 4: Memory is over, the new memory region expands the old one.\n");
    printf("Initialize the heap with 100KB of memory\n");
    void* heap = heap_init(HEAP_SIZE);
    is_valid(heap, "heap_init failed");
    debug_heap(stdout, heap);
    printf("Allocate block 140KB of memory\n");
    void *block1 = _malloc(BLOCK_TEST4_SIZE);
    is_valid(block1, "malloc block1 failed");
    debug_heap(stdout, heap);
    _free(block1);
    heap_free(heap);
    return true;
}

//The test memory is over, the old memory region cannot be expanded due to a different allocated address range, the new region is allocated elsewhere.
bool test5(){
    printf("Test 5: Memory is over, the old memory region cannot be expanded due to a different allocated address range, the new region is allocated elsewhere.\n");
    printf("Initialize the heap...\n");
    void* heap = heap_init(REGION_MIN_SIZE);
    is_valid(heap, "heap_init failed");
    printf("Allocate block 1...\n");
    void *block1 = _malloc(REGION_MIN_SIZE);
    is_valid(block1, "malloc block1 failed");
    if(block_header_from_block(block1)->capacity.bytes != REGION_MIN_SIZE){
        printf("Error: _malloc failed\n");
        return false;
    }
    debug_heap(stdout, heap);
    void *next_block = mmap(HEAP_START + REGION_MIN_SIZE,REGION_MIN_SIZE,
                        PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
    if(next_block == MAP_FAILED){
        printf("Error: mmap failed\n");
        return false;
    }
    debug_heap(stdout, heap);
    printf("Allocate block 2 ...\n");
    void *block2 = _malloc(REGION_MIN_SIZE);
    is_valid(block2, "memory for block 2 is not allocated\n");
    debug_heap(stdout, heap);
    printf("Free the block\n");
    _free(block1);
    _free(block2);
    heap_free(heap);
    return true;
}