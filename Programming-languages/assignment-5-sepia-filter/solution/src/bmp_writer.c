#include "bmp.h"

// Writes an 'image' struct to a BMP image file
enum write_status from_image_to_bmp(FILE* out, const struct image* img) {
    // Write the BMP header
    struct bmp_header header;
    header.bfType = 0x4d42;
    header.bfileSize = sizeof(header) + img->width * img->height * sizeof(struct pixel) + calc_padding(img->width);
    header.bfReserved = 0;
    header.bOffBits = sizeof(header);
    header.biSize = sizeof(header) - 14;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    if (fwrite(&header, sizeof header, 1, out) != 1) {
        return WRITE_ERROR;
    }
    // Write the image data
    for (size_t i = 0; i < img->height; i++) {
        fwrite(img->data + i * img->width, sizeof(struct pixel), img->width, out);
        fseek(out, calc_padding(img->width), SEEK_CUR);
    }

    return WRITE_OK;
}
