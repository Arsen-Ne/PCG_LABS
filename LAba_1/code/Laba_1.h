#ifndef COLORSTRUCTS_H
#define COLORSTRUCTS_H

// структуры представляющие цветовые модели

struct RGB
{
    double r;
    double g;
    double b;
};

struct CMYK
{
    double c;
    double m;
    double y;
    double k;
};

struct HSV
{
    double h;
    double s;
    double v;
};

struct HSL
{
    double h;
    double s;
    double l;
};

struct XYZ
{
    double x;
    double y;
    double z;
};

struct LAB
{
    double l;
    double a;
    double b;
};

#endif // COLORSTRUCTS_H
