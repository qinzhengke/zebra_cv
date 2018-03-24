#ifndef DISP_BMP_T_H
#define DISP_BMP_T_H

#include <stdint.h>
#include <string>

using namespace std;

enum raw_bmp_type_t{
    NOT_RAW_BMP = 0,
    RAW_BMP_INT8,
    RAW_BMP_UINT8,
    RAW_BMP_INT16,
    RAW_BMP_UINT16,
    RAW_BMP_INT32,
    RAW_BMP_UINT32,
    RAW_BMP_FLOAT,
    RAW_BMP_DOUBLE,
    NUM_RAW_BMP_TYPE
};

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint8_t *addr;
    int N;
    double min;
    double max;
}color_map_t;
#pragma pack(pop)

int save_raw_bmp_file(string path, int width, int height, raw_bmp_type_t type,
                     uint8_t *buf,  int cmapN, double cmap_min, double cmap_max);

int read_raw_bmp_file(string path, int *W, int *H, raw_bmp_type_t *type,
                      void** data, uint8_t** data_rgb, color_map_t *cmap_out);



#endif // DISP_BMP_T_H
