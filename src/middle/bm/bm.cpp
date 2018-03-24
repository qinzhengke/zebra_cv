#include <stdint.h>
#include <stdio.h>
#include <limits.h>


/**
 * @brief naive_bm The naive way of block matching.
 * @param img_left [IN] Left image.
 * @param img_right [IN] Right image.
 * @param width [IN] image width.
 * @param height [OUT] image height. The size of two images should be equal.
 * @param W [IN] The size used in calculating cost, i.e., 3 for 3x3, 5 for 5x5.
 * @param max_disp [IN] The max dispairty during matching.
 * @param disp [OUT] disparity image, with memory allocated inside.
 * @return 0 if success.
 */

int naive_bm(uint8_t* img_left, uint8_t* img_right, int width, int height, int W,
             int max_disp, int32_t *disp)
{
    if(width>10000 || height >10000)
    {
        printf("[ERROR], naive_bm, invalid width: %d or height: %d\n", width, height);
        return 1;
    }

    int r,cp;
    for(r=0; r<height; r++)
    {

        for(cp=0; cp<width; cp++)
        {
            uint8_t vp = img_left[r*width+cp];
            int min_cost = INT_MAX;
            int disp_min_cost = 0;
            int i;
            for(i=0; i<max_disp; i++)
            {
                int cq = cp - i;
                if(cq < 0)
                    continue;
                int rw, cw;
                for(rw=-W/2; rw<=W/2; rw++)
                {
                    if(r+rw < 0 || r+rw >height-1)
                        continue;
                    for(cw=-W/2; cw<W/2; cw++)
                    {
                        if(cp+cw<0 || cp+cw>width-1 || cq+cw<0 || cq+cw>width-1)
                            continue;
                    }

                }
            }
        }
    }
    return 0;
}
