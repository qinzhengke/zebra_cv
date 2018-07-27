#include <stdint.h>
#include <malloc.h>
#include <string.h>

#include "transform.h"

#ifndef PRINT_ERROR
#define PRINT_ERROR(...)    \
    do{ \
        printf("\x1B[41;37m");      \
        printf("[ERROR]");          \
        printf("\x1B[0m");          \
        printf("[%s] ", __func__);  \
        printf(__VA_ARGS__);        \
        printf("\n");               \
    }while(0)
#endif

#ifndef PRINT_INFO
#define PRINT_INFO(...)    \
    do{ \
        printf("\x1B[42;37m");      \
        printf("[INFO] ");          \
        printf("\x1B[0m");          \
        printf(__VA_ARGS__);        \
        printf("\n");               \
    }while(0)
#endif

#ifndef RETURN_IF_ERROR
#define RETURN_IF_ERROR(x)  \
    if(0 != (x))        \
    {                   \
        return (x);     \
    }
#endif

int rotate_right_angle_clockwise(uint8_t *img_in, uint32_t W, uint32_t H,
                                 uint32_t pix_size, RotateRightAngle angle,
                                 uint8_t **img_out, uint32_t* Wo, uint32_t *Ho)
{
    if(NULL == img_in)
    {
        PRINT_ERROR("null input, img_in:%x", img_in);
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
        PRINT_ERROR("null input, img_in:%x", img_in);
        return -1;
    }

    if(d>W || d>H)
    {
        PRINT_ERROR("d is too large, d:%u, W:%u, H:%u", d, W, H);
    }

    *Wo = W / d;
    *Ho = H / d;
    *img_out = (uint8_t*)malloc((*Wo)*(*Ho)*pix_size);

    int r,c;
    for(r=0; r<*Ho; r++)
    {
        for(c=0; c<*Wo; c++)
        {
            uint32_t pos1 = (r*(*Wo)+c)*pix_size;
            uint32_t pos2 = (r*W+c)*d*pix_size;
            memcpy((void*)(*img_out+(r*(*Wo)+c)*pix_size),
                   (void*)(img_in+(r*W+c)*d*pix_size), pix_size);
        }
    }

    return 0;
}

int crop_image(uint8_t *img, uint32_t W, uint32_t H, uint32_t xl, uint32_t yt,
                  uint32_t wp, uint32_t hp, uint8_t **patch)
{
    PRINT_INFO("Crop: xl:%u, yt:%u, wp:%u, hp:%u", xl, yt, wp, hp);
    (*patch) = new uint8_t[wp*hp];
    for(uint32_t r=0; r<hp; r++)
    {
        for(uint32_t c=0; c<wp; c++)
        {
            (*patch)[r*wp+c] = img[(yt+r)*W+xl+c];
        }
    }
    return 0;
}

int calc_high_resolution(uint8_t *img, uint32_t W, uint32_t H, uint32_t facotr,
                         uint8_t **img_out, uint32_t *Wo, uint32_t *Ho)
{
    (*Wo) = W * facotr;
    (*Ho) = H * facotr;
    (*img_out) = new uint8_t[(*Wo)*(*Ho)];
    for(uint32_t r=0; r< (*Ho); r++)
    {
        for(uint32_t c=0; c<(*Wo); c++)
        {
            (*img_out)[r*(*Wo)+c] = img[r/facotr*W+c/facotr];
        }
    }

    return 0;
}

