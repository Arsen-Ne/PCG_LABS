#ifndef COLORTRANSFORM_H
#define COLORTRANSFORM_H

#include "ColorStructs.h"

// Класс содерим функции для конвертации моделей
// модели переводятся в XYZ и обратно

class ColorTransform
{
public:
    static XYZ RGB_to_XYZ(RGB rgb);
    static XYZ CMYK_to_XYZ(CMYK cmyk);
    static XYZ HSV_to_XYZ(HSV hsv);
    static XYZ HSL_to_XYZ(HSL hsl);
    static XYZ LAB_to_XYZ(LAB lab);

    static RGB XYZ_to_RGB(XYZ xyz);
    static CMYK XYZ_to_CMYK(XYZ xyz);
    static HSV XYZ_to_HSV(XYZ xyz);
    static HSL XYZ_to_HSL(XYZ xyz);
    static LAB XYZ_to_LAB(XYZ xyz);

private:
    static double rgb_value_to_rgbn_value(double x);
    static double rgbn_value_to_rgb_value(double x);
    static void rgb_to_rgbn(const RGB& rgb, RGB& rgbn);
    static void rgbn_to_rgb(const RGB& rgbn, RGB& rgb);
    static RGB hsv_to_rgb(HSV in);
    static HSV rgb_to_hsv(RGB in);
    static RGB hsl_to_rgb(HSL in);
    static HSL rgb_to_hsl(RGB in);
    static double xyz_value_to_lab_value(double x);
    static double lab_value_to_xyz_value(double x);
};

#endif // COLORTRANSFORM_H
