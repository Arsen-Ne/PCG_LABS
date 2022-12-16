#ifndef PALETTE_H
#define PALETTE_H

#include <QLabel>
#include <QMouseEvent>

class Palette : public QLabel
{
    Q_OBJECT
public:
    Palette(QWidget* parent = Q_NULLPTR);
    ~Palette();

    QPoint getPos() const;

signals:
    void clickedColor(QColor color);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    QPoint pos;
};

#endif // PALETTE_H
