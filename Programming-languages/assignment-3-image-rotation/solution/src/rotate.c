#include "rotate.h"

/* создаёт копию изображения, которая повёрнута на 90 градусов */
struct image rotate(struct image const* img ){
// Create a new image structure to hold the rotated image
    struct image rotated = alloc_image(img->height, img->width);

    // Rotate the image 90 degrees counterclockwise
    for (size_t y = 0; y < rotated.height; y++) {
        for (size_t x = 0; x < rotated.width; x++) {
            rotated.data[y * rotated.width + x] = img->data[(img->height - x) * img->width + y - img->width];
        }
    }

    return rotated;
}
