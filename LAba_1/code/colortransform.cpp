#include "colortransform.h"
#include <cmath>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

double smallest(double x, double y, double z){
    return MIN(MIN(x, y), z);
}

XYZ ColorTransform::RGB_to_XYZ(RGB rgb)
{
    RGB rgbn;
    rgb_to_rgbn(rgb, rgbn);
    return {
        0.412453 * rgbn.r + 0.357580 * rgbn.g + 0.180423 * rgbn.b,
        0.212671 * rgbn.r + 0.715160 * rgbn.g + 0.072169 * rgbn.b,
        0.019334 * rgbn.r + 0.119193 * rgbn.g + 0.950227 * rgbn.b
    };
}

XYZ ColorTransform::CMYK_to_XYZ(CMYK cmyk)
{
    RGB rgb;
    rgb.r = 255 * (1 - cmyk.c / 100) * (1 - cmyk.k / 100);
    rgb.g = 255 * (1 - cmyk.m / 100) * (1 - cmyk.k / 100);
    rgb.b = 255 * (1 - cmyk.y / 100) * (1 - cmyk.k / 100);
    return RGB_to_XYZ(rgb);
}

XYZ ColorTransform::HSV_to_XYZ(HSV hsv)
{
    RGB rgb = hsv_to_rgb(hsv);
    return RGB_to_XYZ(rgb);
}

XYZ ColorTransform::HSL_to_XYZ(HSL hls)
{
    RGB rgb = hsl_to_rgb(hls);
    return RGB_to_XYZ(rgb);
}

XYZ ColorTransform::LAB_to_XYZ(LAB lab)
{
    XYZ xyz;
    xyz.x = lab_value_to_xyz_value(lab.a / 500 + (lab.l + 16) / 116)  * 100;
    xyz.y = lab_value_to_xyz_value((lab.l + 16) / 116)  * 95.047;
    xyz.z = lab_value_to_xyz_value((lab.l + 16) / 116 - lab.b / 200)  * 108.883;
    return xyz;
}

RGB ColorTransform::XYZ_to_RGB(XYZ xyz)
{
    RGB rgbn;
    rgbn.r = 3.2406 * xyz.x / 100 - 1.5372 * xyz.y / 100 - 0.4986 * xyz.z / 100;
    rgbn.g = -0.9689 * xyz.x / 100 + 1.8758 * xyz.y / 100 + 0.0415 * xyz.z / 100;
    rgbn.b = 0.0557 * xyz.x / 100 - 0.2040 * xyz.y / 100 + 1.0570 * xyz.z / 100;
    RGB rgb;
    rgbn_to_rgb(rgbn, rgb);
    return { round(rgb.r), round(rgb.g), round(rgb.b) };
}

CMYK ColorTransform::XYZ_to_CMYK(XYZ xyz)
{
    RGB rgb = XYZ_to_RGB(xyz);
    CMYK cmyk;
    cmyk.k = smallest(1 - rgb.r / 255.0, 1 - rgb.g / 255.0, 1 - rgb.b / 255.0);
    cmyk.c = cmyk.k != 1 ? (1 - rgb.r / 255 - cmyk.k) / (1 - cmyk.k) : 0;
    cmyk.m = cmyk.k != 1 ? (1 - rgb.g / 255 - cmyk.k) / (1 - cmyk.k) : 0;
    cmyk.y = cmyk.k != 1 ? (1 - rgb.b / 255 - cmyk.k) / (1 - cmyk.k) : 0;
    return {
        cmyk.c * 100,
        cmyk.m * 100,
        cmyk.y * 100,
        cmyk.k * 100
    };
}

HSV ColorTransform::XYZ_to_HSV(XYZ xyz)
{
    RGB rgb = XYZ_to_RGB(xyz);
    return rgb_to_hsv(rgb);
}

HSL ColorTransform::XYZ_to_HSL(XYZ xyz)
{
    RGB rgb = XYZ_to_RGB(xyz);
    return rgb_to_hsl(rgb);
}

LAB ColorTransform::XYZ_to_LAB(XYZ xyz)
{
    LAB lab;
    lab.l = 116 * xyz_value_to_lab_value(xyz.y / 100) - 16;
    lab.a = 500 * (xyz_value_to_lab_value(xyz.x / 95.047) - xyz_value_to_lab_value(xyz.y / 100));
    lab.b = 200 * (xyz_value_to_lab_value(xyz.y /100) - xyz_value_to_lab_value(xyz.z / 108.883));
    return lab;
}

double ColorTransform::rgb_value_to_rgbn_value(double x)
{
   if(x >= 0.04045) {
       return pow((x + 0.055)/1.055, 2.4);
   }else{
       return x / 12.92;
   }
}

double ColorTransform::rgbn_value_to_rgb_value(double x)
{
    if(x >= 0.0031308) {
        return 1.055 * pow(x, 1/2.4) - 0.055;
    }else{
        return x * 12.92;
    }
}

void ColorTransform::rgb_to_rgbn(const RGB &rgb, RGB &rgbn)
{
    rgbn.r = rgb_value_to_rgbn_value(rgb.r / 255) * 100;
    rgbn.g = rgb_value_to_rgbn_value(rgb.g / 255) * 100;
    rgbn.b = rgb_value_to_rgbn_value(rgb.b / 255) * 100;
}

void ColorTransform::rgbn_to_rgb(const RGB &rgbn, RGB &rgb)
{
    rgb.r = rgbn_value_to_rgb_value(rgbn.r) * 255;
    rgb.b = rgbn_value_to_rgb_value(rgbn.b) * 255;
    rgb.g = rgbn_value_to_rgb_value(rgbn.g) * 255;
}

RGB ColorTransform::hsv_to_rgb(HSV in)
{
    double      hh, p, q, t, ff;
    long        i;
    RGB         out;

    in.s /= 100;
    in.v /= 100;

    if(in.s <= 0.0) {
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }

    out.r *= 255;
    out.g *= 255;
    out.b *= 255;
    return out;
}

HSV ColorTransform::rgb_to_hsv(RGB in)
{
    HSV         out;
    double      min, max, delta;

    in.r /= 255;
    in.g /= 255;
    in.b /= 255;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0;
        return out;
    }
    if( max > 0.0 ) {
        out.s = (delta / max);
    } else {
        out.s = 0.0;
        out.h = NAN;
        return out;
    }
    if( in.r >= max )
        out.h = ( in.g - in.b ) / delta;
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;

    out.h *= 60.0;

    if( out.h < 0.0 )
        out.h += 360.0;

    out.s *= 100;
    out.v *= 100;
    return out;
}

float hue2rgb(float p, float q, float t) {

  if (t < 0)
    t += 1;
  if (t > 1)
    t -= 1;
  if (t < 1./6)
    return p + (q - p) * 6 * t;
  if (t < 1./2)
    return q;
  if (t < 2./3)
    return p + (q - p) * (2./3 - t) * 6;

  return p;

}

RGB ColorTransform::hsl_to_rgb(HSL in)
{
    float h = in.h / 360, s = in.s / 100, l = in.l / 100;
    RGB result;

  if(0 == s) {
    result.r = result.g = result.b = l; // achromatic
  }
  else {
    float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    float p = 2 * l - q;
    result.r = hue2rgb(p, q, h + 1./3) * 255;
    result.g = hue2rgb(p, q, h) * 255;
    result.b = hue2rgb(p, q, h - 1./3) * 255;
  }

  return result;
}

HSL ColorTransform::rgb_to_hsl(RGB in)
{
      HSL result;

      float r = in.r, g = in.g, b = in.b;

      r /= 255;
      g /= 255;
      b /= 255;

      float max = MAX(MAX(r,g),b);
      float min = MIN(MIN(r,g),b);

      result.h = result.s = result.l = (max + min) / 2;

      if (max == min) {
        result.h = result.s = 0; // achromatic
      }
      else {
        float d = max - min;
        result.s = (result.l > 0.5) ? d / (2 - max - min) : d / (max + min);

        if (max == r) {
          result.h = (g - b) / d + (g < b ? 6 : 0);
        }
        else if (max == g) {
          result.h = (b - r) / d + 2;
        }
        else if (max == b) {
          result.h = (r - g) / d + 4;
        }

        result.h /= 6;
      }

      result.h *= 360;
      result.s *= 100;
      result.l *= 100;
      return result;
}

double ColorTransform::xyz_value_to_lab_value(double x)
{
    if(x >= 0.008856){
        return pow(x, 1/3);
    }else{
        return 7.787 * x + 16 / 116;
    }
}

double ColorTransform::lab_value_to_xyz_value(double x)
{
    if(x >= 0.008856){
        return pow(x, 3);
    }else{
        return (x - 16 / 116) / 7.787;
    }
}
