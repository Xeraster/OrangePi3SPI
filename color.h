#ifndef COLOR_H
#define COLOR_H

//a basic color struct, not to be confused with the color class I usually use, this is a 16 bit version for this project specifically.
struct color
{
    color(int r, int g, int b)
    {
        if (r > 31)
        {
            red = 31;
        }
        else
        {
            red = r;
        }

        if (g > 63)
        {
            green = 63;
        }
        else
        {
            green = g;
        }

        if (b > 31)
        {
            blue = 31;
        }
        else
        {
            blue = r;
        }
    }

    unsigned int blue;
    unsigned int green;
    unsigned int red;
};

#endif