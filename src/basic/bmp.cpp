#include <stdint.h>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

# pragma pack(push)
# pragma pack(1)
typedef struct {
    /* type : Magic identifier,BM(0x42,0x4d) */
    unsigned short int type;
    unsigned int size;/* File size in bytes */
    unsigned short int reserved1, reserved2;
    unsigned int offset;/* Offset to image data, bytes */
} BmpFileHeader;

typedef struct {
    unsigned int size;/* Info Header size in bytes */
    int width, height;/* Width and height of image */
    unsigned short planes;/* Number of colour planes */
    unsigned short bits; /* Bits per pixel */
    unsigned int compression; /* Compression type */
    unsigned int imagesize; /* Image size in bytes */
    int xresolution, yresolution; /* Pixels per meter */
    unsigned int ncolours; /* Number of colours */
    unsigned int importantcolours; /* Important colours */
} BmpInfoHeader;
#pragma pack(pop)

class img_size_t
{
public:
    img_size_t(){}
    img_size_t(uint32_t cols, uint32_t rows)
    {
        this->cols = cols;
        this->rows = rows;
    }
    uint32_t cols;
    uint32_t rows;
};

uint8_t g_bmp_palette[1024];

int init_bmp_header(BmpFileHeader *fh, BmpInfoHeader *ih, int width, int height)
{
    ih->size = sizeof(BmpInfoHeader);
    ih->width = width;
    ih->height = -height; // save data from up to down.
    ih->planes = 1;
    ih->bits = 8;
    ih->compression = 0;
    ih->imagesize = width*height;
    ih->xresolution = 0;
    ih->yresolution = 0;
    ih->ncolours = 0;
    ih->importantcolours = 0;


    fh->type = 0x4d42;
    fh->size = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader) + 1024 + width*height;
    fh->offset = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader) + 1024;
    fh->reserved1 = 0;
    fh->reserved2 = 0;

    return 0;
}

int save_bmp_file(string path, int width, int height, unsigned char *buf, uint8_t *palette = NULL)
{
    ofstream file(path, ios::binary);
    if (!file.is_open())
    {

        cout<<"Cannot open file to write,"<<endl;
        return 1;
    }

    BmpFileHeader fh;
    BmpInfoHeader ih;
    init_bmp_header(&fh, &ih, width, height);

    file.write((char*)(&fh), sizeof(BmpFileHeader));
    file.write((char*)(&ih), sizeof(BmpInfoHeader));
    if(NULL == palette) // Create a new palette
    {
        uint8_t palette_loc[1024];
        for (int i = 0; i < 256; i++)
        {
            palette_loc[i*4] = i;
            palette_loc[i*4+1] = i;
            palette_loc[i*4+2] = i;
            palette_loc[i*4+3] = 0;
        }
        file.write((char*)palette_loc, 1024);
    }
    else
    {
        file.write((char*)palette, 1024);
    }
    file.write((char*)buf, ih.imagesize);
    file.close();


    return 0;
}

/**
 * @brief read_bmp_file The memory is allocted inside.
 * @param path [IN] Image path.
 * @param W [OUT] Image width.
 * @param H [OUT] Image height.
 * @param data [OUT] Image data address.
 * @return 0: success, non-0: fail.
 */
int read_bmp_file(string path, uint32_t *W, uint32_t *H, uint8_t**data)
{
    ifstream ifs(path, ios::binary);
    if(!ifs.is_open())
    {
        cout<<"[ERROR], read_bmp_file, Cannot open file: "<<path<<endl;
        return 1;
    }

    BmpFileHeader fh;
    BmpInfoHeader ih;
    ifs.read((char*)(&fh), sizeof(BmpFileHeader));
    ifs.read((char*)(&ih), sizeof(BmpInfoHeader));
    int w = ih.width;
    int h = abs(ih.height);
    if(ih.imagesize != w*h)
    {
        cout<<"[ERROR], read_bmp_file, Only support 8-bit bmp image!"<<endl;
        return 1;
    }

    uint8_t *data_addr = new uint8_t[w*h];
    ifs.seekg(fh.offset, ios::beg);
    if(ih.height <0 )
    {
        ifs.read((char*)data_addr, ih.imagesize);
    }
    else    // Flip image in vertical direction.
    {
        for(int r=h-1; r>=0; r--)
        {
            ifs.read((char*)(data_addr+w*r), w);
        }
    }

    *W = w;
    *H = h;
    *data = data_addr;

    return 0;
}

// Test code, read and write bmp file.
#if 1
int main(char argc, char **argv)
{

    if(argc < 2)
        return 1;

    uint8_t *img;
    uint32_t w, h;
    read_bmp_file(string(argv[1]), &w, &h, &img);
    save_bmp_file("output.bmp", w, h, img);
    return 0;
}
#endif
