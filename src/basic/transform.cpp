#include <stdint.h>
#include <malloc.h>
#include <string.h>

#include "transform.h"

int rotate_right_angle_clockwise(uint8_t *img_in, uint32_t W, uint32_t H,
                                 uint32_t pix_size, RotateRightAngle angle,
                                 uint8_t **img_out, uint32_t* Wo, uint32_t *Ho)
{
    if(NULL == img_in)
    {
        printf("[ERROR], %s null input, img_in:%x", __func__, img_in);
        return -1;
    }
    int32_t cos_alphas[NUM_ROATE_RIGHT_ANGLE] = {0, -1, 0};
    int32_t sin_alphas[NUM_ROATE_RIGHT_ANGLE] = {-1, 0, 1};

    uint32_t x_offs[NUM_ROATE_RIGHT_ANGLE] = {H/2-1, W/2-1, H/2};
    uint32_t y_offs[NUM_ROATE_RIGHT_ANGLE] = {W/2, H/2-1, W/2-1};

    *Wo = angle%2==0 ? H : W;
    *Ho = angle%2==0 ? W : H;

    int32_t cos_a = cos_alphas[angle];
    int32_t sin_a = sin_alphas[angle];
    int32_t x_off = x_offs[angle];
    int32_t y_off = y_offs[angle];

    *img_out = (uint8_t*)malloc(W*H*pix_size);
    int y,x;
    for(y=0; y<H; y++)
    {
        for(x=0; x<W; x++)
        {
            uint32_t xo = (uint32_t)(cos_a*(x-W/2) + sin_a*(y-H/2) + x_off);
            uint32_t yo = (uint32_t)(-sin_a*(x-W/2) + cos_a*(y-H/2) + y_off);
            memcpy((void*)(*img_out + (yo*(*Wo)+xo)*pix_size),
                   (void*)(img_in + (y*W+x)*pix_size),  pix_size);
        }
    }
    return 0;
}

int down_sample(uint8_t* img_in, uint32_t W, uint32_t H, uint32_t d,
                uint32_t pix_size, uint8_t **img_out, uint32_t *Wo,
                uint32_t *Ho)
{
    if(NULL == img_in)
    {
        printf("[ERROR], %s, null input, img_in:%x", __func__, img_in);
        return -1;
    }

    if(d>W || d>H)
    {
        printf("[ERROR], %s, d is too large, d:%u, W:%u, H:%u", d, W, H);
    }

    *Wo = W / d;
    *Ho = H / d;
    *img_out = (uint8_t*)malloc((*Wo)*(*Ho)*pix_size);

    int r,c;
    for(r=0; r<*Ho; r++)
    {
        for(c=0; c<*Wo; c++)
        {
            memcpy((void*)(*img_out+(r*(*Wo)+c)*pix_size),
                   (void*)(img_in+(r*W+c)*d*pix_size), pix_size);
        }
    }

    return 0;
}
