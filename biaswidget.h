#ifndef BIASWIDGET_H
#define BIASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPaintEvent>

/// class used to hold all the lines required to draw one bias widget
class ArrowLines {
public:
    QLineF up;
    QLineF east;
    QLineF south;
    QLineF down;
    QLineF west;
    QLineF north;
};

class BiasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BiasWidget(QWidget *parent = nullptr, int _frameWidth = 0, int _frameHeight = 0);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;


protected:
    void paintEvent(QPaintEvent * event) override;

private:
    //
    // Variables:
    //

    const double maxArrowLength = 100; // in px
    int frameWidth;
    int frameHeight;
    // QPen pen;
    // QBrush brush;

    QPen *backgroundArrowPen;

    ArrowLines * backgroundArrowLines;

    //
    // Functions:
    //
    void drawBackgroundArrows(QPainter *painter);



signals:

public slots:

};

#endif // BIASWIDGET_H


