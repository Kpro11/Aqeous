#ifndef DEPTHWIDGET_H
#define DEPTHWIDGET_H

#include <QWidget>
#include <QLabel>

class DepthLabel {
    public:
        QLabel *label;
        int value;
        QChar letter;
};


class DepthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DepthWidget(QWidget *parent = nullptr);
    void setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight);
    double depth;

private:
    QWidget * videoPlayer;

    int * windowWidth;
    int * windowHeight;

    int frameWidth;
    int frameHeight;

    QLabel * currentDepth;

    //Frame that holds the labels
    QFrame * frame;

    QList<DepthLabel *> labels;

    QString whiteText = " QLabel { color: white;  } ";   // stylesheet for white text


signals:

public slots:
};

#endif // DEPTHWIDGET_H
