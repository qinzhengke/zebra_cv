#include "../../src/basic/bmp.h"

// Test code, read and write bmp file.

int main(char argc, char **argv)
{
    if(argc < 2)
        return 1;

    uint8_t *img;
    uint32_t w, h;
    if(0 == read_bmp_file_mono(string(argv[1]), &w, &h, &img))
    {
        save_bmp_file_mono("output.bmp", w, h, img);
    }

    if(argc <3)
        return 0;

    if(0 == read_bmp_file_rgb(string(argv[2]), &w, &h, &img))
    {
        save_bmp_file_rgb("output-rgb.bmp", w, h, img);
    }

    return 0;
}
