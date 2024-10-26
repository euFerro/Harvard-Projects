#include "ColorListRGB.h"

//https://community.khronos.org/t/color-tables/22518/5

int colorCount = 0;

float Colors[][3] = {
    1,0,0,
    0,1,0,
    0,0,1,
    1,0,1,
    1,1,0,
    0,1,1,
    1.0, 0.2, 0.0,
    1.0, 0.5, 0.5,
    0.5, 1.0, 1.0,
    0.5, 1.0, 0.5,
    1.0, 1.0, 1.0,
    0.8, 0.8, 0.8
};

void defineColor(int c)
{
   // glColor3fv(Colors[c]);
    glColor3f(Colors[c][0], Colors[c][1], Colors[c][2]);
}

int nextColor()
{
    if (colorCount > 5)
    {
        colorCount = 0;
    }
    int temp = colorCount;
    colorCount++;
    return temp;
}
