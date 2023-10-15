#include <math.h>
#include "sepia.h"

// Apply the sepia filter to each pixel in the image
static struct pixel apply_sepia_filter(struct pixel p) {
    static const float transformation_matrix[3][3] = {
            {0.393f, 0.769f, 0.189f},
            {0.349f, 0.686f, 0.168f},
            {0.272f, 0.534f, 0.131f}
    };
    struct pixel sepia_pixel;

    sepia_pixel.r = (uint8_t)fminf(
            transformation_matrix[0][0] * (float)p.r
            + transformation_matrix[0][1] * (float)p.g
            + transformation_matrix[0][2] * (float)p.b, 255);
    sepia_pixel.g = (uint8_t)fminf(
            transformation_matrix[1][0] * (float)p.r
            + transformation_matrix[1][1] * (float)p.g
            + transformation_matrix[1][2] * (float)p.b, 255);
    sepia_pixel.b = (uint8_t)fminf(
            transformation_matrix[2][0] * (float)p.r
            + transformation_matrix[2][1] * (float)p.g
            + transformation_matrix[2][2] * (float)p.b, 255);
    return sepia_pixel;
}

/* Applies a sepia filter to an image. */
void sepia_filter(struct image* img) {

    for (size_t i = 0; i < img->height * img->width; i++) {
        struct pixel origin_pixel = img->data[i];
        struct pixel sepia_pixel = apply_sepia_filter(origin_pixel);
        img->data[i] = sepia_pixel;
    }
}
