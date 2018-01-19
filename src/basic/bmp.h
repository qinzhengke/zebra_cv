#ifndef __BMP_H__
#define __BMP_H__

/**
 * @brief save_bmp_file Save 8-bit gray image in bmp file.
 * @param path [IN] Save path.
 * @param width [IN] Image width.
 * @param height [IN] Image height.
 * @param buf [IN] Image data address.
 * @param palette [IN] 8 bit palette, give NULL to create palette inside.
 * @return 0: success, others: fail.
 */

int save_bmp_file(string path, int width, int height, unsigned char *buf,
                  uint8_t *palette = NULL);

/**
 * @brief read_bmp_file The memory is allocted inside.
 * @param path [IN] Image path.
 * @param W [OUT] Image width.
 * @param H [OUT] Image height.
 * @param data [OUT] Image data address.
 * @return 0: success, non-0: fail.
 */

int read_bmp_file(string path, uint32_t *W, uint32_t *H, uint8_t**data);

#endif
