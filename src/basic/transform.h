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

int rotate_right_angle_clockwise(uint8_t *imgIn, uint32_t W, uint32_t H,
                                 uint32_t pix_size, RotateRightAngle angle,
                                 uint8_t **imgOut, uint32_t* Wo, uint32_t *Ho);

#endif
