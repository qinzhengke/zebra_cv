#include <iostream>

#include "../../src/basic/transform.h"
#include "../../src/basic/bmp.h"


using namespace std;

int print_map_uint8(uint8_t *map, uint32_t W, uint32_t H)
{
    for(int r=0; r<H; r++)
    {
        for(int c=0; c<W; c++)
        {
            cout<<(uint32_t)(map[r*W+c])<<"\t";
        }
        cout<<endl;
    }
    return 0;
}

int main(char argc, char**argv)
{

    int W=6, H=4;
    uint8_t *map0 = new uint8_t[W*H];
    for(int i=0; i<W*H; i++)
    {
        map0[i] = i+1;
    }
    cout<<"map 0:"<<endl;
    print_map_uint8(map0, W, H);

    uint8_t *map1;
    uint32_t W1, H1;
    rotate_right_angle_clockwise(map0, W, H, 1, ROTATE_90, &map1, &W1, &H1);
    cout<<"map 1:"<<endl;
    print_map_uint8(map1, W1, H1);

    uint8_t *map2;
    uint32_t W2, H2;
    rotate_right_angle_clockwise(map0, W, H, 1, ROTATE_180, &map2, &W2, &H2);
    cout<<"map 2:"<<endl;
    print_map_uint8(map2, W2, H2);

    uint8_t *map3;
    uint32_t W3, H3;
    rotate_right_angle_clockwise(map0, W, H, 1, ROTATE_270, &map3, &W3, &H3);
    cout<<"map 3:"<<endl;
    print_map_uint8(map3, W3, H3);

    uint8_t *img0;
    uint32_t Wi0, Hi0;
    read_bmp_file_mono("../../../data/lena.bmp", &Wi0, &Hi0, &img0);

    uint8_t *img1;
    uint32_t Wi1, Hi1;
    rotate_right_angle_clockwise(img0, Wi0, Hi0, 1, ROTATE_90, &img1, &Wi1, &Hi1);
    save_bmp_file_mono("lena_90.bmp", Wi1, Hi1, img1);

    uint8_t *img2;
    uint32_t Wi2, Hi2;
    rotate_right_angle_clockwise(img0, Wi0, Hi0, 1, ROTATE_180, &img2, &Wi2, &Hi2);
    save_bmp_file_mono("lena_180.bmp", Wi2, Hi2, img2);

    uint8_t *img3;
    uint32_t Wi3, Hi3;
    rotate_right_angle_clockwise(img0, Wi0, Hi0, 1, ROTATE_270, &img3, &Wi3, &Hi3);
    save_bmp_file_mono("lena_270.bmp", Wi3, Hi3, img3);

    uint8_t *tulips0;
    uint32_t Wt0, Ht0;
    read_bmp_file_rgb("../../../data/tulips.bmp", &Wt0, &Ht0, &tulips0);

    uint8_t *tulips1;
    uint32_t Wt1, Ht1;
    rotate_right_angle_clockwise(tulips0, Wt0, Ht0, 3, ROTATE_90, &tulips1, &Wt1, &Ht1);
    save_bmp_file_rgb("tulips_90.bmp", Wt1, Ht1, tulips1);

    uint8_t *tulips2;
    uint32_t Wt2, Ht2;
    rotate_right_angle_clockwise(tulips0, Wt0, Ht0, 3, ROTATE_180, &tulips2, &Wt2, &Ht2);
    save_bmp_file_rgb("tulips_180.bmp", Wt2, Ht2, tulips2);

    uint8_t *tulips3;
    uint32_t Wt3, Ht3;
    rotate_right_angle_clockwise(tulips0, Wt0, Ht0, 3, ROTATE_270, &tulips3, &Wt3, &Ht3);
    save_bmp_file_rgb("tulips_270.bmp", Wt3, Ht3, tulips3);

    return 0;
}
