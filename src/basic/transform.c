#include <stdint.h>

#include "transform.h"

int rotate_right_angle_clockwise(uint8_t *imgIn, uint32_t W, uint32_t H,
                                 uint32_t pix_size, RotateRightAngel angle,
                                 uint8_t **imgOut)
{
    uint32_t cos_alphas[NUM_ROATE_RIGHT_ANGLE] = {0, -1, 0};
    uint32_t sin_alphas[NUM_ROATE_RIGHT_ANGLE] = {1, 0, -1};

    uint32_t x_ci = W/2;
    uint32_t y_ci = H/2;
    return 0;
}
