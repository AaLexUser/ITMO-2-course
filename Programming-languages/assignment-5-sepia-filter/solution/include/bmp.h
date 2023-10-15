#pragma once
#include "image.h"
#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
struct bmp_header
{
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};
#pragma pack(pop)
/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_ERROR
    /* коды других ошибок  */
};

enum read_status from_bmp_to_image( FILE* in, struct image* img );

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR
    /* коды других ошибок  */
};

enum write_status from_image_to_bmp(FILE* out, struct image const* img );
