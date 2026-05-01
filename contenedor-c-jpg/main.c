#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

#define WIDTH 800
#define HEIGHT 600
#define CHANNELS 3

int main() {
    const char *filename = "salida.jpg";

    unsigned char *image = malloc(WIDTH * HEIGHT * CHANNELS);
    if (image == NULL) {
        printf("Error: no se pudo reservar memoria.\n");
        return 1;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int index = (y * WIDTH + x) * CHANNELS;

            image[index] = (unsigned char)(x * 255 / WIDTH);
            image[index + 1] = (unsigned char)(y * 255 / HEIGHT);
            image[index + 2] = 150;
        }
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *outfile = fopen(filename, "wb");
    if (!outfile) {
        printf("Error: no se pudo crear el archivo %s\n", filename);
        free(image);
        return 1;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = WIDTH;
    cinfo.image_height = HEIGHT;
    cinfo.input_components = CHANNELS;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride = WIDTH * CHANNELS;

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = &image[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    fclose(outfile);
    free(image);

    printf("Imagen JPG generada correctamente: %s\n", filename);

    return 0;
}