#include "palette.h"
#include <QPainter>

Palette::Palette(QWidget *parent): QLabel(parent)
{
    pos.setX(-1);
    pos.setY(-1);
}

Palette::~Palette()
{

}

void Palette::mousePressEvent(QMouseEvent *event)
{
    QRect rectangle = rect();
    QPixmap pixmap(rectangle.size());
    render(&pixmap, QPoint(), QRegion(rectangle));
    QImage img = pixmap.toImage();
    pos = event->pos();
    QColor color = img.pixelColor(event->pos());
    emit clickedColor(color);
}


QPoint Palette::getPos() const
{
    return pos;
}
