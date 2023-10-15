#include "image.h"
#include "bmp.h"
#include "rotate.h"
#include <stdio.h>

int main( int argc, char** argv ) {
    // Check that the user provided the input and output filenames
    if (argc != 3) {
        printf("Usage: %s input.bmp output.bmp\n", argv[0]);
        return 1;
    }
    // Open the input file
    FILE *in_file = fopen(argv[1], "rb");
    if (!in_file) {
        printf("Error opening input file\n");
        return 1;
    }
    // Open the output file
    FILE *out_file = fopen(argv[2], "wb");
    if (!out_file) {
        printf("Error opening output file\n");
        return 1;
    }

    // Read the input image
    struct image img;
    if(from_bmp(in_file, &img)){
        fclose(in_file);
        fclose(out_file);
        free_image(&img);
        fprintf(stderr, "Failed to read bmp image\n");
    }
    if (!img.data) {
        fprintf(stderr, "Failed to read input image\n");
        return 1;
    }

    // Rotate the image
    struct image rotated = rotate(&img);
    // Write the rotated image to the output file
    if (to_bmp(out_file, &rotated) != WRITE_OK) {
        fclose(in_file);
        fclose(out_file);
        free_image(&rotated);
        free_image(&img);
        fprintf(stderr, "Failed to write output image\n");
        return 1;
    }
    // Free up the memory used by the image
    free_image(&img);
    free_image(&rotated);
    // Close the files
    fclose(in_file);
    fclose(out_file);

    return 0;
}
