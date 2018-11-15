#include "biaswidget.h"
#include <QLineF>
#include <QDebug>

BiasWidget::BiasWidget(QWidget *parent, int _frameWidth, int _frameHeight) : QWidget(parent)
{
    frameWidth = _frameWidth;
    frameHeight = _frameHeight;
    antialiased = false;
    transformed = false;
}

void BiasWidget::paintEvent(QPaintEvent * ) {

    // make the 7 points we need, each point represent an arrows max position
    static const QPointF points[7] = {
        QPointF(frameWidth/2, frameHeight/2), // middle
        QPointF(frameWidth/2, 0), // middle top
        QPointF(frameWidth, frameHeight / 3), // right upper
        QPointF(frameWidth, (frameHeight * 2) / 3), // right lower
        QPointF(frameWidth/2, frameHeight), // middle bottom
        QPointF(0, (frameHeight * 2) / 3), // left lower
        QPointF(0, frameHeight / 3) // left uppder
    };

    QPainter painter( this );

    painter.setWindow(QRect(0, 0, frameWidth, frameHeight));
    painter.setViewport(0, 0, frameWidth, frameHeight);

    //pen.setStyle(Qt::DashDotLine);
    pen.setWidth(3);
    pen.setBrush(Qt::green);
    //pen.setCapStyle(Qt::RoundCap);
    //pen.setJoinStyle(Qt::RoundJoin);

    painter.setPen(pen);
    painter.setBrush(brush);

    painter.drawRect(QRect(0,0, 40, 40));

    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);

    QLineF line = QLineF(points[0], points[1]);
    line.setLength(100);

    painter.drawLine(line);


    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
}

QSize BiasWidget::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize BiasWidget::sizeHint() const
{
    qDebug() << "Setting size hint with: " << frameWidth << frameHeight;
    return QSize(frameWidth, frameHeight);
}
