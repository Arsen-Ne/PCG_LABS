#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QVector>
#include <QCheckBox>
struct vect
{
    double x;
    double y;
    double x1,x2,y1,y2;
    int end;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void averagePoint();
    void kirusBack();
    void clearPlots();
    void readFile();
private:
     QCustomPlot* plot;
     QVBoxLayout* box = new QVBoxLayout(this);
     QHBoxLayout* boxbuttons = new QHBoxLayout(this);
     QPushButton* pbAveragePoint = new QPushButton("Алгоритм средней точки",this);
     QPushButton* pbMnogoyg = new QPushButton("Алгоритм Кируса-Бека",this);
     QPushButton* pbClear = new QPushButton("Очистить",this);
     QPushButton* pbOpenFile = new QPushButton("Открыть файл",this);
     int currentGraph = 0;
     double x_min,y_min,x_max,y_max;
     int n,m = -1;
     QVector <double> vector_X_1;
     QVector <double> vector_Y_1;
     QVector <double> vector_X_2;
     QVector <double> vector_Y_2;

     QVector <double> X_Mn;
     QVector <double> Y_Mn;
     QVector <bool> check;
     QVector <vect> edges;
     int q = 0;
     int id,ind=0;
     double f_x,f_y;
     void LayoutSettings();
     void draw();
     void drawRectangle();
     void drawMnogoug();
     void cutLine1(double,double,double,double);
     void cutLine2(double,double,double,double);
     void where(double,bool&,double,bool&,double);
};
#endif // MAINWINDOW_H
