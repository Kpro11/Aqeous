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

    QString borderStyleSheet;
    QString whiteText;
    QString bigNumStyle;
    QString numStyle;
    QString depthStyleSheet;

signals:

public slots:
    void updateLabels();
    void updateDepth(double _depth);
    void updateAutoDepth(double _autoDepth);
    void updateDepthReference(double _depthRef);
    void setPosition(QLabel * _lbl, Position * _lblPos);
    QString formatDepth(double _depth);
    void setupStyleSheets();
};

#endif // DEPTHWIDGET_H
