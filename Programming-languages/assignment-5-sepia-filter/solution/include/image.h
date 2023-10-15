#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};

uint32_t calc_padding(uint32_t width);

struct image alloc_image(uint32_t width, uint32_t height);

void free_image(struct image* img);

struct pixel get_image_pixel(struct image const* source, size_t row, size_t col);

void set_image_pixel(struct image const* target, struct pixel pixel, size_t row, size_t col);
