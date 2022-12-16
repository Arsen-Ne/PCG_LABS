#ifndef MODELS_H
#define MODELS_H

#include "colortransform.h"
#include <QString>

// класс хранить цветовые модели,
// предоставляет доступ главной форме к элементам моделей,
// пересчитывает значения моделей
class Models
{
public:
    typedef int(Models::*GetFunc)(void);

    Models();

    // геттеры элементов моделей
    int get_r_rgb();
    int get_g_rgb();
    int get_b_rgb();

    int get_c_cmyk();
    int get_m_cmyk();
    int get_y_cmyk();
    int get_k_cmyk();

    int get_h_hsv();
    int get_s_hsv();
    int get_v_hsv();

    int get_h_hsl();
    int get_s_hsl();
    int get_l_hsl();

    int get_x_xyz();
    int get_y_xyz();
    int get_z_xyz();

    int get_l_lab();
    int get_a_lab();
    int get_b_lab();

    // сеттеры элементов моделей
    void set_r_rgb(int val);
    void set_g_rgb(int val);
    void set_b_rgb(int val);

    void set_c_cmyk(int val);
    void set_m_cmyk(int val);
    void set_y_cmyk(int val);
    void set_k_cmyk(int val);

    void set_h_hsv(int val);
    void set_s_hsv(int val);
    void set_v_hsv(int val);

    void set_h_hsl(int val);
    void set_s_hsl(int val);
    void set_l_hsl(int val);

    void set_x_xyz(int val);
    void set_y_xyz(int val);
    void set_z_xyz(int val);

    void set_l_lab(int val);
    void set_a_lab(int val);
    void set_b_lab(int val);

    bool getClumped() const;

    const QString &getErrors() const;

private:
    RGB rgb;
    CMYK cmyk;
    HSV hsv;
    HSL hsl;
    XYZ xyz;
    LAB lab;

    // функции вызываемые при изменении модели
    // пересчитывают значения остальных моделей
    void rgb_changed();
    void cmyk_changed();
    void hsv_changed();
    void hsl_changed();
    void xyz_changed();
    void lab_changed();

    // фукции ограничивают значения в моделях,
    // а также выставляют флаг ошибки
    void clump_rgb(RGB& rgb);
    void clump_cmyk(CMYK& cmyk);
    void clump_hsv(HSV& hsv);
    void clump_hsl(HSL& hsl);
    void clump_xyz(XYZ& xyz);
    void clump_lab(LAB& lab);

    bool clumped;
    QString errors = "";
};

#endif // MODELS_H
