#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct __attribute__((packed)) pixel {
    uint8_t r, g, b;
};

struct image {
    size_t width, height;
    struct pixel* data;
};

size_t calc_padding(size_t width);

struct image alloc_image(size_t width, size_t height);

void free_image(struct image* img);
