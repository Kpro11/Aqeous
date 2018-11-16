#include "biaswidget.h"
#include <QLineF>
#include <QDebug>
#include "fontsize.h" // using only the linearTransform function

BiasWidget::BiasWidget(QWidget *parent, int _frameWidth, int _frameHeight) : QWidget(parent)
{
    frameWidth = _frameWidth;
    frameHeight = _frameHeight;

    // pen used to create background arrows (not the ones created by real bias)
    int penWidth = 4;

    backgroundArrowPen = new QPen();
    backgroundArrowPen->setStyle(Qt::SolidLine);    // tried using DashedLine here instead but it doesnt fill up 100% at the end
    backgroundArrowPen->setWidth(penWidth);
    backgroundArrowPen->setBrush(Qt::darkGray);

    // set fontSize
    fontSize = frameWidth / 18;

    // We need to pad the points on the frame to allow rendering of text after an arrow
    double spacing = fontSize * 2;

    // Points on the frame that correspond to where the different arrow should point
    middle =  QPointF(frameWidth/2, frameHeight/2);        // middle point
    up = QPointF(frameWidth/2, spacing);                         // top middle
    east = QPointF(frameWidth - spacing, frameHeight / 3);           // right upper
    south = QPointF(frameWidth - spacing, (frameHeight * 2) / 3);    // right lower
    down = QPointF(frameWidth/2, frameHeight - spacing);             // bottom middle
    west = QPointF(spacing, (frameHeight * 2) / 3);              // left lower
    north = QPointF(spacing, frameHeight / 3);                   // left upper

    // class used store all the background arrow lines
    backgroundArrowLines = new ArrowLines();

    // Creates the actual lines and store them in the class
    backgroundArrowLines->up = QLineF(middle, up);
    backgroundArrowLines->east = QLineF(middle, east);
    backgroundArrowLines->south = QLineF(middle,south);
    backgroundArrowLines->down = QLineF(middle, down);
    backgroundArrowLines->west = QLineF(middle, west);
    backgroundArrowLines->north = QLineF(middle, north);

    // class used to store all the real bias arrow lines
    biasArrowLines = new ArrowLines();

    biasArrowLines->up = QLineF(middle, up);
    biasArrowLines->east = QLineF(middle, east);
    biasArrowLines->south = QLineF(middle,south);
    biasArrowLines->down = QLineF(middle, down);
    biasArrowLines->west = QLineF(middle, west);
    biasArrowLines->north = QLineF(middle, north);

    // create a copy
    biasArrowLinesOriginal = new ArrowLines();

    biasArrowLinesOriginal->up = QLineF(middle, up);
    biasArrowLinesOriginal->east = QLineF(middle, east);
    biasArrowLinesOriginal->south = QLineF(middle,south);
    biasArrowLinesOriginal->down = QLineF(middle, down);
    biasArrowLinesOriginal->west = QLineF(middle, west);
    biasArrowLinesOriginal->north = QLineF(middle, north);



    // calculate the length of bias arrows
    arrowLengthDown = middle.y() - down.y();
    arrowLengthNorth = sqrt(pow(middle.x() - north.x(), 2) + pow(north.y() - middle.y(), 2));
    arrowLengthEast = arrowLengthNorth;

    // set default length to zero
    biasArrowLines->up.setLength(0);
    biasArrowLines->east.setLength(0);
    biasArrowLines->south.setLength(0);
    biasArrowLines->down.setLength(0);
    biasArrowLines->west.setLength(0);
    biasArrowLines->north.setLength(0);



    // create the different pens used with real bias arrows

    biasArrowPenNorth = new QPen();
    biasArrowPenNorth->setWidth(penWidth);
    biasArrowPenNorth->setBrush(Qt::red);

    biasArrowPenEast = new QPen();
    biasArrowPenEast->setWidth(penWidth);
    biasArrowPenEast->setBrush(Qt::yellow);

    biasArrowPenDown = new QPen();
    biasArrowPenDown->setWidth(penWidth);
    biasArrowPenDown->setBrush(Qt::green);

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

    // draw the arrow letters
    drawBiasArrowLetters(&painter);

    // update length of real bias arrows:
    // testing func: updateBias(-359,200,-50);

    // draw all the real bias arrows
    drawBiasArrows(&painter);
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

/// Draws all the real bias arrows
/// @param * painter The QPainter object created in paintEvent
void BiasWidget::drawBiasArrows(QPainter *painter) {

    qDebug() << "drawBiasArrows: " << biasArrowLines->north.length();

    // we set new pens on every axis because they should have different colors
    painter->setPen(*biasArrowPenNorth);
    if (biasArrowLines->north.length() > 0)
        painter->drawLine(biasArrowLines->north);
    if (biasArrowLines->south.length() > 0)
        painter->drawLine(biasArrowLines->south);

    painter->setPen(*biasArrowPenEast);
    if (biasArrowLines->west.length() > 0)
        painter->drawLine(biasArrowLines->west);
    if (biasArrowLines->east.length() > 0)
        painter->drawLine(biasArrowLines->east);

    painter->setPen(*biasArrowPenDown);
    if (biasArrowLines->up.length() > 0)
        painter->drawLine(biasArrowLines->up);
    if (biasArrowLines->down.length() > 0)
        painter->drawLine(biasArrowLines->down);
}

void BiasWidget::drawBiasArrowLetters(QPainter *painter) {
    QString n = "N";
    QString e = "E";
    QString d = "D";
    QString s = "S";
    QString w = "W";
    QString u = "U";

    QPointF n_p = north;
    QPointF e_p = east;
    QPointF d_p = down;
    QPointF s_p = south;
    QPointF w_p = west;
    QPointF u_p = up;       // hue hue

    // adjust the points to better place the letters

    double spacing = frameWidth / 20;   // random reference point

    n_p.setX( n_p.x() - spacing * 1.4);

    s_p.setX( s_p.x() + spacing * 0.6 );
    s_p.setY( s_p.y() + spacing * 0.7);

    e_p.setX( e_p.x() + spacing * 0.6 );
    e_p.setY( e_p.y() + spacing * 0.2 );

    w_p.setX( w_p.x() - spacing * 1.6 );
    w_p.setY( w_p.y() + spacing * 0.8 );

    u_p.setX( u_p.x() - spacing * 0.35 );
    u_p.setY( u_p.y() - spacing * 0.4 );

    d_p.setX( d_p.x() - spacing * 0.35 );
    d_p.setY( d_p.y() + spacing * 1.4 );

    // set the font size
    QFont font = painter->font();
    font.setPixelSize(fontSize);
    painter->setFont(font);

    // Finally draw the text
    painter->drawText(n_p, n);
    painter->drawText(s_p, s);
    painter->drawText(e_p, e);
    painter->drawText(w_p, w);
    painter->drawText(u_p, u);
    painter->drawText(d_p, d);
}


/// Updates the length of the bias arrows
/// @param double _north => the bias gotten from controller - [-400,400]
/// @param double _east => [-400,400]
/// @param double _down => [-200,200]
void BiasWidget::updateBias(double _north, double _east, double _down) {
    qDebug() << "Updating bias with " << _north << _east << _down;
    // update _north and south axis:
    if(_north > 0) {
        // set south length to 0
        biasArrowLines->south.setLength(0);
        // transform from [0,400] to [0, maxArrowLength]
        double newLength = FontSize::linearTransform(_north, 0, 400, 0, arrowLengthNorth);
        // here we have to make a copy of the original line because somehow setLength doesnt work when length is set to zero
        biasArrowLines->north = biasArrowLinesOriginal->north;
        // set the new length
        biasArrowLines->north.setLength(newLength);
        qDebug() << newLength << biasArrowLines->north.length();
    } else if (_north < 0) {
        // set _north length to 0
        biasArrowLines->north.setLength(0);
        double newLength = FontSize::linearTransform(abs(_north), 0, 400, 0, arrowLengthNorth);
        biasArrowLines->south = biasArrowLinesOriginal->south;
        biasArrowLines->south.setLength(newLength);
    } else {
        // set both to zero
        biasArrowLines->north.setLength(0);
        biasArrowLines->south.setLength(0);
    }

    // east and west axis
    if (_east > 0) {
        biasArrowLines->west.setLength(0);
        double newLength = FontSize::linearTransform(_east, 0, 400, 0, arrowLengthEast);
        biasArrowLines->east = biasArrowLinesOriginal->east;
        biasArrowLines->east.setLength(newLength);
    } else if (_east < 0) {
        biasArrowLines->east.setLength(0);
        double newLength = FontSize::linearTransform(abs(_east), 0, 400, 0, arrowLengthEast);
        biasArrowLines->west = biasArrowLinesOriginal->west;
        biasArrowLines->west.setLength(newLength);
    } else {
        biasArrowLines->east.setLength(0);
        biasArrowLines->west.setLength(0);
    }

    // up and down axis
    qDebug() << "Down " << _down;
    if (_down > 0) {
        biasArrowLines->down.setLength(0);
        double newLength = FontSize::linearTransform(abs(_down), 0, 200, 0, arrowLengthDown);
        biasArrowLines->up = biasArrowLinesOriginal->up;
        biasArrowLines->up.setLength(newLength);
    } else if (_down < 0) {
        biasArrowLines->up.setLength(0);
        double newLength = FontSize::linearTransform(abs(_down), 0, 200, 0, arrowLengthDown);
        biasArrowLines->down = biasArrowLinesOriginal->down;
        biasArrowLines->down.setLength(newLength);
    } else {
        biasArrowLines->down.setLength(0);
        biasArrowLines->up.setLength(0);
    }

    // update the component, this will call the paintEvent
    update();
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
