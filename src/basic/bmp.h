#ifndef __BMP_H__
#define __BMP_H__

#include <string>
#include <stdint.h>
using namespace std;

/**
 * @brief save_bmp_file_mono Save 8-bit gray image in bmp file.
 * @param path [IN] Save path.
 * @param width [IN] Image width.
 * @param height [IN] Image height.
 * @param buf [IN] Image data address.
 * @param palette [IN] 8 bit palette, give NULL to create palette inside.
 * @return 0: success, others: fail.
 */

int save_bmp_file_mono(string path, int width, int height, unsigned char *buf,
                  uint8_t *palette = NULL);

/**
 * @brief save_bmp_file_rgb Save 24-bit rgb image in bmp file.
 * @param path [IN] Save path.
 * @param width [IN] Image width.
 * @param height [IN] Image height.
 * @param buf [IN] Image data address.
 * @return 0: success, others: fail.
 */

int save_bmp_file_rgb(string path, int width, int height, unsigned char *buf);

/**
 * @brief read_bmp_file_mono Read 8-bit mono bmp image.
 *        The memory is allocted inside.
 * @param path [IN] Image path.
 * @param W [OUT] Image width.
 * @param H [OUT] Image height.
 * @param data [OUT] Image data address.
 * @return 0: success, others: fail.
 */

int read_bmp_file_mono(string path, uint32_t *W, uint32_t *H, uint8_t**data);

/**
 * @brief read_bmp_file_mono Read 24-bit rgb bmp image.
 *        The memory is allocted inside.
 * @param path [IN] Image path.
 * @param W [OUT] Image width.
 * @param H [OUT] Image height.
 * @param data [OUT] Image data address.
 * @return 0: success, others: fail.
 */

int read_bmp_file_rgb(string path, uint32_t *W, uint32_t *H, uint8_t**data);

#endif
