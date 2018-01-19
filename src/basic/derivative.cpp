#include <iostream>

#include <stdint.h>

using namespace std;

#ifndef __FUNC_INOUT__
#define __FUNC_INOUT__
#define IN
#define OUT
#endif

/**
 * @brief calc_img_derivative The memory is alloced inside.
 * @param img [IN] Input image.
 * @param W [IN] Width of input image.
 * @param H [IN] Height of input image.
 * @param img_deri_x [OUT] Output derivative image of x.
 * @param img_deri_y [OUT] Output derivative image of y.
 * @return
 */

int calc_img_derivative(uint8_t* img, int32_t W, int32_t H,
                        int32_t **img_deri_x, int32_t **img_deri_y)
{
    int32_t *deri_x = (int32_t*)calloc(1, W*H*sizeof(int32_t));
    int32_t *deri_y = (int32_t*)calloc(1, W*H*sizeof(int32_t));
    if(NULL == *deri_x && NULL == *deri_y)
    {
        printf("[ERROR] in %s, @ malloc !", __LINE__);
        return 1;
    }

    int r,c;
    for(r=1; r<H-1; r++)
    {
        for(c=1; c<W-1; c++)
        {
            deri_x[r*W+c] = ((int32_t)img[r*W+c+1] - (int32_t)img[r*W+c-1])/2;
            deri_y[r*W+c] = ((int32_t)img[(r+1)*W+c] - (int32_t)img[(r-1)*W+c-1])/2;
        }
    }

    *img_deri_x = deri_x;
    *img_deri_y = deri_y;
    return 0;
}

int main(char argc, char **argv)
{

    return 0;
}
