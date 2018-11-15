#ifndef BIASWIDGET_H
#define BIASWIDGET_H

#include <QWidget>

class BiasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BiasWidget(QWidget *parent = nullptr);

private:
    const double maxArrowLength = 100; // in px


signals:

public slots:

};

#endif // BIASWIDGET_H
