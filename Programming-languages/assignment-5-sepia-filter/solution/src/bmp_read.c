#include "bmp.h"
#include "image.h"

#define BMP_TYPE 0x4D42

static enum read_status validate_bmp_header(struct bmp_header const *header) {
    if (header->bfType != BMP_TYPE) {
        return READ_INVALID_SIGNATURE;
    }
    if (header->biBitCount != 24) {
        return READ_INVALID_BITS;
    }
    if (header->biPlanes != 1) {
        return READ_INVALID_HEADER;
    }
    if (header->biCompression != 0) {
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}
static enum read_status validateFile(FILE* in){
    if (in == NULL){
        return READ_ERROR;
    }
    return READ_OK;
}

static enum read_status validateImage(struct image* img){
    if (img == NULL){
        return READ_ERROR;
    }
    return READ_OK;
}
// Reads a BMP header from a file
static enum read_status read_bmp_header(FILE* in, struct bmp_header* header) {
    if(!fread(header, sizeof(struct bmp_header), 1, in)){
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}
//Reads pixels from a file
static enum read_status read_pixels(FILE* in, struct image* img, struct bmp_header* header){
    const uint32_t padding = calc_padding(img->width);
    // Read the pixel data for the current row
    for(uint64_t i = 0; i < img->height; i++){
        //Read the entire row one pixel at a time
         uint32_t count = fread(img->data + (img->width) * i, header->biBitCount / 8, img->width, in);
        if (count != img->width) {
            free_image(img);
            return READ_INVALID_BITS;
        }
        // Skip over the padding at the end of the row
        if (fseek(in, padding, SEEK_CUR)) {
            free_image(img);
            return READ_INVALID_BITS;
        }
    }
    return READ_OK;
}

// Reads a BMP image from a file
enum read_status from_bmp_to_image(FILE* in, struct image* img){
    if(validateFile(in) || validateImage(img)){
        return READ_ERROR;
    }
    struct bmp_header header;
    enum read_status status;

    if((status = read_bmp_header(in, &header)) != READ_OK)
        return status;

    if ((status = validate_bmp_header(&header)) != READ_OK)
        return status;

    *img = alloc_image(header.biWidth,header.biHeight);

    return read_pixels(in, img, &header);
}
