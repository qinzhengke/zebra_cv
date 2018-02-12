#include <stdint.h>


/**
 * @brief naive_bm The naive way of block matching.
 * @param img_left [IN] Left image.
 * @param img_right [IN] Right image.
 * @param width [IN] image width.
 * @param height [OUT] image height. The size of two images should be equal.
 * @param W [IN] The size used in calculating cost, i.e., 3 for 3x3, 5 for 5x5.
 * @param disp [OUT] disparity image, with memory allocated inside.
 * @return 0 if success.
 */

int naive_bm(uint8_t* img_left, uint8_t* img_right, int width, int height, int W, int32_t *disp)
{
    int r,c;
    for(r=0; r<height; r++)
    {
        for(c=0; c<width; c++)
        {

        }
    }
    return 0;
}
