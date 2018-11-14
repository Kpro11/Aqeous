#ifndef DEPTHWIDGET_H
#define DEPTHWIDGET_H

#include <QWidget>
#include <QLabel>
#include "position.h"

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
    double depthRef;

private:
    QWidget * videoPlayer;

    int * windowWidth;
    int * windowHeight;

    int frameWidth;
    int frameHeight;

    QLabel * currentDepth;
    Position * currentDepthPos;

    QLabel * depthReference;
    Position * depthReferencePos;

    QLabel * depthReferenceLock;
    Position * depthReferenceLockPos;

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
    void setPosition(QLabel * _lbl, Position * _lblPos);
};

#endif // DEPTHWIDGET_H
