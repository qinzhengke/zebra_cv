#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <stdint.h>

enum RotateRightAngle
{
    ROTATE_90 = 0,
    ROTATE_180,
    ROTATE_270,
    NUM_ROATE_RIGHT_ANGLE
};

/**
 * @brief rotate_right_angle_clockwise
 * Rotate a map, only for right angle, which is 90, 180 and 270 degree.
 * The transform is logical, contains no float numerical error.
 * @param imgIn [IN]
 * @param W [IN]
 * @param H [IN]
 * @param pix_size [IN] The size of each pixel, e.g., mono uint8 map is 1.
 * @param angle [IN]
 * @param imgOut [OUT]
 * @param Wo [OUT]
 * @param Ho [OUT]
 * @return
 */
int rotate_right_angle_clockwise(uint8_t *imgIn, uint32_t W, uint32_t H,
                                 uint32_t pix_size, RotateRightAngle angle,
                                 uint8_t **imgOut, uint32_t* Wo, uint32_t *Ho);

int down_sample(uint8_t* img_in, uint32_t W, uint32_t H, uint32_t d,
                uint32_t pix_size, uint8_t **img_out, uint32_t *Wo,
                uint32_t *Ho);

#endif
