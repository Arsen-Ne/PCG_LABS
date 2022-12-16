#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "models.h"
#include "palette.h"
#include <QMainWindow>
#include <QMap>
#include <QSpinBox>
#include <QtUiTools>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void r_rgb_spin_valueChanged(int arg1);

    void g_rgb_spin_valueChanged(int arg1);

    void b_rgb_spin_valueChanged(int arg1);

    void l_lab_spin_valueChanged(int arg1);

    void a_lab_spin_valueChanged(int arg1);

    void b_lab_spin_valueChanged(int arg1);

    void c_cmyk_spin_valueChanged(int arg1);

    void m_cmyk_spin_valueChanged(int arg1);

    void y_cmyk_spin_valueChanged(int arg1);

    void k_cmyk_spin_valueChanged(int arg1);

    void h_hsl_spin_valueChanged(int arg1);

    void s_hsl_spin_valueChanged(int arg1);

    void l_hsl_spin_valueChanged(int arg1);

    void h_hsv_spin_valueChanged(int arg1);

    void s_hsv_spin_valueChanged(int arg1);

    void v_hsv_spin_valueChanged(int arg1);

    void x_xyz_spin_valueChanged(int arg1);

    void y_xyz_spin_valueChanged(int arg1);

    void z_xyz_spin_valueChanged(int arg1);

    void r_rgb_slider_valueChanged(int value);

    void g_rgb_slider_valueChanged(int value);

    void b_rgb_slider_valueChanged(int value);

    void l_lab_slider_valueChanged(int value);

    void a_lab_slider_valueChanged(int value);

    void b_lab_slider_valueChanged(int value);

    void c_cmyk_slider_valueChanged(int value);

    void m_cmyk_slider_valueChanged(int value);

    void y_cmyk_slider_valueChanged(int value);

    void k_cmyk_slider_valueChanged(int value);

    void h_hsl_slider_valueChanged(int value);

    void s_hsl_slider_valueChanged(int value);

    void l_hsl_slider_valueChanged(int value);

    void h_hsv_slider_valueChanged(int value);

    void s_hsv_slider_valueChanged(int value);

    void v_hsv_slider_valueChanged(int value);

    void x_xyz_slider_valueChanged(int value);

    void y_xyz_slider_valueChanged(int value);

    void z_xyz_slider_valueChanged(int value);

    void on_comboBox_currentIndexChanged(int index);

public slots:
    void color_selected(QColor color);

private:
    Ui::MainWindow *ui;
    Models* models;

    QMap<QString, Models::GetFunc> map;

    void update_values(QString widget_name);

    bool  in_change = false;

    void update_color();

    QWidget *loadUiFile(QWidget *parent, QString uiname);

    void load_rgb_lab_cmyk();

    void load_rgb_cmyk_hls();

    void load_rgb_xyz_lab();

    void load_rgb_hsv_lab();

    void load_cmyk_lab_hsv();

    void load_cmyk_rgb_hls();

    void load_cmyk_rgb_hsv();

    void load_rgb_xyz_hsv();

    void load_hsv_xyz_lab();

    void load_cmyk_lab_rgb();

    void load_xyz_lab_hls();

    void load_rgb_xyz_hls();

    void load_rgb_xyz_cmyk();

    void load_cmyk_lab_xyz();

    void load_rgb_cmyk_hsv();

    void load_cmyk_hls_xyz();

    void load_rgb_hls_lab();

    void load_cmyk_xyz_rgb();

    void connect_rgb_widget();

    void connect_lab_widget();

    void connect_cmyk_widget();

    void connect_hsl_widget();

    void connect_hsv_widget();

    void connect_xyz_widget();

    void show_widget(int f, int s, int t);

    QWidget* _widgetOnTheTop;
};
#endif // MAINWINDOW_H
