#include <iostream>
#include <fstream>

using namespace std;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;

int cvt2color(float *img, uint32_t W, uint32_t H, uint8_t **img_out)
{
    const int32_t N = 500;
    uint8_t color_map[N][3];
    float r = 0.4;
    int32_t s1=(int32_t)((float)N*r), s2 = N/2, s3=(int32_t)((float)N*(1.0-r));
    float k1,k2,k3,k4;
    k1 = 255.0 / r /(float)N;
    k2 = -255.0/(0.5-r)/(float)N;
    k3 = 255.0/(0.5-r)/(float)N;
    k4 = -255.0 / r /(float)N;
    for(int32_t i=0; i<N; i++)
    {
        if(i<s1)
        {
            color_map[i][0] = 255;
            float pix = k1 *(float)i;
            if(pix<0.0) pix = 0.0;
            else if(pix>255.0) pix = 255.0;
            color_map[i][1] = (uint8_t)(pix);
            color_map[i][2] = 0;
        }
        else if(i<s2)
        {
            float pix = k2*(float)(i-s2);
            if(pix<0.0) pix = 0.0;
            else if(pix>255.0) pix = 255.0;
            color_map[i][0] = (uint8_t)(pix);
            color_map[i][1] = 255;
            color_map[i][2] = 0;
        }
        else if(i<s3)
        {
            color_map[i][0] = 0;
            color_map[i][1] = 255;
            float pix = k3*(float)(i-s2);
            if(pix<0.0) pix = 0.0;
            else if(pix>255.0) pix = 255.0;
            color_map[i][2] = (uint8_t)(pix);
        }
        else
        {
            color_map[i][0] = 0;
            float pix = k4 *(float)(i-N);
            if(pix<0.0) pix = 0.0;
            else if(pix>255.0) pix = 255.0;
            color_map[i][1] =  (uint8_t)(pix);
            color_map[i][2] = 255;
        }
    }

    *img_out = new uint8_t[3*W*H];
    for(uint32_t r=0; r<H; r++)
        for(uint32_t c=0; c<W; c++)
        {
            int32_t loc = (int32_t)img[r*W+c] + N/2;
            for(int k=0; k<3; k++)
            {
                if(loc < 0)
                    loc = 0;
                else if(loc > N-1)
                    loc = N-1;
                (*img_out)[r*3*W+3*c+k] = color_map[(uint32_t)loc][k];
            }
        }

    return 0;
}

int main(char argc, char** argv)
{
    uint32_t W=400,H=50;
    float *img = new float[W*H];
    for(uint32_t r=0; r< H; r++)
        for(uint32_t c=0; c<W; c++)
            img[r*W+c] = 1.3*((float)c-200.0);

    uint8_t *img_color;
    cvt2color(img, W, H, &img_color);

    ofstream f;
    f.open("out.bin3", ios::binary);
    f.write((const char*)&W, sizeof(uint32_t));
    f.write((const char*)&H, sizeof(uint32_t));
    f.write((const char*)img_color, W*H*3);
    f.close();
    delete img_color;
    cout<<"done!"<<endl;
    return 0;
}
