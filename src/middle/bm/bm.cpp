#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

#include "../../basic/compare.h"
#include "../../basic/transform.h"


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

int calc_local_disparity(uint8_t *img_l, uint32_t Wl, uint32_t Hl,
                         uint8_t *img_r, uint32_t Wr, uint32_t Hr,
                         uint32_t xl, uint32_t yt, uint32_t wp, uint32_t hp,
                         float* min_cost_disp, float* min_cost)
{

    int st = 0;

    uint8_t *patch_l, *patch_r;
    uint32_t Wpl = wp, Hpl = hp, Wpr=xl+wp, Hpr=hp;
    st = crop_image(img_l, Wl, Hl, xl, yt, Wpl, Hpl, &patch_l);
    RETURN_IF_ERROR(st);
//    save_bmp_file_mono("patch_l.bmp" , Wpl, Hpl, patch_l);

    st = crop_image(img_r, Wr, Hr, 0, yt, Wpr, Hpr, &patch_r);
    RETURN_IF_ERROR(st);
//    save_bmp_file_mono("patch_r.bmp" , Wpr, Hpr, patch_r);


    uint8_t *patch_l_h, *patch_r_h; // High resolution.
    uint32_t Wplh, Hplh, Wprh, Hprh;
    uint32_t factor = 10;

    st = calc_high_resolution(patch_l, Wpl, Hpl, factor, &patch_l_h, &Wplh, &Hplh);
    RETURN_IF_ERROR(st);
//    save_bmp_file_mono("patch_h_l.bmp" , Wplh, Hplh, patch_l_h);

    st = calc_high_resolution(patch_r, Wpr, Hpr, factor, &patch_r_h, &Wprh, &Hprh);
    RETURN_IF_ERROR(st);
//    save_bmp_file_mono("patch_h_r.bmp" , Wprh, Hprh, patch_r_h);

    ofstream ofs_cost("cost.csv");
    if(!ofs_cost.is_open())
    {
        PRINT_ERROR("Cannot open file: cost.txt");
        return -1;
    }
    ofs_cost<<"disparity,cost"<<endl;

    int max_disp_f = MAX_DISP*factor;   // Factored max disparity.
    int min_cost_disp_f = 0;    // Factored min cost disparity
    *min_cost = FLT_MAX;
    for(int disp=0; disp<max_disp_f; disp++)
    {
        float cost = 0.0;
        st = compare_patch(patch_l_h, Wplh, Hplh, patch_r_h, Wprh, Hprh,
                           Wprh-Wplh-disp, 0, &cost);
        RETURN_IF_ERROR(st)
        cout<<"disp: "<<(float)disp/factor<<", cost: "<<cost<<endl;
        ofs_cost<<(float)disp/factor<<","<<cost<<endl;
        if(cost < *min_cost)
        {
            *min_cost = cost;
            min_cost_disp_f = disp;
        }
    }
    ofs_cost.close();

    cout<<"min cost:"<<*min_cost<<", disp:"<<(float)min_cost_disp_f/(float)factor<<endl;
    uint8_t *patch_min_cost;
    st = crop_image(patch_r_h, Wprh, Hprh, Wprh-Wplh-min_cost_disp_f, 0, Wplh,
                    Hplh, &patch_min_cost);
    RETURN_IF_ERROR(st);
//    save_bmp_file_mono("patch_min_cost.bmp", Wplh, Hplh, patch_min_cost);

    *min_cost_disp = (float)min_cost_disp_f/(float)factor;

    return 0;
}


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
