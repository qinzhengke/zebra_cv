#include "../../src/basic/bmp.h"

// Test code, read and write bmp file.

int main(char argc, char **argv)
{
    if(argc < 2)
        return 1;

    uint8_t *img;
    uint32_t w, h;
    if(0 == read_bmp_file(string(argv[1]), &w, &h, &img))
    {
        save_bmp_file("output.bmp", w, h, img);
    }
    return 0;
}
