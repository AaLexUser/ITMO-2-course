#include "bmp.h"
#define BMP_TYPE 0x4d42
#define BMP_RESERVED 0
#define BMP_PLANES 1
#define BMP_COMPRESSION 0
#define BMP_BITS 24
#define BMP_IMAGE_SIZE 0
#define BMP_X_PELS_PER_METER 0
#define BMP_Y_PELS_PER_METER 0
#define BMP_CLR_USED 0
#define BMP_CLR_IMPORTANT 0



// Reads a BMP image from a file and returns the image data as an 'image' struct
enum read_status from_bmp(FILE* in, struct image* img) {
    // Read the BMP header
    struct bmp_header header;
    if(!fread(&header, sizeof(header), 1, in)){
        return READ_INVALID_HEADER;
    };

    // Check that this is a BMP file
    if (header.bfType != 0x4d42) {
        // Not a BMP file
        return READ_INVALID_SIGNATURE;
    }
    const size_t padding = calc_padding(header.biWidth);

    // Read the image data
    *img = alloc_image(header.biWidth,header.biHeight) ;
    for(uint64_t i = 0; i < img->height; i++){
        if (fread(img->data + img->width * i, sizeof(struct pixel), img->width, in) != img->width) {
            free_image(img);
            return READ_INVALID_BITS;
        }
        if (fseek(in, (int64_t)padding, SEEK_CUR)) {
            free_image(img);
            return READ_INVALID_BITS;
        }
    }
    return READ_OK;
}

// Writes an 'image' struct to a BMP image file
enum write_status to_bmp(FILE* out, const struct image* img) {
    // Write the BMP header
    struct bmp_header header = {0};
    header.bfType = BMP_TYPE;
    header.bfileSize = sizeof(header) + img->width * img->height * sizeof(struct pixel) + calc_padding(img->width);
    header.bfReserved = BMP_RESERVED;
    header.bOffBits = sizeof(header);
    header.biSize = sizeof(header) - 14;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes =  BMP_PLANES;
    header.biBitCount = BMP_BITS;
    header.biCompression = BMP_COMPRESSION;
    header.biSizeImage = BMP_IMAGE_SIZE;
    header.biXPelsPerMeter = BMP_X_PELS_PER_METER;
    header.biYPelsPerMeter = BMP_Y_PELS_PER_METER;
    header.biClrUsed = BMP_CLR_USED;
    header.biClrImportant = BMP_CLR_IMPORTANT;
    if (fwrite(&header, sizeof header, 1, out) != 1) {
        return WRITE_ERROR;
    }
    // Write the image data
    for (size_t i = 0; i < img->height; i++) {
        fwrite(img->data + i * img->width, sizeof(struct pixel), img->width, out);
        fseek(out, (int64_t)calc_padding(img->width), SEEK_CUR);
    }

    return WRITE_OK;
}
