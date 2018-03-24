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

/**
 * @brief save_raw_bmp_file
 * @param path [IN] output path
 * @param width [IN]
 * @param height [IN]
 * @param type [IN] Map data type.
 * @param buf [IN] Map start address.
 * @param cmapN [IN] Color map bins
 * @param cmap_min [IN] minimum value when convert to fake color.
 * @param cmap_max [OUT] Maximum value when convert to fake color.
 * @return 0 if success.
 */
int save_raw_bmp_file(string path, int width, int height, raw_bmp_type_t type,
                     uint8_t *buf,  int cmapN, double cmap_min, double cmap_max);

/**
 * @brief read_raw_bmp_file
 * @param path [IN] Input path.
 * @param W [IN]
 * @param H [IN]
 * @param type [IN] Map data type.
 * @param data [OUT] raw data start address.
 * @param data_rgb [OUT] bmp rgb data start address.
 * @param cmap_out [OUT] color map, Only cmapN, min, and max are valid,
 *        cmap.addr is null, which should be calculated when loading file.
 * @return
 */
int read_raw_bmp_file(string path, int *W, int *H, raw_bmp_type_t *type,
                      void** data, uint8_t** data_rgb, color_map_t *cmap_out);



#endif // DISP_BMP_T_H
