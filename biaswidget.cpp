#include "biaswidget.h"
#include <QLineF>
#include <QDebug>

BiasWidget::BiasWidget(QWidget *parent, int _frameWidth, int _frameHeight) : QWidget(parent)
{
    frameWidth = _frameWidth;
    frameHeight = _frameHeight;

    // pen used to create background arrows (not the ones created by real bias)
    backgroundArrowPen = new QPen();
    backgroundArrowPen->setStyle(Qt::DotLine);
    backgroundArrowPen->setWidth(6);
    backgroundArrowPen->setBrush(Qt::darkGray);


    // Points on the frame that correspond to where the different arrow should point
    QPointF middle =  QPointF(frameWidth/2, frameHeight/2);        // middle point
    QPointF up = QPointF(frameWidth/2, 0);                         // top middle
    QPointF east = QPointF(frameWidth, frameHeight / 3);           // right upper
    QPointF south = QPointF(frameWidth, (frameHeight * 2) / 3);    // right lower
    QPointF down = QPointF(frameWidth/2, frameHeight);             // bottom middle
    QPointF west = QPointF(0, (frameHeight * 2) / 3);              // left lower
    QPointF north = QPointF(0, frameHeight / 3);                   // left upper

    // class used store all the background arrow lines
    backgroundArrowLines = new ArrowLines();

    // Creates the actual lines and store them in the class
    backgroundArrowLines->up = QLineF(middle, up);
    backgroundArrowLines->east = QLineF(middle, east);
    backgroundArrowLines->south = QLineF(middle,south);
    backgroundArrowLines->down = QLineF(middle, down);
    backgroundArrowLines->west = QLineF(middle, west);
    backgroundArrowLines->north = QLineF(middle, north);
}

/// Draws the entire widget, is called every time component updates
/// @param QPaintEvent * event Check QPainter spec
void BiasWidget::paintEvent(QPaintEvent * ) {
    QPainter painter( this );

    // sets the window and viewport to be the same size as parent
    painter.setWindow(QRect(0, 0, frameWidth, frameHeight));
    painter.setViewport(0, 0, frameWidth, frameHeight);

    // Activate anti aliasing to improve rendering
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw all the background arrows
    drawBackgroundArrows(&painter);
}

/// Draws all the background arrows
/// @param * painter The QPainter object created in paintEvent
void BiasWidget::drawBackgroundArrows(QPainter *painter) {
    painter->setPen(*backgroundArrowPen);

    painter->drawLine(backgroundArrowLines->up);
    painter->drawLine(backgroundArrowLines->east);
    painter->drawLine(backgroundArrowLines->south);
    painter->drawLine(backgroundArrowLines->down);
    painter->drawLine(backgroundArrowLines->west);
    painter->drawLine(backgroundArrowLines->north);
}

/// Sets the minimum size - should never be called tho?
/// @return QSize - the size of the window
QSize BiasWidget::minimumSizeHint() const
{
    return QSize(200, 200);
}

/// Sets the size of the widget
/// @return QSize - the wanted size of the widget based on parent witdh and height
QSize BiasWidget::sizeHint() const
{
    return QSize(frameWidth, frameHeight);
}
