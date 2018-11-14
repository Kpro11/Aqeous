#ifndef DEPTHWIDGET_H
#define DEPTHWIDGET_H

#include <QWidget>
#include <QLabel>

class DepthLabel {
    public:
        QLabel *label;
        int value;
};


class DepthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DepthWidget(QWidget *parent = nullptr);
    void setupUI(QWidget * _videoPlayer, int * _windowWidth, int * _windowHeight);
    double depth = 0.0;

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
    QString bigNumStyle = " QLabel { color: white; font-size: 23px; } ";
    QString numStyle = " QLabel { color: white; font-size: 17px; } ";

signals:

public slots:
    void updateLabels();
    void updateDepth(double _depth);
    void updateFlags(double, double);
};

#endif // DEPTHWIDGET_H
