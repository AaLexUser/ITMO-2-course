#include "image.h"
#include "sepia.h"
#include "bmp.h"
#include <time.h>
#include <math.h>
#include <stdio.h>

int main( int argc, char** argv ) {
    // Check that the user provided the input and output filenames
    if (argc != 4) {
        printf("Usage: %s -[ac] input.bmp output.bmp\n", argv[0]);
        return 1;
    }
    // Open the input file
    FILE *in_file = fopen(argv[2], "rb");
    if (!in_file) {
        printf("Error opening input file\n");
        return 1;
    }
    // Open the output file
    FILE *out_file = fopen(argv[3], "wb");
    if (!out_file) {
        printf("Error opening output file\n");
        return 1;
    }

    // Read the input image
    struct image img;
    if(from_bmp_to_image(in_file, &img)){
        fclose(in_file);
        fclose(out_file);
        free_image(&img);
        fprintf(stderr, "Failed to read bmp image\n");
    }
    if (!img.data) {
        fprintf(stderr, "Failed to read input image\n");
        return 1;
    }
    clock_t start = clock();
    // Apply the sepia filter
    if(argv[1][1]=='c'){
        sepia_filter(&img);
    }
    else if(argv[1][1]=='a'){
        sepia_filter_asm(&img);
    }
    printf("Time: %.2f ms\n", (((float)(clock() - start) / CLOCKS_PER_SEC)*1000)); // Time in ms

    // Write the rotated image to the output file
    if (from_image_to_bmp(out_file, &img)) {
        fclose(in_file);
        fclose(out_file);
        free_image(&img);
        fprintf(stderr, "Failed to write output image\n");
        return 1;
    }
    // Free up the memory used by the image
    free_image(&img);
    // Close the files
    fclose(in_file);
    fclose(out_file);

    return 0;
}
