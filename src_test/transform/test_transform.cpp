#include <iostream>

#include "../../src/basic/transform.h"

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

    return 0;
}
