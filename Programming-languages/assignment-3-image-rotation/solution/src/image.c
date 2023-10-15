#include "image.h"


// Calculates the number of padding bytes
size_t calc_padding(size_t width) {
    return 4 - sizeof(struct pixel) * width % 4;
}

// Allocates memory for a new image with the given dimensions
struct image alloc_image(size_t width, size_t height) {
    struct image img;
    img.width = width;
    img.height = height;
    img.data = malloc(img.width * img.height * sizeof(struct pixel));
    if (!img.data) {
        // Handle error allocating memory for the image
        printf("Failed to allocate memory for the image data\n");
    }
    return img;
}

// Frees the memory allocated for an image
void free_image(struct image* img) { free(img->data); }

