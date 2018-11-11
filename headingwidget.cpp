#include "headingwidget.h"
#include <QDebug>


HeadingWidget::HeadingWidget(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight)
{
    videoPlayer = _videoPlayer;
    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    slider = new QSlider( Qt::Horizontal, _videoPlayer );

    slider->setGeometry(30,80, *windowWidth - 60, 40);
}
