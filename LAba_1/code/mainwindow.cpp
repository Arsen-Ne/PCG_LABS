#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    models = new Models;

    QString layers[] = {
        "RGB ↔ LAB ↔ CMYK",
        "RGB ↔ CMYK ↔ HLS",
        "RGB ↔ XYZ ↔ LAB",
        "RGB ↔ HSV ↔ LAB",
        "CMYK ↔ LAB ↔ HSV",
        "CMYK ↔ RGB ↔ HLS",
        "CMYK ↔ RGB ↔ HSV",
        "RGB ↔ XYZ ↔ HSV",
        "HSV ↔ XYZ ↔ LAB",
        "CMYK ↔ LAB ↔ RGB",
        "XYZ ↔ LAB ↔ HLS",
        "RGB ↔ XYZ ↔ HLS",
        "RGB ↔ XYZ ↔ CMYK",
        "CMYK ↔ LAB ↔ XYZ",
        "RGB ↔ CMYK ↔ HSV",
        "CMYK ↔ HLS ↔ XYZ",
        "RGB ↔ HLS ↔ LAB",
        "CMYK ↔ XYZ ↔ RGB",
    };

    for(int i = 0; i < 18; i++)
    {
        ui->comboBox->addItem(layers[i]);
    }

    connect_rgb_widget();
    connect_lab_widget();
    connect_cmyk_widget();
    connect_hsl_widget();
    connect_hsv_widget();
    connect_xyz_widget();

    if(!in_change)
    {
        in_change = true;
        update_values("");
        in_change = false;
        update_color();
    }

    _widgetOnTheTop = new QPushButton(this);
    QPoint pos = ui->colorPicker->getPos();
    _widgetOnTheTop->setGeometry(pos.x(), pos.y(), 2, 2);

    connect(ui->colorPicker, SIGNAL(clickedColor(QColor)), this, SLOT(color_selected(QColor)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_values(QString widget_name)
{
    QMap<QString, Models::GetFunc>::const_iterator i = map.constBegin();
    while (i != map.constEnd())
    {
        QString w_name = i.key();
        if(w_name != widget_name)
        {
            if(w_name.contains("spin"))
            {
                QSpinBox* spin = ui->centralwidget->findChild<QSpinBox*>(w_name);
                spin->setValue((models->*i.value())());
            }
            else if(w_name.contains("slider"))
            {
                QSlider* slider = ui->centralwidget->findChild<QSlider*>(w_name);
                slider->setValue((models->*i.value())());
            }
        }
        ++i;
    }
}

QString decToHexa(int n)
{
    char hexaDeciNum[2];

    int i = 0;
    while (n != 0) {
         int temp = 0;
         temp = n % 16;
         if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        n = n / 16;
    }

    QString hexCode = "";
    if (i == 2) {
        hexCode.push_back(hexaDeciNum[0]);
        hexCode.push_back(hexaDeciNum[1]);
    }
    else if (i == 1) {
        hexCode = "0";
        hexCode.push_back(hexaDeciNum[0]);
    }
    else if (i == 0)
        hexCode = "00";
    return hexCode;
}

QString convertRGBtoHex(int R, int G, int B)
{
    if ((R >= 0 && R <= 255)
        && (G >= 0 && G <= 255)
        && (B >= 0 && B <= 255)) {

        QString hexCode = "#";
        hexCode += decToHexa(R);
        hexCode += decToHexa(G);
        hexCode += decToHexa(B);

        return hexCode;
    }

    else
        return "-1";
}

void MainWindow::update_color()
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(models->get_r_rgb(), models->get_g_rgb(), models->get_b_rgb()));
    ui->selectedColor->setPalette(pal);

    ui->selectedColorHex->setText(convertRGBtoHex(models->get_r_rgb(), models->get_g_rgb(), models->get_b_rgb()));

    if(models->getClumped())
        ui->logTextEdit->setPlainText(models->getErrors());
    else
        ui->logTextEdit->setPlainText("");
}

QWidget *MainWindow::loadUiFile(QWidget *parent, QString uiname)
{
    QFile file(":/forms/" + uiname);
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    return loader.load(&file, parent);
}

void MainWindow::connect_rgb_widget()
{
    QSpinBox* r_rgb_spin = ui->centralwidget->findChild<QSpinBox*>("r_rgb_spin");
    QSpinBox* g_rgb_spin = ui->centralwidget->findChild<QSpinBox*>("g_rgb_spin");
    QSpinBox* b_rgb_spin = ui->centralwidget->findChild<QSpinBox*>("b_rgb_spin");

    connect(r_rgb_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(r_rgb_spin_valueChanged(int)));
    connect(g_rgb_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(g_rgb_spin_valueChanged(int)));
    connect(b_rgb_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(b_rgb_spin_valueChanged(int)));

    map[r_rgb_spin->objectName()] = &Models::get_r_rgb;
    map[g_rgb_spin->objectName()] = &Models::get_g_rgb;
    map[b_rgb_spin->objectName()] = &Models::get_b_rgb;

    QSlider* r_rgb_slider = ui->centralwidget->findChild<QSlider*>("r_rgb_slider");
    QSlider* g_rgb_slider = ui->centralwidget->findChild<QSlider*>("g_rgb_slider");
    QSlider* b_rgb_slider = ui->centralwidget->findChild<QSlider*>("b_rgb_slider");

    connect(r_rgb_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(r_rgb_slider_valueChanged(int)));
    connect(g_rgb_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(g_rgb_slider_valueChanged(int)));
    connect(b_rgb_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(b_rgb_slider_valueChanged(int)));

    map[r_rgb_slider->objectName()] = &Models::get_r_rgb;
    map[g_rgb_slider->objectName()] = &Models::get_g_rgb;
    map[b_rgb_slider->objectName()] = &Models::get_b_rgb;
}

void MainWindow::connect_lab_widget()
{
    QSpinBox* l_lab_spin = ui->centralwidget->findChild<QSpinBox*>("l_lab_spin");
    QSpinBox* a_lab_spin = ui->centralwidget->findChild<QSpinBox*>("a_lab_spin");
    QSpinBox* b_lab_spin = ui->centralwidget->findChild<QSpinBox*>("b_lab_spin");

    connect(l_lab_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(l_lab_spin_valueChanged(int)));
    connect(a_lab_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(a_lab_spin_valueChanged(int)));
    connect(b_lab_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(b_lab_spin_valueChanged(int)));

    map[l_lab_spin->objectName()] = &Models::get_l_lab;
    map[a_lab_spin->objectName()] = &Models::get_a_lab;
    map[b_lab_spin->objectName()] = &Models::get_b_lab;

    QSlider* l_lab_slider = ui->centralwidget->findChild<QSlider*>("l_lab_slider");
    QSlider* a_lab_slider = ui->centralwidget->findChild<QSlider*>("a_lab_slider");
    QSlider* b_lab_slider = ui->centralwidget->findChild<QSlider*>("b_lab_slider");

    connect(l_lab_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(l_lab_slider_valueChanged(int)));
    connect(a_lab_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(a_lab_slider_valueChanged(int)));
    connect(b_lab_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(b_lab_slider_valueChanged(int)));

    map[l_lab_slider->objectName()] = &Models::get_l_lab;
    map[a_lab_slider->objectName()] = &Models::get_a_lab;
    map[b_lab_slider->objectName()] = &Models::get_b_lab;
}

void MainWindow::connect_cmyk_widget()
{
    QSpinBox* c_cmyk_spin = ui->centralwidget->findChild<QSpinBox*>("c_cmyk_spin");
    QSpinBox* m_cmyk_spin = ui->centralwidget->findChild<QSpinBox*>("m_cmyk_spin");
    QSpinBox* y_cmyk_spin = ui->centralwidget->findChild<QSpinBox*>("y_cmyk_spin");
    QSpinBox* k_cmyk_spin = ui->centralwidget->findChild<QSpinBox*>("k_cmyk_spin");

    connect(c_cmyk_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(c_cmyk_spin_valueChanged(int)));
    connect(m_cmyk_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(m_cmyk_spin_valueChanged(int)));
    connect(y_cmyk_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(y_cmyk_spin_valueChanged(int)));
    connect(k_cmyk_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(k_cmyk_spin_valueChanged(int)));


    map[c_cmyk_spin->objectName()] = &Models::get_c_cmyk;
    map[m_cmyk_spin->objectName()] = &Models::get_m_cmyk;
    map[y_cmyk_spin->objectName()] = &Models::get_y_cmyk;
    map[k_cmyk_spin->objectName()] = &Models::get_k_cmyk;

    QSlider* c_cmyk_slider = ui->centralwidget->findChild<QSlider*>("c_cmyk_slider");
    QSlider* m_cmyk_slider = ui->centralwidget->findChild<QSlider*>("m_cmyk_slider");
    QSlider* y_cmyk_slider = ui->centralwidget->findChild<QSlider*>("y_cmyk_slider");
    QSlider* k_cmyk_slider = ui->centralwidget->findChild<QSlider*>("k_cmyk_slider");

    connect(c_cmyk_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(c_cmyk_slider_valueChanged(int)));
    connect(m_cmyk_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(m_cmyk_slider_valueChanged(int)));
    connect(y_cmyk_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(y_cmyk_slider_valueChanged(int)));
    connect(k_cmyk_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(k_cmyk_slider_valueChanged(int)));

    map[c_cmyk_slider->objectName()] = &Models::get_c_cmyk;
    map[m_cmyk_slider->objectName()] = &Models::get_m_cmyk;
    map[y_cmyk_slider->objectName()] = &Models::get_y_cmyk;
    map[k_cmyk_slider->objectName()] = &Models::get_k_cmyk;
}

void MainWindow::connect_hsl_widget()
{
    QSpinBox* h_hsl_spin = ui->centralwidget->findChild<QSpinBox*>("h_hsl_spin");
    QSpinBox* s_hsl_spin = ui->centralwidget->findChild<QSpinBox*>("s_hsl_spin");
    QSpinBox* l_hsl_spin = ui->centralwidget->findChild<QSpinBox*>("l_hsl_spin");

    connect(h_hsl_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(h_hsl_spin_valueChanged(int)));
    connect(s_hsl_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(s_hsl_spin_valueChanged(int)));
    connect(l_hsl_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(l_hsl_spin_valueChanged(int)));

    map[h_hsl_spin->objectName()] = &Models::get_h_hsl;
    map[s_hsl_spin->objectName()] = &Models::get_s_hsl;
    map[l_hsl_spin->objectName()] = &Models::get_l_hsl;

    QSlider* h_hsl_slider = ui->centralwidget->findChild<QSlider*>("h_hsl_slider");
    QSlider* s_hsl_slider = ui->centralwidget->findChild<QSlider*>("s_hsl_slider");
    QSlider* l_hsl_slider = ui->centralwidget->findChild<QSlider*>("l_hsl_slider");

    connect(h_hsl_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(h_hsl_slider_valueChanged(int)));
    connect(s_hsl_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(s_hsl_slider_valueChanged(int)));
    connect(l_hsl_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(l_hsl_slider_valueChanged(int)));

    map[h_hsl_slider->objectName()] = &Models::get_h_hsl;
    map[s_hsl_slider->objectName()] = &Models::get_s_hsl;
    map[l_hsl_slider->objectName()] = &Models::get_l_hsl;
}

void MainWindow::connect_hsv_widget()
{
    QSpinBox* h_hsv_spin = ui->centralwidget->findChild<QSpinBox*>("h_hsv_spin");
    QSpinBox* s_hsv_spin = ui->centralwidget->findChild<QSpinBox*>("s_hsv_spin");
    QSpinBox* v_hsv_spin = ui->centralwidget->findChild<QSpinBox*>("v_hsv_spin");

    connect(h_hsv_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(h_hsv_spin_valueChanged(int)));
    connect(s_hsv_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(s_hsv_spin_valueChanged(int)));
    connect(v_hsv_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(v_hsv_spin_valueChanged(int)));

    map[h_hsv_spin->objectName()] = &Models::get_h_hsv;
    map[s_hsv_spin->objectName()] = &Models::get_s_hsv;
    map[v_hsv_spin->objectName()] = &Models::get_v_hsv;

    QSlider* h_hsv_slider = ui->centralwidget->findChild<QSlider*>("h_hsv_slider");
    QSlider* s_hsv_slider = ui->centralwidget->findChild<QSlider*>("s_hsv_slider");
    QSlider* v_hsv_slider = ui->centralwidget->findChild<QSlider*>("v_hsv_slider");

    connect(h_hsv_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(h_hsv_slider_valueChanged(int)));
    connect(s_hsv_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(s_hsv_slider_valueChanged(int)));
    connect(v_hsv_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(v_hsv_slider_valueChanged(int)));

    map[h_hsv_slider->objectName()] = &Models::get_h_hsv;
    map[s_hsv_slider->objectName()] = &Models::get_s_hsv;
    map[v_hsv_slider->objectName()] = &Models::get_v_hsv;
}

void MainWindow::connect_xyz_widget()
{
    QSpinBox* x_xyz_spin = ui->centralwidget->findChild<QSpinBox*>("x_xyz_spin");
    QSpinBox* y_xyz_spin = ui->centralwidget->findChild<QSpinBox*>("y_xyz_spin");
    QSpinBox* z_xyz_spin = ui->centralwidget->findChild<QSpinBox*>("z_xyz_spin");

    connect(x_xyz_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(x_xyz_spin_valueChanged(int)));
    connect(y_xyz_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(y_xyz_spin_valueChanged(int)));
    connect(z_xyz_spin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(z_xyz_spin_valueChanged(int)));

    map[x_xyz_spin->objectName()] = &Models::get_x_xyz;
    map[y_xyz_spin->objectName()] = &Models::get_y_xyz;
    map[z_xyz_spin->objectName()] = &Models::get_z_xyz;

    QSlider* x_xyz_slider = ui->centralwidget->findChild<QSlider*>("x_xyz_slider");
    QSlider* y_xyz_slider = ui->centralwidget->findChild<QSlider*>("y_xyz_slider");
    QSlider* z_xyz_slider = ui->centralwidget->findChild<QSlider*>("z_xyz_slider");

    connect(x_xyz_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(x_xyz_slider_valueChanged(int)));
    connect(y_xyz_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(y_xyz_slider_valueChanged(int)));
    connect(z_xyz_slider,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(z_xyz_slider_valueChanged(int)));

    map[x_xyz_slider->objectName()] = &Models::get_x_xyz;
    map[y_xyz_slider->objectName()] = &Models::get_y_xyz;
    map[z_xyz_slider->objectName()] = &Models::get_z_xyz;
}

void MainWindow::show_widget(int f, int s, int t)
{
    QWidget* widgets[] = {
        ui->rgb_block,
        ui->cmyk_block,
        ui->hsv_block,
        ui->hsl_block,
        ui->lab_block,
        ui->xyz_block,
    };

    for(int i = 0; i < 6; i++){
        if(i == f || i == s || i == t){
            widgets[i]->show();
        }else{
            widgets[i]->hide();
        }
    }
}


void MainWindow::load_rgb_lab_cmyk()
{
    show_widget(0, 4, 1);
}

void MainWindow::load_rgb_cmyk_hls()
{
    show_widget(0, 1, 3);
}

void MainWindow::load_rgb_xyz_lab()
{
    show_widget(0, 5, 4);
}

void MainWindow::load_rgb_hsv_lab()
{
    show_widget(0, 2, 4);
}

void MainWindow::load_cmyk_lab_hsv()
{
    show_widget(1, 4, 2);
}

void MainWindow::load_cmyk_rgb_hls()
{
    show_widget(1, 0, 3);
}

void MainWindow::load_cmyk_rgb_hsv()
{
    show_widget(1, 0, 2);
}

void MainWindow::load_rgb_xyz_hsv()
{
    show_widget(0, 5, 2);
}

void MainWindow::load_hsv_xyz_lab()
{
    show_widget(2, 5, 4);
}

void MainWindow::load_cmyk_lab_rgb()
{
    show_widget(1, 4, 0);
}

void MainWindow::load_xyz_lab_hls()
{
    show_widget(5, 4, 3);
}

void MainWindow::load_rgb_xyz_hls()
{
    show_widget(0, 5, 3);
}

void MainWindow::load_rgb_xyz_cmyk()
{
    show_widget(0, 5, 1);
}

void MainWindow::load_cmyk_lab_xyz()
{
    show_widget(1, 4, 5);
}

void MainWindow::load_rgb_cmyk_hsv()
{
    show_widget(0, 1, 2);
}

void MainWindow::load_cmyk_hls_xyz()
{
    show_widget(1, 3, 5);
}

void MainWindow::load_rgb_hls_lab()
{
    show_widget(0, 3, 4);
}

void MainWindow::load_cmyk_xyz_rgb()
{
    show_widget(1, 5, 0);
}

void MainWindow::r_rgb_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_r_rgb(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}

void MainWindow::g_rgb_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_g_rgb(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::b_rgb_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_b_rgb(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::l_lab_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_l_lab(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::a_lab_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_a_lab(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::b_lab_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_b_lab(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::c_cmyk_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_c_cmyk(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::m_cmyk_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_m_cmyk(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::y_cmyk_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_y_cmyk(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::k_cmyk_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_k_cmyk(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::h_hsl_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_h_hsl(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::s_hsl_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_s_hsl(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::l_hsl_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_l_hsl(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::h_hsv_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_h_hsv(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::s_hsv_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_s_hsv(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::v_hsv_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_v_hsv(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::x_xyz_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_x_xyz(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::y_xyz_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_y_xyz(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::z_xyz_spin_valueChanged(int arg1)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_z_xyz(arg1);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::r_rgb_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_r_rgb(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::g_rgb_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_g_rgb(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::b_rgb_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_b_rgb(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::l_lab_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_l_lab(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::a_lab_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_a_lab(value);
        update_values(obj->objectName());
        in_change = false;
    }
}


void MainWindow::b_lab_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_b_lab(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::c_cmyk_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_c_cmyk(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::m_cmyk_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_m_cmyk(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::y_cmyk_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_y_cmyk(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::k_cmyk_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_k_cmyk(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::h_hsl_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_h_hsl(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::s_hsl_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_s_hsl(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::l_hsl_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_l_hsl(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::h_hsv_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_h_hsv(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::s_hsv_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_s_hsv(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::v_hsv_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_v_hsv(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::x_xyz_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_x_xyz(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::y_xyz_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_y_xyz(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}


void MainWindow::z_xyz_slider_valueChanged(int value)
{
    if(!in_change)
    {
        QSpinBox* obj = (QSpinBox*)sender();
        in_change = true;
        models->set_z_xyz(value);
        update_values(obj->objectName());
        in_change = false;
        update_color();
    }
}

void MainWindow::color_selected(QColor color)
{
    if(!in_change)
    {
        in_change = true;
        models->set_r_rgb(color.red());
        models->set_g_rgb(color.green());
        models->set_b_rgb(color.blue());
        update_values("");
        in_change = false;
        update_color();

        QPoint pos = ui->colorPicker->getPos();
        _widgetOnTheTop->move(pos.x() + 17, pos.y() + 17);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        load_rgb_lab_cmyk();
    }
    else if(index == 1){
        load_rgb_cmyk_hls();
    }
    else if(index == 2){
        load_rgb_xyz_lab();
    }
    else if(index == 3){
        load_rgb_hsv_lab();
    }
    else if(index == 4){
        load_cmyk_lab_hsv();
    }
    else if(index == 5){
        load_cmyk_rgb_hls();
    }
    else if(index == 6){
        load_cmyk_rgb_hsv();
    }
    else if(index == 7){
        load_rgb_xyz_hsv();
    }
    else if(index == 8){
        load_hsv_xyz_lab();
    }
    else if(index == 9){
        load_cmyk_lab_rgb();
    }
    else if(index == 10){
        load_xyz_lab_hls();
    }
    else if(index == 11){
        load_rgb_xyz_hls();
    }
    else if(index == 12){
        load_rgb_xyz_cmyk();
    }
    else if(index == 13){
        load_cmyk_lab_xyz();
    }
    else if(index == 14){
        load_rgb_cmyk_hsv();
    }
    else if(index == 15){
        load_cmyk_hls_xyz();
    }
    else if(index == 16){
        load_rgb_hls_lab();
    }
    else if(index == 17){
        load_cmyk_xyz_rgb();
    }
}

