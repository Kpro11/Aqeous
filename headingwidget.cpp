#include "headingwidget.h"
#include <QDebug>
#include "QHBoxLayout"
#include <QLabel>

HeadingWidget::HeadingWidget(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight)
{
    videoPlayer = _videoPlayer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    // create frame that acts as a container for this heading widget;
    frame = new QFrame( videoPlayer );
    frame->setObjectName("headingWidget");

    // set the position and dimensions (start x, start y, width, heigth)
    frame->setGeometry(200,80, *windowWidth - 400, 40);
    // add a border to the bottom
    frame->setStyleSheet( "QFrame#headingWidget { border: 3px solid white; border-top: 0; border-left: 0; border-right: 0; }" );




    QLabel * lbl = new QLabel( "Test1", frame );
    lbl->setStyleSheet(whiteText);
    lbl->setGeometry(0,0, 100, 40);
    QLabel * lbl2 = new QLabel( "Test2", frame );
    lbl2->setStyleSheet(whiteText);
    lbl2->setGeometry(100,0, 100, 40);
}


