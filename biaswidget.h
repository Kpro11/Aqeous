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

    QPointF middle;
    QPointF up;
    QPointF east;
    QPointF south;
    QPointF down;
    QPointF west;
    QPointF north;

    QPen *backgroundArrowPen;
    QPen *biasArrowPenNorth;
    QPen *biasArrowPenEast;
    QPen *biasArrowPenDown;

    double fontSize;

    ArrowLines * backgroundArrowLines;
    ArrowLines * biasArrowLines;
    ArrowLines * biasArrowLinesOriginal;

    double arrowLengthNorth;
    double arrowLengthEast;
    double arrowLengthDown;

    //
    // Functions:
    //
    void drawBackgroundArrows(QPainter *painter);
    void drawBiasArrows(QPainter *painter);

signals:

public slots:
    void updateBias(double north, double east, double down);

};

#endif // BIASWIDGET_H


