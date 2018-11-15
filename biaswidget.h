#ifndef BIASWIDGET_H
#define BIASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPaintEvent>

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
    const double maxArrowLength = 100; // in px
    int frameWidth;
    int frameHeight;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;

signals:

public slots:

};

#endif // BIASWIDGET_H


