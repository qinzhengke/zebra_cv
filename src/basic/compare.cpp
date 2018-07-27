#include <stdint.h>

#include "compare.h"


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

/**
 * @brief compare_patch
 * @param img1
 * @param W1
 * @param W2
 * @param img2
 * @param W2
 * @param H2
 * @param x_off left up corner of img1 in img2
 * @param y_off
 * @return
 */
int compare_patch(uint8_t *img1, uint32_t W1, uint32_t H1, uint8_t *img2,
                  uint32_t W2, uint32_t H2, uint32_t x_off, uint32_t y_off,
                  float *cost)
{
    float n = 0.0;
    float sum_xx = 0.0;
    float sum_x = 0.0;
    for(int r1=0; r1<H1; r1++)
    {
        for(int c1=0; c1<W1; c1++)
        {
            int r2 = r1 + y_off;
            int c2 = c1 + x_off;
            if(r2<0 || r2>H2-1 || c2<0 || c2>W2-1)
            {
                continue;
            }
            float dv = img1[r1*W1+c1] - img2[r2*W2+c2];
            sum_xx += dv*dv;
            sum_x += dv;
            n += 1.0;
        }
    }
    if(0.0 > n)
    {
        PRINT_ERROR("n=0");
        return -1;
    }

    (*cost) = sum_xx/n - sum_x*sum_x/n/n;

    return 0;
}

