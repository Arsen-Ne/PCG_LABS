#include "models.h"

Models::Models()
{
    set_r_rgb(0);
    set_g_rgb(0);
    set_b_rgb(0);

    set_c_cmyk(0);
    set_m_cmyk(0);
    set_y_cmyk(0);
    set_k_cmyk(0);

    set_h_hsv(0);
    set_s_hsv(0);
    set_v_hsv(0);

    set_h_hsl(0);
    set_s_hsl(0);
    set_l_hsl(0);

    set_x_xyz(0);
    set_y_xyz(0);
    set_z_xyz(0);

    set_l_lab(0);
    set_a_lab(0);
    set_b_lab(0);

    rgb_changed();
    cmyk_changed();
    hsv_changed();
    hsl_changed();
    xyz_changed();
    lab_changed();

    clumped = false;
}

int Models::get_r_rgb()
{
    return rgb.r;
}

int Models::get_g_rgb()
{
     return rgb.g;
}

int Models::get_b_rgb()
{
     return rgb.b;
}

int Models::get_c_cmyk()
{
     return cmyk.c;
}

int Models::get_m_cmyk()
{
    return cmyk.m;
}

int Models::get_y_cmyk()
{
    return cmyk.y;
}

int Models::get_k_cmyk()
{
    return cmyk.k;
}

int Models::get_h_hsv()
{
    return hsv.h;
}

int Models::get_s_hsv()
{
    return hsv.s;
}

int Models::get_v_hsv()
{
    return hsv.v;
}

int Models::get_h_hsl()
{
    return hsl.h;
}

int Models::get_s_hsl()
{
    return hsl.s;
}

int Models::get_l_hsl()
{
    return hsl.l;
}

int Models::get_x_xyz()
{
    return xyz.x;
}

int Models::get_y_xyz()
{
    return xyz.y;
}

int Models::get_z_xyz()
{
    return xyz.z;
}

int Models::get_l_lab()
{
    return lab.l;
}

int Models::get_a_lab()
{
    return lab.a;
}

int Models::get_b_lab()
{
    return lab.b;
}

void Models::set_r_rgb(int val)
{
    rgb.r = val;
    rgb_changed();
}

void Models::set_g_rgb(int val)
{
    rgb.g = val;
    rgb_changed();
}

void Models::set_b_rgb(int val)
{
    rgb.b = val;
    rgb_changed();
}

void Models::set_c_cmyk(int val)
{
    cmyk.c = val;
    cmyk_changed();
}

void Models::set_m_cmyk(int val)
{
    cmyk.m = val;
    cmyk_changed();
}

void Models::set_y_cmyk(int val)
{
    cmyk.y = val;
    cmyk_changed();
}

void Models::set_k_cmyk(int val)
{
    cmyk.k = val;
    cmyk_changed();
}

void Models::set_h_hsv(int val)
{
    hsv.h = val;
    hsv_changed();
}

void Models::set_s_hsv(int val)
{
    hsv.s = val;
    hsv_changed();
}

void Models::set_v_hsv(int val)
{
    hsv.v = val;
    hsv_changed();
}

void Models::set_h_hsl(int val)
{
    hsl.h = val;
    hsl_changed();
}

void Models::set_s_hsl(int val)
{
    hsl.s = val;
    hsl_changed();
}

void Models::set_l_hsl(int val)
{
    hsl.l = val;
    hsl_changed();
}

void Models::set_x_xyz(int val)
{
    xyz.x = val;
    xyz_changed();
}

void Models::set_y_xyz(int val)
{
    xyz.y = val;
    xyz_changed();
}

void Models::set_z_xyz(int val)
{
    xyz.z = val;
    xyz_changed();
}

void Models::set_l_lab(int val)
{
    lab.l = val;
    lab_changed();
}

void Models::set_a_lab(int val)
{
    lab.a = val;
    lab_changed();
}

void Models::set_b_lab(int val)
{
    lab.b = val;
    lab_changed();
}

void Models::rgb_changed()
{
    xyz = ColorTransform::RGB_to_XYZ(rgb);
    clump_xyz(xyz);
    cmyk = ColorTransform::XYZ_to_CMYK(xyz);
    clump_cmyk(cmyk);
    hsv = ColorTransform::XYZ_to_HSV(xyz);
    clump_hsv(hsv);
    hsl = ColorTransform::XYZ_to_HSL(xyz);
    clump_hsl(hsl);
    lab = ColorTransform::XYZ_to_LAB(xyz);
    clump_lab(lab);
}

void Models::cmyk_changed()
{
    xyz = ColorTransform::CMYK_to_XYZ(cmyk);
    clump_xyz(xyz);
    rgb = ColorTransform::XYZ_to_RGB(xyz);
    clump_rgb(rgb);
    hsv = ColorTransform::XYZ_to_HSV(xyz);
    clump_hsv(hsv);
    hsl = ColorTransform::XYZ_to_HSL(xyz);
    clump_hsl(hsl);
    lab = ColorTransform::XYZ_to_LAB(xyz);
    clump_lab(lab);
}

void Models::hsv_changed()
{
    xyz = ColorTransform::HSV_to_XYZ(hsv);
    clump_xyz(xyz);
    rgb = ColorTransform::XYZ_to_RGB(xyz);
    clump_rgb(rgb);
    cmyk = ColorTransform::XYZ_to_CMYK(xyz);
    clump_cmyk(cmyk);
    hsl = ColorTransform::XYZ_to_HSL(xyz);
    clump_hsl(hsl);
    lab = ColorTransform::XYZ_to_LAB(xyz);
    clump_lab(lab);
}

void Models::hsl_changed()
{
    xyz = ColorTransform::HSL_to_XYZ(hsl);
    clump_xyz(xyz);
    rgb = ColorTransform::XYZ_to_RGB(xyz);
    clump_rgb(rgb);
    cmyk = ColorTransform::XYZ_to_CMYK(xyz);
    clump_cmyk(cmyk);
    hsv = ColorTransform::XYZ_to_HSV(xyz);
    clump_hsv(hsv);
    lab = ColorTransform::XYZ_to_LAB(xyz);
    clump_lab(lab);
}

void Models::xyz_changed()
{
    rgb = ColorTransform::XYZ_to_RGB(xyz);
    clump_rgb(rgb);
    cmyk = ColorTransform::XYZ_to_CMYK(xyz);
    clump_cmyk(cmyk);
    hsv = ColorTransform::XYZ_to_HSV(xyz);
    clump_hsv(hsv);
    hsl = ColorTransform::XYZ_to_HSL(xyz);
    clump_hsl(hsl);
    lab = ColorTransform::XYZ_to_LAB(xyz);
    clump_lab(lab);
}

void Models::lab_changed()
{
    xyz = ColorTransform::LAB_to_XYZ(lab);
    clump_xyz(xyz);
    rgb = ColorTransform::XYZ_to_RGB(xyz);
    clump_rgb(rgb);
    cmyk = ColorTransform::XYZ_to_CMYK(xyz);
    clump_cmyk(cmyk);
    hsv = ColorTransform::XYZ_to_HSV(xyz);
    clump_hsv(hsv);
    hsl = ColorTransform::XYZ_to_HSL(xyz);
    clump_hsl(hsl);
}

void Models::clump_rgb(RGB &rgb)
{
    bool changed = false;
    errors = "";
    if(rgb.r < 0){
        rgb.r = 0;
        changed = true;
    }

    if(rgb.g < 0){
        rgb.g = 0;
        changed = true;
    }

    if(rgb.b < 0){
        rgb.b = 0;
        changed = true;
    }

    if(rgb.r > 255){
        rgb.r = 255;
        changed = true;
    }

    if(rgb.g > 255){
        rgb.g = 255;
        changed = true;
    }

    if(rgb.b > 255){
        rgb.b = 255;
        changed = true;
    }

    clumped = changed;
    if(clumped){
        if(errors != ""){
            errors += "\n";
        }
        errors += "Ограничены цвета в модели rgb";
    }
}

void Models::clump_cmyk(CMYK &cmyk)
{
    bool changed = false;
    errors = "";
    if(cmyk.c < 0){
        cmyk.c = 0;
        changed = true;
    }

    if(cmyk.m < 0){
        cmyk.m = 0;
        changed = true;
    }

    if(cmyk.y < 0){
        cmyk.y = 0;
        changed = true;
    }

    if(cmyk.k < 0){
        cmyk.k = 0;
        changed = true;
    }

    if(cmyk.c > 100){
        cmyk.c = 100;
        changed = true;
    }

    if(cmyk.m > 100){
        cmyk.m = 100;
        changed = true;
    }

    if(cmyk.y > 100){
        cmyk.y = 100;
        changed = true;
    }

    if(cmyk.k > 100){
        cmyk.k = 100;
        changed = true;
    }

    clumped = changed;
    if(clumped){
        if(errors != ""){
            errors += "\n";
        }
        errors += "Ограничены цвета в модели cmyk";
    }
}

void Models::clump_hsv(HSV &hsv)
{
    bool changed = false;
    errors = "";
    if(hsv.h < 0){
        hsv.h = 0;
        changed = true;
    }

    if(hsv.s < 0){
        hsv.s = 0;
        changed = true;
    }

    if(hsv.v < 0){
        hsv.v = 0;
        changed = true;
    }

    if(hsv.h > 360){
        hsv.h = 360;
        changed = true;
    }

    if(hsv.s > 100){
        hsv.s = 100;
        changed = true;
    }

    if(hsv.v > 100){
        hsv.v = 100;
        changed = true;
    }

    clumped = changed;
    if(clumped){
        if(errors != ""){
            errors += "\n";
        }
        errors += "Ограничены цвета в модели hsv";
    }
}

void Models::clump_hsl(HSL &hsl)
{
    bool changed = false;
    errors = "";
    if(hsl.h < 0){
        hsl.h = 0;
        changed = true;
    }

    if(hsl.s < 0){
        hsl.s = 0;
        changed = true;
    }

    if(hsl.l < 0){
        hsl.l = 0;
        changed = true;
    }

    if(hsl.h > 360){
        hsl.h = 360;
        changed = true;
    }

    if(hsl.s > 100){
        hsl.s = 100;
        changed = true;
    }

    if(hsl.l > 100){
        hsl.l = 100;
        changed = true;
    }

    clumped = changed;
    if(clumped){
        if(errors != ""){
            errors += "\n";
        }
        errors += "Ограничены цвета в модели hsl";
    }
}

void Models::clump_xyz(XYZ &xyz)
{
    bool changed = false;
    errors = "";
    if(xyz.x < 0){
        xyz.x = 0;
        changed = true;
    }

    if(xyz.y < 0){
        xyz.y = 0;
        changed = true;
    }

    if(xyz.z < 0){
        xyz.z = 0;
        changed = true;
    }

    if(xyz.x > 95){
        xyz.x = 95;
        changed = true;
    }

    if(xyz.y > 100){
        xyz.y = 100;
        changed = true;
    }

    if(xyz.z > 108){
        xyz.z = 108;
        changed = true;
    }

    clumped = changed;
    if(clumped){
        if(errors != ""){
            errors += "\n";
        }
        errors += "Ограничены цвета в модели xyz";
    }
}

void Models::clump_lab(LAB &lab)
{
    bool changed = false;
    errors = "";
    if(lab.l < -20){
        lab.l = 20;
        changed = true;
    }

    if(lab.a < -128){
        lab.a = -128;
        changed = true;
    }

    if(lab.b < -128){
        lab.b = -128;
        changed = true;
    }

    if(lab.l > 100){
        lab.l = 100;
        changed = true;
    }

    if(lab.a > 128){
        lab.a = 128;
        changed = true;
    }

    if(lab.b > 128){
        lab.b = 128;
        changed = true;
    }

    clumped = changed;
    if(clumped){
        if(errors != ""){
            errors += "\n";
        }
        errors += "Ограничены цвета в модели lab";
    }
}

const QString &Models::getErrors() const
{
    return errors;
}

bool Models::getClumped() const
{
    return clumped;
}


